#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <ArduinoJson.h>
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// Konfiguracja AP
const char* ssid = "Stacja_Pogodowa";
const char* pass = "haslo123";
ESP8266WebServer server(80);
void handleData() {
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 StaticJsonDocument<200> doc;
 doc["temp"] = isnan(t) ? 0 : t;
 doc["humi"] = isnan(h) ? 0 : h;
 String response;
 serializeJson(doc, response);
 server.send(200, "application/json", response);
}
void setup() {
 Serial.begin(115200);
 dht.begin();
 // Ustawienie trybu Access Point
 WiFi.mode(WIFI_AP);
 WiFi.softAP(ssid, pass);
 Serial.println("Serwer AP uruchomiony!");
 Serial.print("IP Serwera: ");
 Serial.println(WiFi.softAPIP()); // Domyślnie 192.168.4.1
 server.on("/pogoda", handleData);
 server.begin();
}
void loop() {
 server.handleClient();
}