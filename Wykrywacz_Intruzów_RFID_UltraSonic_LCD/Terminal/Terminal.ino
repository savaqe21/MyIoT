#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

// PINY DLA RFID (SPI)
#define SS_PIN 15 // D8
#define RST_PIN 0 // D3

MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// ADRES MAC STRAŻNIKA (NodeMCU z czujnikiem i buzzerem)
uint8_t sensorAddress[] = {0x40, 0xF5, 0x20, 0x2E, 0x6F, 0x90};

// TWOJE UID KARTY
String masterUID = "c6 03 96 2c";

// ZMIENNE LOGICZNE I CZASOWE
unsigned long intruderTime = 0;   // Moment wykrycia intruza
long durationLimit = 30000;       // Startowy czas: 30 sekund
bool waiting = false;             // Czy system jest w trybie autoryzacji

struct Message {
  int status; // 0=OK, 1=Intruz, 2=Alarm
} myData;

// FUNKCJA ODBIERANIA DANYCH (Wywoływana przez ESP-NOW)
void onDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  struct Message incoming;
  memcpy(&incoming, incomingData, sizeof(incoming));
  
  if (incoming.status == 1 && !waiting) {
    waiting = true;
    intruderTime = millis();
    durationLimit = 30000;
  }
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  
  // Inicjalizacja ekranu OLED (próba dwóch adresów I2C)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();

  // Konfiguracja ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Blad ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_add_peer(sensorAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_recv_cb(onDataRecv);
  
  Serial.println("Terminal Gotowy");
}

void loop() {
  display.clearDisplay();
  display.setCursor(0,0);

  if (!waiting) {
    // TRYB CZUWANIA
    display.setTextSize(1);
    display.println("SYSTEM UZBROJONY");
    display.println("\nStatus: Bezpiecznie");
    display.display();
  } 
  else {
    // TRYB WYKRYCIA INTRUZA
    long elapsed = millis() - intruderTime;
    long timeLeft = durationLimit - elapsed;
    
    // Sprawdzenie czy czas minął
    if (timeLeft <= 0) {
      display.setTextSize(2);
      display.println("ALARM!!!");
      display.setTextSize(1);
      display.println("\nBrak autoryzacji!");
      display.display();
      
      myData.status = 2; // Wyślij sygnał ciągłego alarmu
      esp_now_send(sensorAddress, (uint8_t *) &myData, sizeof(myData));
    } 
    else {
      // Wyświetlanie odliczania
      display.setTextSize(1);
      display.println("INTRUZ WYKRYTY!");
      display.setTextSize(2);
      display.print(timeLeft/1000); display.println(" sek");
      display.setTextSize(1);
      display.println("\nZbliz karte...");
      display.display();

      // Obsługa czytnika RFID
      if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
          uid += String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
          uid += String(rfid.uid.uidByte[i], HEX);
        }
        uid.trim();
        
        Serial.print("Odczytano UID: ");
        Serial.println(uid);

        if (uid == masterUID) {
          // DOBRA KARTA - ROZBROJENIE
          myData.status = 0; 
          esp_now_send(sensorAddress, (uint8_t *) &myData, sizeof(myData));
          waiting = false;
          
          display.clearDisplay();
          display.setCursor(0,0);
          display.println("KARTA OK");
          display.println("ROZBROJONO");
          display.display();
          delay(2000);
        } 
        else {
          // ZŁA KARTA - KARA 5 SEKUND
          durationLimit -= 5000; 
          
          display.clearDisplay();
          display.setCursor(0,0);
          display.setTextSize(2);
          display.println("ZLA KARTA");
          display.setTextSize(1);
          display.println("\nKARA: -5 SEKUND!");
          display.display();
          delay(1000); // Pauza na przeczytanie komunikatu
        }
      }
    }
  }
  delay(50); // Małe opóźnienie dla stabilności pętli
}