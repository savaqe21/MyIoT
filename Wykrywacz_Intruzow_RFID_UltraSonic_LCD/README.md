### Cześć! 👋

🛡️ IoT Smart Alarm System: ESP8266 + RFID + Ultrasonic </br>
Dwumodułowy, inteligentny system alarmowy oparty na bezprzewodowej komunikacji ESP-NOW. 
Projekt realizuje kompletny scenariusz ochrony mienia: od detekcji intruza czujnikiem ultradźwiękowym, 
przez autoryzację zbliżeniową RFID, aż po zaawansowaną logikę kar czasowych i powiadomień wizualnych.

🏗️ Architektura Systemu

- **Jednostka A (Strażnik)**: NodeMCU pełniący rolę sensora. Monitoruje przestrzeń (HC-SR04) i zarządza sygnalizacją dźwiękową (Buzzer).
- **Jednostka B (Terminal)**: Główny węzeł sterujący. Obsługuje autoryzację użytkownika (RFID-RC522) oraz interfejs graficzny (OLED).
- **Komunikacja (ESP-NOW)**: Bezpośrednia wymiana danych między jednostkami bez pośrednictwa routera WiFi, zapewniająca minimalne opóźnienia.

🚀 Kluczowe Funkcjonalności

- **Inteligentna Detekcja**: Monitorowanie strefy w zasięgu 50 cm z natychmiastowym przesyłaniem statusu do terminala.
- **System Autoryzacji**: Rozbrajanie systemu za pomocą unikalnego UID karty/breloka z dynamicznym odliczaniem czasu (30s).
- **Mechanizm Kar Czasowych**: Każda próba użycia nieuprawnionej karty skraca czas na rozbrojenie o 5 sekund, zwiększając bezpieczeństwo.
- **Interfejs Real-time**: Wyświetlanie statusu uzbrojenia, pozostałego czasu oraz alertów o błędach bezpośrednio na ekranie OLED.

🛠️ Technologie

- **Języki**: C++ (Arduino). </br>
- **Protokół**: ESP-NOW (Low-latency wireless). </br>
- **Biblioteki**: SPI, MFRC522, Adafruit_SSD1306, ESP8266WiFi.

| ![IMG_2666](https://github.com/user-attachments/assets/66d152da-6e6d-421f-a85a-246338302dc5) |
| :---: |
| ![IMG_2669](https://github.com/user-attachments/assets/86c73ce8-35c1-497b-aa5b-2d7e3e2ff92d) |
| ![IMG_2668](https://github.com/user-attachments/assets/3e426560-4164-4e1c-ac43-1e9d0d578462) |
| ![IMG_2667](https://github.com/user-attachments/assets/590961d1-7107-465b-bf87-c96dd6a24217) |
