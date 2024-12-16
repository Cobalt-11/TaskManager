"Implementacija sustava za pamćenje zadataka s kružnim bufferom"
---
1. STRUKTURA PODATAKA (Statička biblioteka):
- Kružni buffer fiksne veličine (20 elemenata) s operacijama:
* Inicijalizacija buffera
* Dodavanje elementa
* Uklanjanje elementa
* Ispis sadržaja
* IsEmpty/IsFull provjere
---
2. STRUKTURA BUFFERA:
- Polje struktura zadataka (veličine 20)
- Pokazivač na početak (head)
- Pokazivač na kraj (tail)
- Brojač trenutnih elemenata
---
3. STRUKTURA ZADATKA:
- Naslov (max 50 znakova)
- Prioritet (enum: 1-Nizak, 2-Srednji, 3-Visok)
- Dan isteka (1-31)
- Mjesec isteka (1-12)
- Status (enum: 1-Aktivan, 2-Završen)
---
4. GLAVNA APLIKACIJA:
Osnovne funkcionalnosti:
- Unos novog zadatka
- Označavanje zadatka kao završenog
- Ispis svih aktivnih zadataka
- Ispis po prioritetu
- Izlaz iz programa
Dodatne funkcionalnosti (ako ostane vremena):
- Brisanje zadatka
- Pretraživanje po naslovu
- Ispis zadataka koji ističu u tekućem mjesecu
---
5. OBAVEZNI ZAHTJEVI:
- Validacija unosa podataka
- Provjera stanja buffera prije operacija
- Osnovno error handling
- Komentari za funkcije
---
6. ORGANIZACIJA PROJEKTA:
- task_manager/ (glavni direktorij)
* src/ (source datoteke)
* include/ (header datoteke)
* lib/ (statička biblioteka)
* obj/ (objektne datoteke)
* bin/ (izvršna datoteka)
---
## To-Do Lista:
- [x] **Napravljen header file circular_buffer** 
- [ ] **Napraviti header za task_manager** -- fali još pomocni dio i dodati struktur?



