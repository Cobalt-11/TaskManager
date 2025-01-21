#include <stdio.h>
#include <math.h>
#include <stdlib.h>  // Dodano za funkciju system()
#include "task_manager.h"

int main() {
    circular_buffer cb;
    initialize(&cb);

    // Load tasks from the file at the start
    loadTasksFromFile(&cb, "tasks.txt");

    // Your main menu loop
    while (1) {
        showMainMenu();

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(&cb);  // Add a new task
                break;
            case 2:
                displayTasks(&cb);  // Display tasks
                break;
            case 3:
                // Save tasks to file before exiting
                saveTasksToFile(&cb, "tasks.txt");
                printf("Exiting program...\n");
                return 0;
            case 4:
                printf("Izlaz iz programa.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
