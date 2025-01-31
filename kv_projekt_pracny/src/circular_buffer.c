#include <stdlib.h>
#include <stdio.h>
#include "task_manager.h"
#include "circular_buffer.h"

void initialize(circular_buffer *cb) {
    //cb -> tasks; netreba incijalizirait   
    cb -> elementCounter = 0;
    cb -> head = 0;
    cb -> tail = 0;
}

void addElement(circular_buffer *cb, Task *ts) {

    if(isFull(cb)) {
        printf("Buffer je pun! Nemoguce dodavanje");
        return;
    }

    
    cb -> tasks[cb -> head] = *ts; // kopira podatke u buffer
    cb -> head = (cb -> head + 1 ) % MAX_BUFFER_SIZE; //pomakni u head
    cb -> elementCounter++; //dodaj element
}

//Mice element iz strukture
void removeElement(circular_buffer *cb, int isRemoved) {
    if(isEmpty(cb)) {
        printf("Buffer je prazan!");
    }

    cb -> tail = (cb -> tail + 1 ) % MAX_BUFFER_SIZE; //pomakni u tail
    cb -> elementCounter--;
}

int isEmpty(circular_buffer *cb) {
    return cb -> elementCounter == 0;
}

int isFull(circular_buffer *cb) {
    return cb -> elementCounter == MAX_BUFFER_SIZE;
}


// pomocna funkcija da ispisuje ime varijable umjesto numericke 
// vrijednosti
const char* getStatusString(TaskStatus tStatus) {
    switch (tStatus)
    {
    case ACTIVE: return "ACTIVE";
    case FINISHED: return "FINISHED";        
    default: return "NONE";
    }
}

void printBuffer(circular_buffer *cb) {
    if(isEmpty(cb)) {
        printf("Buffer je prazan.\n");
        return;
    }

    int index  = cb -> tail;
    for (int i = 0; i < cb -> elementCounter; i++) {
        Task *t = &cb -> tasks[index];
        formatTaskDisplay(t); 

        index = (index + 1) % MAX_BUFFER_SIZE;
    }
}


Task* getElement(circular_buffer *cb, int index) {
    if (index < 0 || index >= cb -> elementCounter) {
        return NULL; 
    }
    int actualIndex = (cb->tail + index) % MAX_BUFFER_SIZE; 
    return &cb->tasks[actualIndex];
}



int getCount(circular_buffer *cb) {
    return cb -> elementCounter;
}


#include <stdio.h>

void clearBuffer(circular_buffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->elementCounter = 0;

    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Error opening file tasks.txt\n");
        return;
    }
    fclose(file);  


    if (remove("tasks.txt") == 0) {
        printf("Tasks deleted successfully.\n");
    } else {
        printf("Error deleting tasks\n");
    }

    printf("Buffer cleared and tasks deleted.\n");
}


