### Cześć! 👋

🌦️ ESP8266 Weather Station (OLED) </br>
Inteligentna stacja pogodowa oparta na module ESP8266, która pobiera dane w czasie rzeczywistym z serwisu OpenWeatherMap. 
Projekt wyświetla aktualną temperaturę, wilgotność oraz krótki opis pogodowy dla Gdyni na wyświetlaczu OLED SSD1306.

🛠️ Specyfikacja techniczna

- Hardware: ESP8266 (np. NodeMCU), wyświetlacz OLED 128x64 (I2C).
- Komunikacja: WiFi (klient HTTP), JSON API.
- Biblioteki: ESP8266WiFi, ArduinoJson, Adafruit_SSD1306, Adafruit_GFX.

⚙️ Konfiguracja

Aby uruchomić projekt, należy uzupełnić własny apiKey z OpenWeatherMap oraz dane do domowej sieci WiFi w kodzie źródłowym. 
Dane są odświeżane automatycznie co 60 sekund.

| ![IMG_2642](https://github.com/user-attachments/assets/d63e5edb-3f75-457a-9d67-672c62d2c15c) |
| :---: |
