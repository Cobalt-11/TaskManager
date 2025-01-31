---
# Task Manager - Implementacija sustava za pamćenje zadataka s kružnim bufferom

## 1. Naslovna stranica

- **SVEUČILIŠTE JOSIPA JURAJA STROSSMAYERA U OSIJEKU**
  **ELEKTROTEHNIČKI FAKULTET OSIJEK**
- **Autor:** Patrik Pracny
- **Datum izrade dokumentacije:** 30.1.2025. Osijek
- **Verzija aplikacije:** 1.0
- **Projektni zadatak**

## 2. Uvod

### 2.1. Svrha projekta
Projekt je izrađen kako bi omogućio efikasno upravljanje zadacima pomoću kružnog buffera. Rješava problem ograničenog kapaciteta memorije i omogućuje brzo dodavanje, uklanjanje i pregled zadataka bez potrebe za kompleksnim strukturama podataka.

### 2.2. Ciljevi
- Implementirati sustav za pohranu i upravljanje zadacima.
- Koristiti kružni buffer kako bi se osigurala optimizacija memorijskog prostora.
- Omogućiti validaciju unosa i osnovno rukovanje greškama.

### 2.3. Opis problema
U mnogim aplikacijama za upravljanje zadacima javlja se potreba za fiksnim brojem unosa koji se recikliraju nakon popunjavanja kapaciteta. Ovaj projekt omogućava efikasno rukovanje takvim podacima koristeći kružni buffer.

## 3. Opis projekta

### 3.1. Glavne komponente
- **Statička biblioteka** – Implementacija kružnog buffera.
- **Glavna aplikacija** – Interakcija s korisnikom i upravljanje zadacima.
- **Podatkovne strukture** – Struktura za spremanje zadataka i manipulacija njima.

### 3.2. Funkcionalnosti
**Osnovne funkcionalnosti:**
- Unos novog zadatka
- Označavanje zadatka kao završenog
- Ispis svih zadataka
- Ispis po prioritetu
- Izlaz iz programa
- Brisanje zadataka
- Brisanje cijelog buffera
- Spremanje zadataka u datoteku "tasks.txt"

### 3.3. Struktura direktorija
```
kv_projekt/
│── src/         # Izvorni kod aplikacije (.c datoteke)
│── include/     # Header datoteke za deklariranje funkcija i struktura
│── lib/         # Statička biblioteka s implementacijom kružnog buffera (.a ili .lib)
│── obj/         # Objektne datoteke generirane tijekom kompilacije
│── bin/         # Izvršna datoteka aplikacije
```

## 4. Instalacija i pokretanje

Za preuzimanje izvornog koda koristite naredbu:
```sh
git clone https://gitlab.com/dock7713840/np_kv_projekt24.git
cd np_kv_projekt24
cd kv_projekt_pracny
```

Provjera GCC kompajlera:
```sh
gcc --version
```
U slučaju da gcc nije instaliran, instalirajte ga pomoću:
```sh
apt install gcc
```

Stvaranje potrebnih direktorija:
```sh
mkdir bin lib obj
```

Kompilacija:
```sh
gcc -O3 -Wall -I./include -c ./src/circular_buffer.c -o ./obj/circular_buffer.o
gcc -O3 -Wall -I./include -c ./src/task_manager.c -o ./obj/task_manager.o
gcc -O3 -Wall -I./include -c ./src/main.c -o ./obj/main.o
```

Stvaranje statičke biblioteke:
```sh
ar rcs ./lib/lib_project.a ./obj/circular_buffer.o ./obj/task_manager.o ./obj/main.o
```

Generiranje izvršne datoteke:
```sh
gcc -O3 -Wall -I./include -o ./bin/Run ./obj/main.o ./lib/lib_project.a
```

Pokretanje aplikacije:
```sh
./bin/Run
```

## 5. Tehnički detalji

### 5.1. Opis podataka
- **Struktura buffera** – Polje struktura zadataka (20 elemenata), pokazivači `head` i `tail`, brojač trenutnog broja zadataka.
- **Struktura zadatka** – Naslov, prioritet, datum isteka, status.

### 5.2. Glavne funkcije
- `initBuffer()` – Inicijalizacija buffera.
- `addTask()` – Dodavanje novog zadatka.
- `removeTask()` – Uklanjanje najstarijeg zadatka.
- `printTasks()` – Ispis trenutnih zadataka.
- `isEmpty()` / `isFull()` – Provjera statusa buffera.

### 5.3. Važni algoritmi
- **Kružni buffer** – Efikasna struktura podataka koja koristi pokazivače za optimizaciju dodavanja i uklanjanja elemenata.
- **Sortiranje po prioritetu** – Omogućuje ispis zadataka prema važnosti.

## 6. Zaključak

Projekt "Task Manager" omogućuje efikasno upravljanje zadacima koristeći kružni buffer. Implementacija osigurava optimizirano korištenje memorije, jednostavnost korištenja i modularnost koda.

**Moguća buduća poboljšanja:**
- Dodavanje grafičkog sučelja za korisnike.
- Dodavanje algoritama pretraživanja i filtriranja zadataka.
