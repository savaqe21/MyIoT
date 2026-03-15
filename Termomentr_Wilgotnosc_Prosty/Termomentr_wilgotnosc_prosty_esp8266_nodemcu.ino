#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// Konfiguracja sieci WiFi
const char* ssid = "Termometr_Prosty";
const char* pass = "haslo123";
ESP8266WebServer server(80);
void handleRoot() {
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 String html = "<!DOCTYPE html><html lang='pl'><head>";
 html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
 html += "<meta http-equiv='refresh' content='5'>";
 html += "<style>";
 html += "body { font-family: sans-serif; background: #0f172a; color: #f8fafc; display: flex; align-items: center; justify-content: center; min-height: 100vh; margin: 0; }";
 html += ".card { background: #1e293b; padding: 2rem; border-radius: 20px; box-shadow: 0 10px 30px rgba(0,0,0,0.5); text-align: center; border: 1px solid #334155; }";
 html += "h1 { color: #38bdf8; font-size: 1.2rem; margin-bottom: 20px; }";
 html += ".val { font-size: 3rem; font-weight: bold; color: #fff; }";
 html += ".unit { font-size: 1.5rem; color: #38bdf8; }";
 html += ".error { color: #ef4444; font-weight: bold; }";
 html += "</style></head><body>";
 html += "<div class='card'>";
 html += "<h1>ODCZYT Z PINU D5</h1>";
 if (isnan(h) || isnan(t)) {
   html += "<p class='error'>Błąd odczytu czujnika!</p>";
   html += "<p style='font-size: 0.8rem;'>Sprawdź połączenie z pinem D5</p>";
 } else {
   html += "<div><span class='val'>" + String(t, 1) + "</span><span class='unit'>°C</span></div>";
   html += "<div style='margin-top: 15px;'><span class='val'>" + String(h, 0) + "</span><span class='unit'>%</span></div>";
 }
 html += "</div></body></html>";
 server.send(200, "text/html", html);
}
void setup() {
 // Rozpoczęcie pracy czujnika
 dht.begin();
 // Konfiguracja Access Pointa
 WiFi.mode(WIFI_AP);
 WiFi.softAP(ssid, pass);
 // Reakcja na wejście na stronę
 server.on("/", handleRoot);
 // Start serwera
 server.begin();
}
void loop() {
 server.handleClient();
}