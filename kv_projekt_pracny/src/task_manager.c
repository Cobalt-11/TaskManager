#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "task_manager.h"

// Funkcija za glavni meni
//treba viditi da li je ovo ovako oke?

// potencijano dodati izborni meni koji se dobije tek kada odaberem task iz liste
//npr imam 3 taska --> odaberem 2. task i onda mi samo njega ispise na meni, i ako je active da mi ponudi opciju
//da ka markam kao finished, u suprotnom nema opcije i dodati opciju za brisanje tog taska
void showMainMenu() {
    printf("\n===== Glavni Meni =====\n");
    printf("1. Dodaj novi zadatak\n");
    printf("2. Prikaži zadatke\n");
    printf("3. Spremi u tasks.txt\n");
    printf("4. Očisti buffer.\n");
    printf("5. Izlaz\n");
    printf("=======================\n");
    printf("Odabir: ");
}

// Funkcija za unos novog zadatka
void addTask(circular_buffer *cb) {
    if (isFull(cb)) {
        printf("Buffer je pun! Ne možete dodati novi zadatak.\n");
        return;
    }

    Task newTask;
    printf("Unesite naslov zadatka (maks. %d znakova): ", MAX_TITLE_LENGTH);
    scanf(" %[^\n]", newTask.title); // Učitavanje stringa s razmakom
    printf("Odaberite prioritet (1 - LOW, 2 - MEDIUM, 3 - HIGH): ");
    int priority;
    scanf("%d", &priority);
    newTask.priority = (priorityLevel)priority;

    printf("Unesite dan: ");
    scanf("%hd", &newTask.day);
    printf("Unesite mjesec: ");
    scanf("%hd", &newTask.month);

    printf("Odaberite status (1 - ACTIVE, 2 - FINISHED): ");
    int status;
    scanf("%d", &status);
    newTask.status = (TaskStatus)status;

    addElement(cb, &newTask); // Dodavanje zadatka u kružni buffer
    printf("Zadatak uspješno dodan.\n");
}

// Funkcija za prikaz zadataka
void displayTasks(circular_buffer *cb) {
    if (isEmpty(cb)) {
        printf("Nema zadataka za prikaz.\n");
        return;
    }

    sortTasksByPriority(cb); //Sortiranje prije ispisa

    printf("\n===== Zadaci =====\n");
    printBuffer(cb); // Koristi funkciju za ispis zadataka
    printf("==================\n");

    while (1) {
        int taskIndex;
        printf("Odaberite broj zadatka (0 za povratak): ");
        scanf("%d", &taskIndex);

        // Povratak u glavni meni
        if (taskIndex == 0) {
            printf("Povratak u glavni meni.\n");
            break;
        }

        // Provjera je li unos ispravan
        if (taskIndex <= 0 || taskIndex > getCount(cb)) {
            printf("Neispravan odabir. Pokušajte ponovo.\n");
            continue;
        }

        // Dohvaćanje odabranog zadatka
        Task *selectedTask = getElement(cb, taskIndex - 1); // Indeksiranje od 0
        if (selectedTask == NULL) {
            printf("Došlo je do greške prilikom dohvaćanja zadatka.\n");
            continue;
        }

        // Prikaz detalja odabranog zadatka
        selectTask(cb, taskIndex, selectedTask);
    }
}


void selectTask(circular_buffer *cb, int taskIndex, Task *selectedTask) {
    if (selectedTask == NULL) {
        printf("Neispravan zadatak.\n");
        return;
    }

    while (1) {
        printf("\n===== Detalji zadatka =====\n");
        printf("Naslov: %s\n", selectedTask->title);
        printf("Prioritet: %d\n", selectedTask->priority);
        printf("Datum: %02d/%02d\n", selectedTask->day, selectedTask->month);
        printf("Status: %s\n", (selectedTask->status == ACTIVE) ? "ACTIVE" : "FINISHED");
        printf("===========================\n");

        printf("1. Označi kao dovršen\n");
        printf("2. Obriši zadatak\n");
        printf("3. Povratak\n");
        printf("Odabir: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Nevažeći unos. Pokušajte ponovo.\n");
            return;
        }

        switch (choice) {
            case 1:
                if (selectedTask->status == FINISHED) {
                    printf("Zadatak je već dovršen.\n");
                } else {
                    selectedTask->status = FINISHED;
                    printf("Zadatak je označen kao dovršen.\n");
                }
                break;
            case 2:
                deleteTask(cb, taskIndex);
            	printf("Zadatak uspješno obrisan");
                return; // Exit after deleting the task
            case 3:
                return; // Exit to the previous menu
            default:
                printf("Nevažeći odabir. Pokušajte ponovo.\n");
        }
    }
}


// two type of  TaskStatus --> ACTIVE & FINISHED <-- i need to access Task then
// i need to get what is status of that Task --- and if status is FINISHED "2", i need to ignore it, or
// if its active i need to be able to change a task
void markTaskCompleted(Task *task) {
    if(task -> status == FINISHED) { //2 predstavlja finised task
        printf("Zadatak je već završen. \n");
        return;
    }
    else {
        task -> status = FINISHED;
        printf("Zadatak '%s' je označen kao dovršen.\n", task -> title);
    }
    
    
}



// POMOCNE FUNKCIJE

int validateDate(const char* date) {
    //Provjeri da li je datum u korektnom formatu
    if (strlen(date) != 10) return 0; // Duzina datuma bi trebala biti 10 

    if (date[4] != '-' || date[7] != '-') return 0;

    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && !isdigit(date[i])) {
            return 0;
        }
    }

    int year, month, day;
    sscanf(date, "%4d-%2d-%2d", &year, &month, &day);

    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return 0;
    if (month == 2) {
        if (day > 29) return 0;
    }

    return 1;
}

int validateInput(const char* input, int type) {
    if (type == 1) {
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                return 0; 
            }
        }
        return 1; 
    } else if (type == 2) {
        return strlen(input) > 0;
    }
    return 0;
}


void formatTaskDisplay(Task* task) {
    printf("\n===== Detalji zadatka =====\n");
    printf("Naslov: %-30s\n", task->title); // Padding u lijevo
    printf("Prioritet: %-10d\n", task->priority);
    printf("Datum: %02d/%02d\n", task->day, task->month);
    printf("Status: %-10s\n", (task->status == ACTIVE) ? "ACTIVE" : "FINISHED");
    printf("===========================\n");
}


int comparePriority(const void* a, const void* b) {
    Task *taskA = (Task*)a;
    Task *taskB = (Task*)b;

    return taskB->priority - taskA->priority; // Sortiranje u padajucem redoslijedu
}

void sortTasksByPriority(circular_buffer *cb) {
    if (isEmpty(cb)) {
        printf("Nema zadataka za sortiranje.\n");
        return;
    }

    qsort(cb->tasks, cb->elementCounter, sizeof(Task), comparePriority);
    printf("Zadaci su uspješno sortirani prema prioritetu.\n");
}

//Funckije za spremanje i učitavanje Task-ova iz file-a
void saveTasksToFile(circular_buffer *cb, const char *filename) {
    if (isEmpty(cb)) {
        printf("Nema zadataka u bufferu.\n");
        return;
    }

    FILE *file = fopen(filename, "w");  //Otvara file u "write" modu
    if (file == NULL) {
        printf("Nemoguce otvoriti file!\n");
        return;
    }

    // Zapis svih novih taskova
    int index = cb->tail;
    for (int i = 0; i < cb->elementCounter; i++) {
        Task *task = &cb->tasks[index];
        fprintf(file, "%s,%d,%hd,%hd,%d\n", task->title, task->priority, task->day, task->month, task->status);
        index = (index + 1) % MAX_BUFFER_SIZE;
    }

    fclose(file);
    printf("Tasks saved to file successfully.\n");
}


void deleteTask(circular_buffer *cb, int taskIndex) {
    if (isEmpty(cb)) {
        printf("Nema zadataka u bufferu.\n");
        return;
    }

    // Validate taskIndex
    if (taskIndex < 1 || taskIndex > cb->elementCounter) {
        printf("Nevažeći indeks zadatka.\n");
        return;
    }

    // Find the actual index in the buffer
    int actualIndex = (cb->head + taskIndex - 1) % MAX_BUFFER_SIZE;

    // Shift all tasks after the deleted task
    for (int i = actualIndex; i != cb->tail; i = (i + 1) % MAX_BUFFER_SIZE) {
        int nextIndex = (i + 1) % MAX_BUFFER_SIZE;
        cb->tasks[i] = cb->tasks[nextIndex];
    }

    // Adjust the tail pointer and element count
    cb->tail = (cb->tail - 1 + MAX_BUFFER_SIZE) % MAX_BUFFER_SIZE;
    cb->elementCounter--;

    printf("Zadatak na indeksu %d je obrisan.\n", taskIndex);
}




void loadTasksFromFile(circular_buffer *cb, const char *filename) {
    FILE *file = fopen(filename, "r");  // Open the file in read mode
    if (file == NULL) {
        printf("No tasks file found, starting with an empty buffer.\n");
        return;
    }

    char title[MAX_TITLE_LENGTH];
    int priority;
    short day, month, status;

    while (fscanf(file, "%[^,],%d,%hd,%hd,%hd\n", title, &priority, &day, &month, &status) == 5) {
        // Prepare the task to be added
        Task newTask;
        strncpy(newTask.title, title, MAX_TITLE_LENGTH);
        newTask.priority = (priorityLevel)priority;
        newTask.day = day;
        newTask.month = month;
        newTask.status = (TaskStatus)status;

        // Add the task to the buffer
        addElement(cb, &newTask);
    }

    fclose(file);
    printf("Tasks loaded from file successfully.\n");
}
