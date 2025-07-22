# Task Manager - Implementacija sustava za pamćenje zadataka s kružnim bufferom

## 1. Instalacija i pokretanje

Za preuzimanje izvornog koda koristite naredbu:
```sh
git clone https://github.com/Cobalt-11/TaskManager.git
cd np_kv_projekt24
cd kv_projekt_pracny
```

Provjera GCC kompajlera:
```sh
gcc --version
```
U slučaju da gcc nije instaliran, instalirajte ga pomoću (u ovom slučaju koristi se Ubuntu distribucija, **za drugu distribuciju ova komanda je drugačija**):
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

---
