#!/bin/bash

# Compile object files
gcc -O3 -Wall -I./include -c ./src/circular_buffer.c -o ./obj/circular_buffer.o
gcc -O3 -Wall -I./include -c ./src/task_manager.c -o ./obj/task_manager.o
gcc -O3 -Wall -I./include -c ./src/main.c -o ./obj/main.o

# Create static library
ar rcs ./lib/libkv_project.a ./obj/circular_buffer.o ./obj/task_manager.o ./obj/main.o

# Link object files and static library to create executable
gcc -O3 -Wall -I./include -o ./bin/Run ./obj/main.o ./lib/libkv_project.a
