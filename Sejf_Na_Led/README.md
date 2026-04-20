### Cześć! 👋

🔐 Smart Safe System (ESP8266) </br>
Interaktywny system kontroli dostępu do sejfu oparty na module ESP8266. 
Urządzenie działa jako niezależny punkt dostępowy (SoftAP) i serwuje zabezpieczony panelem PIN interfejs webowy, 
który pozwala na zdalne ryglowanie zamka oraz sterowanie oświetleniem.

🛠️ Główne funkcje

- Autoryzacja kodem PIN: Dostęp do funkcji "Otwórz" chroniony 4-cyfrowym hasłem sprawdzanym po stronie serwera.
- Interfejs Web Premium: Nowoczesny, responsywny design (Dark Mode) zbudowany w HTML5 i CSS3, dostosowany do urządzeń mobilnych.
- Informacja zwrotna: System wizualnie sygnalizuje błędny kod PIN poprzez sekwencję migania diody LED na module.
- Sterowanie oświetleniem: Funkcja włączania/wyłączania światła (lub innego peryferium) bezpośrednio z poziomu przeglądarki.

⚙️ Specyfikacja techniczna

- Biblioteki: ESP8266WiFi, ESP8266WebServer.
- Bezpieczeństwo: Przesyłanie kodu PIN metodą HTTP POST, obsługa przekierowań (303) oraz prosta walidacja danych.
- Logika: Dynamiczne budowanie stron HTML wewnątrz pamięci mikrokontrolera.

<img src="https://github.com/user-attachments/assets/f54fb18f-51b9-4eaa-9937-8d1597f86feb" width="300">
<img src="https://github.com/user-attachments/assets/325c3038-40be-43fb-af9b-01ecdf8d98e7" width="300">
<img src="https://github.com/user-attachments/assets/257acf58-eb05-41de-b9b8-8b3c37299a03" width="300">

<!--
| ![IMG_2649](https://github.com/user-attachments/assets/257acf58-eb05-41de-b9b8-8b3c37299a03) |
| :---: |
| ![IMG_2644](https://github.com/user-attachments/assets/f54fb18f-51b9-4eaa-9937-8d1597f86feb) |
| ![IMG_2641](https://github.com/user-attachments/assets/325c3038-40be-43fb-af9b-01ecdf8d98e7) |
-->
