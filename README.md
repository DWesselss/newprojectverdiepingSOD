# Reaction Lab

Reaction Lab is een C++ terminal project waarin je reactietijd en accuracy kan trainen.
Het project is gemaakt als schoolproject en laat meerdere C++ onderdelen zien.

## Features

- Terminal menu
- Reactietijd test met random wachttijd
- Accuracy trainer met random letters
- Naam aanpassen via het menu
- High scores bekijken via het menu
- High scores worden opgeslagen in CSV-bestanden
- Scores blijven bewaard nadat je het programma afsluit
- Session statistieken
- ANSI kleuren in de terminal
- Meerdere classes
- Meerdere `.cpp` en `.hpp` bestanden
- CMake build systeem
- Automatisch macOS Finder-icoon na build (op Mac)

## Waar worden de high scores opgeslagen?

De scores worden automatisch opgeslagen in de map:

```bash
data/
```

Daarin komen deze bestanden:

```bash
reaction_scores.csv
accuracy_scores.csv
```

Deze bestanden worden aangemaakt zodra je een test speelt.
Je kan ze openen met bijvoorbeeld Excel, Numbers, LibreOffice Calc of gewoon met een teksteditor.

In het programma zelf kan je de opgeslagen scores terugvinden via:

```text
3. High Scores bekijken
```

## Build op macOS / Linux

Open de map in Terminal en voer uit:

```bash
mkdir build
cd build
cmake ..
make
./reaction_lab
```

## macOS icoon automatisch toepassen

Op **Mac** wordt na het builden automatisch geprobeerd om een custom Finder-icoon op de executable te zetten.
Dat gebeurt via:

- `scripts/apply_macos_icon.sh`
- `resources/reaction_lab_cover.png`

Het icoon wordt dus automatisch toegepast op:

```bash
build/reaction_lab
```

### Belangrijk

Hiervoor heb je meestal **Xcode Command Line Tools** nodig.
Als het icoon niet gezet wordt, run dan eenmalig:

```bash
xcode-select --install
```

Daarna opnieuw builden.

## Build in VS Code

1. Open de map `reaction_lab_cpp`
2. Installeer eventueel CMake Tools
3. Open een terminal
4. Run:

```bash
mkdir build
cd build
cmake ..
make
./reaction_lab
```

## Wat je kan zeggen tegen de docent

Ik heb een terminal-based reaction trainer gemaakt in C++.
De applicatie gebruikt classes, structs, vectors, file handling, random getallen,
chrono timers en een menu-systeem. Scores worden opgeslagen in CSV-bestanden,
waardoor high scores blijven bestaan nadat het programma is afgesloten.

Ook heb ik een menu-optie toegevoegd waarmee je na het invullen alsnog je naam kan aanpassen.
Daarnaast heb ik voor Mac een automatische post-build stap toegevoegd die een custom Finder-icoon op de executable probeert te zetten.

## Bestanden

- `main.cpp` bevat het hoofdmenu en de optie om je naam aan te passen
- `Game.cpp` bevat de reaction test en accuracy trainer
- `Storage.cpp` bevat opslaan en laden van scores
- `Utils.cpp` bevat handige functies zoals kleuren, random en input checks
- `scripts/apply_macos_icon.sh` zet op Mac automatisch een icoon op de executable
- `resources/reaction_lab_cover.png` is de bronafbeelding voor het icoon
