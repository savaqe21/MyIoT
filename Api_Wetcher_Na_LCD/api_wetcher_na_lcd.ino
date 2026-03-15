#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Ustawienia OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// Dane WiFi
const char* ssid = "iot";
const char* password = "iotinternet";
// Dane OpenWeatherMap
String apiKey = "40...09"; // Klucz API
String city = "Gdynia";
String countryCode = "PL";
void setup() {
 Serial.begin(115200);
 // Inicjalizacja wyświetlacza
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
   Serial.println(F("Nie znaleziono OLED"));
   for(;;);
 }
 display.clearDisplay();
 display.setTextColor(WHITE);
 display.setTextSize(1);
 display.setCursor(0,0);
 display.println("Laczenie z WiFi...");
 display.display();
 // Łączenie z WiFi
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 display.clearDisplay();
 display.setCursor(0,0);
 display.println("Polaczono!");
 display.display();
 delay(1000);
}
void loop() {
 if (WiFi.status() == WL_CONNECTED) {
   WiFiClient client;
   HTTPClient http;
   // URL do API
   String url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&units=metric&appid=" + apiKey;
   http.begin(client, url);
   int httpCode = http.GET();
   if (httpCode > 0) {
     String payload = http.getString();
     // Parsowanie JSON
     DynamicJsonDocument doc(1024);
     deserializeJson(doc, payload);
     float temp = doc["main"]["temp"];
     int humi = doc["main"]["humidity"];
     String desc = doc["weather"][0]["description"];
     // Wyświetlanie na OLED
     display.clearDisplay();
     // Nagłówek
     display.setTextSize(1);
     display.setCursor(0,0);
     display.println("POGODA: GDYNIA");
     display.drawLine(0, 10, 128, 10, WHITE);
     // Temperatura
     display.setTextSize(2);
     display.setCursor(0, 20);
     display.print(temp, 1);
     display.print(" C");
     // Wilgotność i opis
     display.setTextSize(1);
     display.setCursor(0, 45);
     display.print("Wilg: "); display.print(humi); display.println("%");
     display.print(desc);
     display.display();
   }
   http.end();
 }
 delay(60000); // Pobieraj dane co 1 minutę
}