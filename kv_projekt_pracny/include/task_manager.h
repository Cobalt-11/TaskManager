//header guard
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include "circular_buffer.h"


// Funkcija za glavni meni
void showMainMenu();

// Funkcija za unos novog zadatka
void addTask(circular_buffer* cb);

// Funkcija za prikaz zadataka
void displayTasks(circular_buffer* cb);

// Funkcija za označavanje zadatka kao završenog
void markTaskCompleted(circular_buffer* cb, int taskIndex);

// Funkcija za brisanje zadatka
void deleteTask(circular_buffer* cb, int taskIndex);

// Funkcija za validaciju datum formata
int validateDate(const char* date);

//Funkcija za validaciju user inputa
int validateInput(const char* input, int type);

// Funcija za sortiranje "task" po prioritetu
void sortTasksByPriority(circular_buffer* cb);

// Funkcija za formatiranje i ispis detalja zadatka
void formatTaskDisplay(taskStruct* task);

// Funkcija za učitavanje zadataka iz datoteke
int loadTasksFromFile(const char* filename, circular_buffer* cb);

// Funkcija za spremanje zadataka u datoteku
int saveTasksToFile(const char* filename, circular_buffer* cb);

// Funkcija za filtriranje zadataka po statusu
void filterTasksByStatus(circular_buffer* cb, taskStatus status);

#endif
//End header guard
