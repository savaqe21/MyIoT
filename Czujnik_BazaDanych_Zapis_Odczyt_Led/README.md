### Cześć! 👋

🌐 IoT Data Logger: ESP8266 + PHP + MySQL </br>
Zaawansowany system zbierania i monitorowania danych środowiskowych w czasie rzeczywistym. 
Projekt realizuje pełny obieg informacji: od fizycznego pomiaru czujnikiem, przez zapis w relacyjnej bazie danych MariaDB, 
aż po zwrotne sterowanie elementami wykonawczymi (LED).

🏗️ Architektura Systemu

- Hardware (Edge): ESP8266 pobiera dane z czujnika DHT11 i wyświetla je na ekranie OLED SSD1306.
- Backend (API): Skrypt PHP odbiera dane metodą POST, identyfikuje urządzenie po deviceId i zarządza komunikacją z bazą danych.
- Database: Struktura MySQL/MariaDB z trzema powiązanymi tabelami:
  - tboard: rejestr urządzeń.
  - treadings: historia pomiarów (temperatura/wilgotność).
  - tresponses: sterowanie (np. stan diody LED wysyłany zwrotnie do urządzenia).

🚀 Kluczowe Funkcjonalności

- Dwukierunkowa komunikacja: ESP8266 wysyła dane sensorów, a w odpowiedzi JSON otrzymuje instrukcje sterujące (np. led_state) oraz aktualny czas serwera.
- Relacyjna baza danych: Wykorzystanie kluczy obcych (fkBoard) do powiązania tysięcy odczytów z konkretną płytką.
- Odporność na błędy: Obsługa błędów parsowania JSON, błędów odczytu czujnika oraz problemów z połączeniem HTTP.
- Podgląd lokalny: Wyświetlanie statusu połączenia i wyników pomiarów bezpośrednio na ekranie OLED.

🛠️ Technologie

- Języki: C++ (Arduino), PHP 8.x, SQL. </br>
- Baza danych: MariaDB (XAMPP/localhost). </br>
- Biblioteki: ArduinoJson, Adafruit_SSD1306, DHT sensor library.
