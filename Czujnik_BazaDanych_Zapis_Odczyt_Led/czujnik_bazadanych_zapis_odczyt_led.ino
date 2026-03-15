#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const char* ssid = "iot";
const char* pass = "iotinternet";
const char* serverURL = "http://10.33.2.194/iot/addSensorData.php"; // IP KOMPUTERA
void setup() {
 Serial.begin(115200);
 delay(1000);
 Serial.println("\n\n--- START SYSTEMU ---");
 pinMode(LED_BUILTIN, OUTPUT);
 dht.begin();
 // Inicjalizacja OLED
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
   Serial.println(F("BŁĄD: Nie znaleziono ekranu OLED (0x3C). Spróbuj zmienić adres na 0x3D w kodzie."));
 } else {
   Serial.println(F("Ekran OLED: OK"));
   display.clearDisplay();
   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(0,0);
   display.println("System startuje...");
   display.display();
 }
 // Łączenie z WiFi
 Serial.print("Laczenie z WiFi: ");
 Serial.println(ssid);
 WiFi.begin(ssid, pass);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 Serial.println("\nWiFi polaczone!");
 Serial.print("Adres IP ESP: ");
 Serial.println(WiFi.localIP());
}
void loop() {
 if (WiFi.status() == WL_CONNECTED) {
   float t = dht.readTemperature();
   float h = dht.readHumidity();
   if (isnan(t) || isnan(h)) {
     Serial.println("Blad odczytu z DHT11!");
   } else {
     Serial.printf("Odczyt: T=%.1f C, H=%.1f%%\n", t, h);
   }
   WiFiClient client;
   HTTPClient http;
   Serial.print("Wysylanie danych do: ");
   Serial.println(serverURL);
   http.begin(client, serverURL);
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
   String postData = "deviceId=arduDevId&temp=" + String(t) + "&humi=" + String(h);
   int httpCode = http.POST(postData);
   if (httpCode > 0) {
     Serial.printf("Serwer odpowiedzial (kod %d)\n", httpCode);
     String payload = http.getString();
     Serial.print("Tresc odpowiedzi: ");
     Serial.println(payload);
     // Parsowanie odpowiedzi JSON
     StaticJsonDocument<256> doc;
     DeserializationError error = deserializeJson(doc, payload);
     if (!error) {
       int ledState = doc["led_state"];
       const char* sTime = doc["serverTime"];
       // Sterowanie diodą (logika odwrócona dla ESP8266)
       digitalWrite(LED_BUILTIN, ledState == 1 ? LOW : HIGH);
       Serial.printf("Akcja: LED set to %d, Czas serwera: %s\n", ledState, sTime);
       // Wyświetlanie na ekranie
       display.clearDisplay();
       display.setCursor(0,0);
       display.setTextSize(1);
       display.println("POLACZONO Z BAZA");
       display.print("Czas: "); display.println(sTime);
       display.drawLine(0, 15, 128, 15, WHITE);
       display.setTextSize(2);
       display.setCursor(0, 25);
       display.print("T: "); display.print(t, 1); display.println(" C");
       display.print("H: "); display.print(h, 0); display.println(" %");
       display.display();
     } else {
       Serial.print("Blad parsowania JSON: ");
       Serial.println(error.c_str());
     }
   } else {
     Serial.printf("BŁĄD HTTP: %s\n", http.errorToString(httpCode).c_str());
     display.clearDisplay();
     display.setCursor(0,0);
     display.println("BLAD SERWERA!");
     display.println(http.errorToString(httpCode));
     display.display();
   }
   http.end();
 } else {
   Serial.println("Rozlaczono z WiFi!");
 }
 Serial.println("--- Czekam 10 sekund ---\n");
 delay(10000);
}