//header guard
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include "circular_buffer.h"

// Funkcija za glavni meni
void showMainMenu();

// Funkcija za unos novog zadatka
void addTask();

// Funkcija za prikaz zadataka
void displayTasks(circular_buffer *cb);

// Funkcija za odabir zadatka
void selectTask(circular_buffer *cb, int taskIndex, Task *task);


// Funkcija za označavanje zadatka kao završenog
void markTaskCompleted(Task *task);

// Funkcija za brisanje zadatka
void deleteTask(circular_buffer *cb, int taskIndex);

//pomocne funkcije
// Validation function for date format (YYYY-MM-DD)
int validateDate(const char* date);

// Validation function for user input (checks for valid integers, strings, etc.)
int validateInput(const char* input, int type);

// Function to format and display task details neatly
void formatTaskDisplay(Task* task);

// Function to sort tasks by priority (ascending order)
void sortTasksByPriority();

int getCount(circular_buffer *cb);

Task* getElement(circular_buffer *cb, int index);

//Funckije za spremanje i učitavanje task-ova

void saveTasksToFile(circular_buffer *cb, const char *filename);

void loadTasksFromFile(circular_buffer *cb, const char *filename);


#endif
//End header guard
