#include <stdlib.h>
#include <stdio.h>
#include "task_manager.h"
#include "circular_buffer.h"

//Inicijalizira strukturu
void initialize(circular_buffer *cb) {
    //cb -> tasks; netreba incijalizirait   
    cb -> elementCounter = 0;
    cb -> head = 0;
    cb -> tail = 0;
}

//Dodaje element u strukturu
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

//Provjerava da li je struktura prazna
int isEmpty(circular_buffer *cb) {
    return cb -> elementCounter == 0;
}

//Provjerava da li je struktura puna
int isFull(circular_buffer *cb) {
    return cb -> elementCounter == MAX_BUFFER_SIZE;
}


//Popricaj s profesorom u vezi ovoga, da umjesto da mi pise 1 ili 2 da pise
// ACTIVE ILI FINISHED
const char* getStatusString(TaskStatus tStatus) {
    switch (tStatus)
    {
    case ACTIVE: return "ACTIVE";
    case FINISHED: return "FINISHED";        
    default: return "NONE";
    }
}

//Ispisuje buffer tj.strukturu
void printBuffer(circular_buffer *cb) {
    if(isEmpty(cb)) {
        printf("Buffer je prazan.\n");
        return;
    }

    int index  = cb -> tail;
    for (int i = 0; i < cb -> elementCounter; i++) {
        Task *t = &cb -> tasks[index]; // Fetch current task
        formatTaskDisplay(t);  // Format and print task details

        index = (index + 1) % MAX_BUFFER_SIZE; // Move to next task
    }
}


Task* getElement(circular_buffer *cb, int index) {
    if (index < 0 || index >= cb -> elementCounter) {
        return NULL; // Vraća NULL ako je indeks izvan granica
    }
    int actualIndex = (cb->tail + index) % MAX_BUFFER_SIZE; // Izračun pravog indeksa
    return &cb->tasks[actualIndex];
}



int getCount(circular_buffer *cb) {
    return cb -> elementCounter;
}


