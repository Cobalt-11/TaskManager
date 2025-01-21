#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "task_manager.h"

// Funkcija za unos novog zadatka
void addTask(circular_buffer* cb) {
    if (isFull(cb)) {
        printf("Buffer je pun.\n");
        //showMainMenu();
        return;
    }

    taskStruct newTask;
    printf("Enter task title: ");
    //getchar();  // To consume newline ---> zbog nekog razloga mice mi prvo slovo
    fgets(newTask.title, MAX_TITLE_LENGTH, stdin);
    newTask.title[strcspn(newTask.title, "\n")] = '\0';  // Remove newline

    // Validacija prioriteta
    int priority = 0;
    while (1) {
        printf("Enter task priority (1: LOW, 2: MEDIUM, 3: HIGH): ");
        scanf("%d", &priority);
        if (priority >= LOW && priority <= HIGH) {
            newTask.priority = priority;
            break;
        } else {
            printf("Neispravan unos. Unesite ispravnu vrijednost 1- 3.\n");
        }
    }

    // Validacija datuma
    while (1) {
        printf("Enter task due date (day month): ");
        scanf("%hd %hd", &newTask.day, &newTask.month);
        if (newTask.day >= 1 && newTask.day <= 31 && newTask.month >= 1 && newTask.month <= 12) {
            break;
        } else {
            printf("Neispravan unos. Unesite ispravan dan (1-31) i mjesec (1-12).\n");
        }
    }

    newTask.status = ACTIVE;
    addElement(cb, &newTask);
    printf("Task added successfully!\n");
    //showMainMenu();
}

// Funkcija za prikaz zadataka
void displayTasks(circular_buffer* cb) {
    if (isEmpty(cb)) {
        printf("No tasks available.\n");
        //showMainMenu();
        return;
    }

    // Sortiranje zadataka po prioritetu prije prikaza
    sortTasksByPriority(cb);

    printf("==== Tasks List ====\n");
    for (int i = 0; i < cb -> elementCounter; i++) {
        //printf("%d. ", i + 1);  // Numeriranje zadataka
        formatTaskDisplay(&cb -> tStruct[i]);
    }

    printf("Total tasks: %d\n", cb->elementCounter);
    //showMainMenu(); -- mogu dodati da mi ponudi pritiskom tipke
}

// Funkcija za označavanje zadatka kao završenog
void markTaskCompleted(circular_buffer* cb, int taskIndex) {
    if (taskIndex < 0 || taskIndex >= cb->elementCounter) {
        printf("Invalid task index.\n");
        //showMainMenu();
        return;
    }

    char confirmation;
    printf("Are you sure you want to mark task '%s' as completed? (d/n): ", cb->tStruct[taskIndex].title);
    getchar();  // Consume newline
    scanf("%c", &confirmation);
    if (confirmation == 'd' || confirmation == 'D') {
        cb->tStruct[taskIndex].status = FINISHED;
        printf("Task marked as completed!\n");
    } else {
        printf("Action canceled.\n");
    }
    //showMainMenu();
}

// Funkcija za brisanje zadatka
void deleteTask(circular_buffer* cb, int taskIndex) {
    if (taskIndex < 0 || taskIndex >= cb->elementCounter) {
        printf("Invalid task index.\n");
        //showMainMenu();
        return;
    }

    char confirmation;
    printf("Are you sure you want to delete task '%s'? (d/n): ", cb->tStruct[taskIndex].title);
    getchar();  // Consume newline
    scanf("%c", &confirmation);
    if (confirmation == 'd' || confirmation == 'D') {
        removeElement(cb, taskIndex);
        printf("Task deleted successfully!\n");
    } else {
        printf("Action canceled.\n");
    }
    //showMainMenu();
}

// Funkcija za validaciju datuma (format "YYYY-MM-DD")
int validateDate(const char* date) {
    int day, month;
    sscanf(date, "%d %d", &day, &month);
    if (day < 1 || day > 31 || month < 1 || month > 12) {
        return 0;  // Nevalidan datum
    }
    return 1;  // Validan datum
}

// Funkcija za validaciju korisničkog unosa
int validateInput(const char* input, int type) {
    // Implementacija validacije, može biti specifično za tip
    return 1;  // Pretpostavljamo da je unos uvijek validan
}


// Funkcija za formatiranje ispisa zadatka
void formatTaskDisplay(taskStruct* task) {
    printf("Title: %s\n", task->title);
    printf("Priority: %d\n", task->priority);
    printf("Due Date: %02d-%02d\n", task->day, task->month);
    printf("Status: %s\n", task->status == ACTIVE ? "Active" : "Completed");
}

// Funkcija za sortiranje zadataka prema prioritetu
void sortTasksByPriority(circular_buffer* cb) {
    for (int i = 0; i < cb->elementCounter - 1; i++) {
        for (int j = i + 1; j < cb->elementCounter; j++) {
            if (cb->tStruct[i].priority > cb->tStruct[j].priority) {
                taskStruct temp = cb->tStruct[i];
                cb->tStruct[i] = cb->tStruct[j];
                cb->tStruct[j] = temp;
            }
        }
    }
}

// Funkcija za učitavanje zadataka iz datoteke
int loadTasksFromFile(const char* filename, circular_buffer* cb) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return -1;  // Neuspjeh prilikom otvaranja datoteke
    }

    int tasksLoaded = 0;

    // Učitavamo zadatke sve dok ne dođemo do kraja datoteke ili buffer nije pun
    while (!feof(file) && cb->elementCounter < MAX_BUFFER_SIZE) {
        taskStruct newTask;
        if (fscanf(file, "%49[^\n]%*c%d %hd %hd %d\n",
            newTask.title,
            &newTask.priority,
            &newTask.day,
            &newTask.month,
            &newTask.status) == 5) {

            addElement(cb, &newTask);
            tasksLoaded++;
        }
    }

    fclose(file);
    printf("%d tasks loaded successfully.\n", tasksLoaded);
    return tasksLoaded;
}

// Funkcija za spremanje zadataka u datoteku
int saveTasksToFile(const char* filename, circular_buffer* cb) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return -1;
    }

    int tasksSaved = 0;
    for (int i = 0; i < cb->elementCounter; i++) {
        if (fprintf(file, "%s\n%d %hd %hd %d\n",
            cb->tStruct[i].title,
            cb->tStruct[i].priority,
            cb->tStruct[i].day,
            cb->tStruct[i].month,
            cb->tStruct[i].status) > 0) {
            tasksSaved++;
        }
    }

    fclose(file);
    printf("%d tasks saved successfully.\n", tasksSaved);
    return tasksSaved;
}


void checkOperationStatus(int status) {
    if (status == -1) {
        printf("Operation failed.\n");
    } else {
        printf("Operation succeeded.\n");
    }
}

// Nova funkcija showMainMenu:
void showMainMenu() {
    printf("\n=== Task Manager Menu ===\n");
    printf("1. Add new task\n");
    printf("2. Display all tasks\n");
    printf("3. Mark task as completed\n");
    printf("4. Delete task\n");
    printf("5. Save tasks to file\n");
    printf("6. Load tasks from file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Nova funkcija za filtriranje zadataka:
void filterTasksByStatus(circular_buffer* cb, taskStatus status) {
    printf("\n=== Filtered Tasks (%s) ===\n",
           status == ACTIVE ? "Active" : "Completed");

    int found = 0;
    for (int i = 0; i < cb->elementCounter; i++) {
        if (cb->tStruct[i].status == status) {
            printf("%d. ", found + 1);
            formatTaskDisplay(&cb->tStruct[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("No tasks found with status: %s\n",
               status == ACTIVE ? "Active" : "Completed");
    }
}

