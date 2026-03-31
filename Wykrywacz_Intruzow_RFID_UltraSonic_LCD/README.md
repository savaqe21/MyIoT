# 🛡️ IoT Smart Alarm System (ESP8266 + RFID + Ultrasonic)

Dwumodułowy, inteligentny system alarmowy oparty na mikrokontrolerach ESP8266, wykorzystujący komunikację bezprzewodową **ESP-NOW**.
Projekt realizuje scenariusz ochrony pomieszczenia z autoryzacją dostępu za pomocą technologii RFID.

## 📋 Funkcje Systemu
* **Detekcja bezkontaktowa**: Wykorzystanie czujnika ultradźwiękowego do monitorowania przestrzeni (zasięg 50 cm).
* **Architektura rozproszona**: Podział na jednostkę sondującą (Strażnik) oraz jednostkę sterującą (Terminal).
* **Bezprzewodowa komunikacja**: Natychmiastowa wymiana danych przez protokół ESP-NOW (nie wymaga routera WiFi).
* **Autoryzacja RFID**: Rozbrajanie systemu za pomocą unikalnego UID karty/breloka.
* **System kar czasowych**: Intruz ma 30 sekund na autoryzację. Każda próba użycia błędnej karty odejmuje 5 sekund od pozostałego czasu.
* **Interfejs OLED**: Wyświetlanie statusu systemu, czasu do alarmu oraz komunikatów o błędach w czasie rzeczywistym.

## 🏗️ Architektura Sprzętowa

### 1. Jednostka A: Strażnik (Sensor Node)
* **Mikrokontroler**: ESP8266 (NodeMCU/LoLin)
* **Czujnik**: HC-SR04 (Ultradźwiękowy miernik odległości)
* **Sygnalizator**: Buzzer aktywny (Low Level Trigger)

### 2. Jednostka B: Terminal (Control Node)
* **Mikrokontroler**: ESP8266 (NodeMCU/LoLin)
* **Czytnik**: RFID-RC522 (13.56 MHz)
* **Wyświetlacz**: OLED 0.96" SSD1306 (I2C)

## 🔧 Połączenia (Pinout)

### Terminal (ESP + RFID + OLED)
| RFID RC522 | ESP8266 | OLED SSD1306 | ESP8266 |
|------------|---------|--------------|---------|
| SDA (SS)   | D8      | VCC          | 3V3     |
| SCK        | D5      | GND          | GND     |
| MOSI       | D7      | SCL          | D1      |
| MISO       | D6      | SDA          | D2      |
| RST        | D3      |              |         |
| 3.3V       | 3V3     |              |         |

### Strażnik (ESP + Ultrasonic + Buzzer)
| Element    | Pin ESP |
|------------|---------|
| Trig       | D1      |
| Echo       | D2      |
| Buzzer I/O | D5      |
| VCC (HC-SR04)| VIN (5V)|

## 🚀 Logika Działania (Scenariusz)
1.  **Czuwanie**: Strażnik mierzy odległość, Terminal wyświetla "SYSTEM UZBROJONY".
2.  **Wykrycie**: Intruz przecina wiązkę (<50cm). Strażnik wysyła sygnał do Terminala i zaczyna pulsacyjnie pikać.
3.  **Autoryzacja**: Terminal uruchamia odliczanie (30s). 
    * **Poprawna karta**: System wraca do czuwania, buzzer milknie.
    * **Błędna karta**: Skrócenie czasu o 5 sekund.
4.  **Alarm**: Po upływie czasu lub wielokrotnych błędach, Terminal wysyła sygnał wymuszający ciągły alarm dźwiękowy.
