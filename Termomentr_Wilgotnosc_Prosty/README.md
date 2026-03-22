### Cześć! 👋

🌡️ Termometr Web (SoftAP + DHT11) </br>
Lokalna stacja pomiarowa oparta na module ESP8266 i czujniku DHT11. 
Urządzenie tworzy własną sieć WiFi (Access Point), udostępniając responsywny panel webowy z aktualnymi odczytami temperatury
i wilgotności bezpośrednio pod adresem IP modułu.

🛠️ Specyfikacja techniczna

- Hardware: ESP8266, czujnik temperatury i wilgotności DHT11 (podpięty pod pin D5).
- Tryb pracy: SoftAP (urządzenie działa jako router/hotspot).
- Interfejs: Serwer HTTP serwujący dynamiczny dokument HTML5/CSS3 z funkcją auto-odświeżania co 5 sekund.
- Biblioteki: ESP8266WiFi, ESP8266WebServer, DHT sensor library.

📱 Jak się połączyć?

Połącz się z siecią WiFi o nazwie: Termometr_Prosty.

Wpisz hasło: haslo123.

W przeglądarce wpisz adres: 192.168.4.1.
