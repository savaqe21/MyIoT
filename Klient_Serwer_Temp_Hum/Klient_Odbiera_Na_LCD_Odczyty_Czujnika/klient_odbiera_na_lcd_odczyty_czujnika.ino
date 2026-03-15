#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, -1);
const char* ssid = "Stacja_Pogodowa";
const char* pass = "haslo123";
// Adres IP serwera z trybem AP
const char* serverURL = "http://192.168.4.1/pogoda";
void setup() {
 Serial.begin(115200);
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
   for(;;);
 }
 display.clearDisplay();
 display.setTextColor(WHITE);
 // Łączenie z WiFi rozsyłanym przez Serwer
 WiFi.begin(ssid, pass);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
}
void loop() {
 if (WiFi.status() == WL_CONNECTED) {
   WiFiClient client;
   HTTPClient http;
   http.begin(client, serverURL);
   int httpCode = http.GET();
   if (httpCode == 200) {
     String payload = http.getString();
     StaticJsonDocument<200> doc;
     deserializeJson(doc, payload);
     float t = doc["temp"];
     float h = doc["humi"];
     display.clearDisplay();
     display.setTextSize(1);
     display.setCursor(0,0);
     display.println("SYSTEM NIEZALEZNY");
     display.drawLine(0, 10, 128, 10, WHITE);
     display.setCursor(0, 20);
     display.setTextSize(2);
     display.print("T: "); display.print(t, 1); display.println(" C");
     display.print("H: "); display.print(h, 0); display.println(" %");
     display.display();
   }
   http.end();
 }
 delay(2000);
}