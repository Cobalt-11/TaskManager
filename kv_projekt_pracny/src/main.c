#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>  // Dodano za funkciju system()
#include "task_manager.h"

int main() {
    circular_buffer cb;
    initialize(&cb);

    // Učitava file
    loadTasksFromFile(&cb, "tasks.txt");

    while (1) {
        showMainMenu();

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(&cb); 
                break;
            case 2:
                displayTasks(&cb); 
                break;
            case 3:
                saveTasksToFile(&cb, "tasks.txt");
                printf("Izlazak iz programa...\n");
                return 0;
            case 4: {
                char confirm[3];  
                printf("Da li sigurno hoćeš obrisati sve? Upiši da/ne: ");
                scanf("%s", confirm);

                if (strcmp(confirm, "da") == 0) {
                    clearBuffer(&cb);  
                    printf("Buffer je izpražnjen\n");
                } else {
                    printf("Povratak na glavni izbornik.\n");
                }
                break; 
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
