### Cześć! 👋

🌐 Rozproszony System Pogodowy (ESP-to-ESP) </br>
Zaawansowany projekt IoT realizujący bezprzewodową komunikację między dwoma modułami ESP8266 bez użycia zewnętrznego routera. 
System dzieli się na stację pomiarową (Serwer) oraz zdalny terminal wyświetlający (Klient).

🛰️ Struktura Projektu

Moduł 1 (Serwer AP): Odczytuje dane z czujnika DHT11 (pin D5) i udostępnia je w formacie JSON pod endpointem /pogoda. 
Działa jako niezależny punkt dostępowy (Access Point).

Moduł 2 (Klient): Łączy się z siecią WiFi serwera, pobiera dane przez HTTP GET, parsuje JSON-a 
i prezentuje wyniki (temperatura i wilgotność) na wyświetlaczu OLED SSD1306.

🛠️ Technologie

- Komunikacja: Protokół HTTP, format danych JSON (biblioteka ArduinoJson).
- Sieć: Tryb SoftAP na serwerze, automatyczna rekonfiguracja WiFi na kliencie.
- Hardware: 2x ESP8266, DHT11, OLED 128x64 I2C.

![IMG_2646](https://github.com/user-attachments/assets/c81005f9-6dfd-4e7e-be07-ef6efee91c15)
