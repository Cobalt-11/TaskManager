#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "circular_buffer.h"

//Inicijalizira strukturu
void initialize(circular_buffer *cb) {
	cb -> tStruct;
	cb -> elementCounter = 0;
	cb -> head = 0;
	cb -> tail = 0;
	memset(cb -> tStruct, 0, sizeof(cb -> tStruct)); //inicijalizira polje sa nulama
}

//Dodaje element u strukturu
void addElement(circular_buffer *cb, taskStruct *ts) {
	if(isFull(cb)) {
		printf("Buffer je pun! Nemoguce naknadno dodavanje.\n");
		return;
	}
	
	cb -> tStruct[cb -> tail] = *ts; //
    cb -> tail = (cb->tail + 1) % MAX_BUFFER_SIZE;  // Pomici buffer u kruzni
    cb -> elementCounter++;
}

//Mice element iz strukture
void removeElement(circular_buffer *cb, int isRemoved) {
	if(isEmpty(cb)) {
		printf("Buffer je prazan! Nemoguce uklanjanje.");
		return;
	}

    cb -> head = (cb -> head + 1) % MAX_BUFFER_SIZE;
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

//Ispisuje buffer tj.strukturu
void printBuffer(circular_buffer *cb) {

	if(isEmpty(cb)) {
		printf("Buffer je prazan.");
	}

	printf("#####TASK_LIST#####");
	int i = cb -> head;
	for(int count = 0; count < cb -> elementCounter; count++) {
		printf("Task %d: Title: %s, Priority: %d, Day: %d, Month: %d, Status: %s\n",
				count + 1,
				cb -> tStruct[i].title,
				cb -> tStruct[i].priority,
				cb -> tStruct[i].day,
				cb -> tStruct[i].month,
				cb -> tStruct[i].status == ACTIVE ? "Active" : "Finished");
		i = (i + 1) % MAX_BUFFER_SIZE; //idi dalje

	}
	printf("########\n");
}
