![](battleship.png)

# Battleship
Projekt z przedmiotu Sieci komputerowe (2020 r.)

Autor: Mateusz Bąk\
Politechnika Poznańska, Wydział Informatyki

## Kompilacja

### Serwer - Linux
Wymagania:
- CMake 3.8
- Kompilator C++11
```
cmake -G "Unix Makefiles" .
make
```
Plik wykonywalny: `BattleshipServer/BattleshipServer`

### Klient - Windows
Wymagania:
- .NET Core 3.1 SDK
```
dotnet build -c Release
```
Plik wykonywalny: `BattleshipClient\bin\Release\netcoreapp3.1\BattleshipClient.exe`

## Protokół komunikacyjny
Komunikacja pomiędzy klientem a serwerem odbywa się poprzez protokół TCP. Wymieniane komunikaty mają postać komend tekstowych zakończonych znakiem nowej linii (`\n`).

#### Komendy wysyłane przez klienta:
- `match` - zgłoszenie chęci rozpoczęcia gry.\
Powoduje dodanie gracza do zbioru graczy oczekujących na rozgrywkę.
- `leave` - anulowanie matchmakingu / opuszczenie rozgrywki.\
Jeśli gracz jest obecnie w zbiorze graczy oczekujących, zostaje z niego usunięty. Jeśli jest w trakcie gry, opuszcza ją.
- `ships` - rozmieszczenie statków na planszy.\
Komenda posiada 3n argumentów, gdzie n jest liczbą statków do rozmieszczenia. Dla każdego statku podawane są kolejno dwie liczby oznaczające kolumnę i rząd lewej górnej komórki statku oraz znak `h` lub `v` oznaczający odpowiednio orientację poziomą lub pionową statku. Rozmiar statku wyznaczany jest na podstawie pozycji danej trójki argumentów zgodnie z ustaloną dla gry konfiguracją. Obecnie jedyną zaimplementowaną konfiguracją rozmiarów statków jest (5, 4, 3, 3, 2). Przykładowe użycie (odpowiadające rozmieszczeniu statków na zdjęciu powyżej):\
`ships 5 8 h 3 5 v 6 6 h 2 1 v 9 4 v`
- `fire` - oddanie strzału (wykonanie tury).\
Komenda posiada 2 argumenty: kolumnę i rząd wybranej przez gracza komórki na planszy. Komenda kończy turę gracza.

#### Komendy wysyłane przez serwer:
- `matchmaking` - potwierdzenie powodzenia komendy `match`.
- `left` - potwierdzenie powodzenia komendy `leave`.
- `ready` - potwierdzenie powodzenia komendy `ships`.
- `miss` - potwierdzenie powodzenia komendy `fire`, przeciwnik nie został trafiony.
- `hit` - potwierdzenie powodzenia komendy `fire`, przeciwnik został trafiony.
- `sunk` - potwierdzenie powodzenia komendy `fire`, statek przeciwnika został zatopiony.
- `opponent ready` - powiadomienie o gotowości przeciwnika.
- `opponent left` - powiadomienie o opuszczeniu gry przez przeciwnika.
- `start` - powiadomienie o rozpoczęciu gry (faza przygotowania).
- `turn` - powiadomienie o rozpoczęciu tury.
- `win` - powiadomienie o wygranej.
- `lose` - powiadomienie o przegranej.
- `draw` - powiadomienie o remisie.
- `Invalid command` - powiadomienie o błędzie w odebranej komendzie.
