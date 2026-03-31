#include <ESP8266WiFi.h>
#include <espnow.h>

const int trigPin = 5;  // D1
const int echoPin = 4;  // D2
const int buzzer = 14;  // D5

uint8_t terminalAddress[] = {0x40, 0xF5, 0x20, 0x2D, 0xC2, 0x23};

struct Message {
  int status; // 1 = Intruz, 0 = OK, 2 = Blad/Alarm
} myData;

int alarmMode = 0; // 0-cisza, 1-pikanie, 2-alarm

void onDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  alarmMode = myData.status;
  
  // Jeśli system rozbrojony wymuś ciszę
  if(alarmMode == 0) digitalWrite(buzzer, HIGH);
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  digitalWrite(buzzer, HIGH); 
  pinMode(buzzer, OUTPUT);
  
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) return;
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_add_peer(terminalAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_recv_cb(onDataRecv);
}

void loop() {
  // Pomiar dystansu
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  // Wykrycie intruza (tylko gdy system jest w trybie OK)
  if (distance > 0 && distance < 50 && alarmMode == 0) {
    myData.status = 1;
    esp_now_send(terminalAddress, (uint8_t *) &myData, sizeof(myData));
    alarmMode = 1; // Tryb ostrzegawczy
    delay(500);
  }

  // Obsługa dźwięku
  if (alarmMode == 1 || alarmMode == 2) { 
    digitalWrite(buzzer, LOW);  // Wyje
    delay(80);
    digitalWrite(buzzer, HIGH); // Cisza
    delay(200);
  } else {
    digitalWrite(buzzer, HIGH);
  }
  
  delay(50);
}