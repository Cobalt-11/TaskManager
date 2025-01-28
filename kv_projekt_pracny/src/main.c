#include <stdio.h>
#include <math.h>
#include <string.h>
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
                printf("Izlazak iz programa...\n");
                return 0;
            case 4: {
                char confirm[3];  // Array to hold user input ("da" or "ne")
                printf("Da li sigurno hoćeš obrisati sve? Upiši da/ne: ");
                scanf("%s", confirm);

                // Check the user's input
                if (strcmp(confirm, "da") == 0) {
                    clearBuffer(&cb);  // Clear the buffer
                    printf("Buffer je izpražnjen\n");
                } else {
                    printf("Povratak na glavni izbornik.\n");
                }
                break;  // Ensure we don't fall through to the next case
                }
            case 5:
                printf("Izlaz iz programa.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
