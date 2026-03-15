#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char* ssid = "Sejf_Smart_System";
const char* pass = "haslo123";
const char* tajny_pin = "1234";
ESP8266WebServer server(80);
void miganieBledy() {
 for (int i = 0; i < 5; i++) {
   digitalWrite(LED_BUILTIN, LOW);
   delay(100);
   digitalWrite(LED_BUILTIN, HIGH);
   delay(100);
 }
}
String buildPage(String title, String content) {
 String html = "<!DOCTYPE html><html lang='pl'><head>";
 html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
 html += "<style>";
 html += "body { font-family: 'Segoe UI', sans-serif; background: #0f172a; color: #f8fafc; margin: 0; display: flex; align-items: center; justify-content: center; min-height: 100vh; }";
 html += ".container { background: #1e293b; padding: 2rem; border-radius: 24px; width: 90%; max-width: 400px; box-shadow: 0 20px 25px -5px rgba(0,0,0,0.3); border: 1px solid #334155; text-align: center; }";
 html += "h1 { font-size: 1.5rem; margin-bottom: 1.5rem; color: #38bdf8; }";
 html += ".btn { display: block; width: 100%; padding: 14px; margin: 10px 0; border-radius: 12px; font-weight: 600; cursor: pointer; border: none; font-size: 1rem; transition: 0.2s; text-decoration: none; box-sizing: border-box; }";
 html += ".btn-blue { background: #3b82f6; color: white; } .btn-blue:active { transform: scale(0.98); }";
 html += ".btn-red { background: #ef4444; color: white; }";
 html += ".btn-green { background: #10b981; color: white; }";
 html += "input { width: 100%; padding: 14px; margin: 15px 0; border-radius: 12px; border: 2px solid #334155; background: #0f172a; color: #fff; font-size: 1.5rem; text-align: center; outline: none; box-sizing: border-box; }";
 html += "input:focus { border-color: #3b82f6; }";
 html += "</style></head><body><div class='container'>";
 html += content;
 html += "</div></body></html>";
 return html;
}
void handleRoot() {
 String content = "<h1>Panel Sejfu</h1>";
 content += "<a href='/on' class='btn btn-blue'>WŁĄCZ ŚWIATŁO</a>";
 content += "<a href='/off' class='btn btn-red'>WYŁĄCZ ŚWIATŁO</a>";
 content += "<div style='margin: 20px 0; border-top: 1px solid #334155;'></div>";
 content += "<form action='/check' method='POST'>";
 content += "<input type='password' name='p' placeholder='KOD PIN' inputmode='numeric' maxlength='4' required>";
 content += "<button type='submit' class='btn btn-blue'>OTWÓRZ</button></form>";
 server.send(200, "text/html", buildPage("Sejf ESP", content));
}
void setup() {
 pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, HIGH);
 WiFi.softAP(ssid, pass);
 server.on("/", handleRoot);
 server.on("/on", []() {
   digitalWrite(LED_BUILTIN, LOW);
   server.sendHeader("Location", "/");
   server.send(303);
 });
 server.on("/off", []() {
   digitalWrite(LED_BUILTIN, HIGH);
   server.sendHeader("Location", "/");
   server.send(303);
 });
 server.on("/check", HTTP_POST, []() {
   if (server.arg("p") == tajny_pin) {
     digitalWrite(LED_BUILTIN, LOW);
     String success = "<h1>OTWARTE</h1><div style='font-size: 40px;'>🔓</div>";
     success += "<a href='/off' class='btn btn-green'>ZABLOKUJ</a>";
     server.send(200, "text/html", buildPage("Otwarto", success));
   } else {
     String error = "<h1 style='color: #ef4444;'>BŁĘDNY PIN</h1>";
     error += "<script>setTimeout(()=>window.location='/', 2000);</script>";
     server.send(200, "text/html", buildPage("Błąd", error));
     miganieBledy();
   }
 });
 server.begin();
}
void loop() {
 server.handleClient();
}