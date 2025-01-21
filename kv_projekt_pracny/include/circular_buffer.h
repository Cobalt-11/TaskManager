//header guard
#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#define MAX_BUFFER_SIZE 20
#define MAX_TITLE_LENGTH 50

typedef enum {
	LOW 	= 1,
	MEDIUM 	= 2,
	HIGH	= 3 
	 } priorityLevel;

typedef enum {
	ACTIVE	 = 1,
	FINISHED = 2
	 } taskStatus;

typedef struct  {
	char title[MAX_TITLE_LENGTH];
	priorityLevel priority;
	short day;
	short month;
	taskStatus status;
	} taskStruct;

typedef struct{

	taskStruct tStruct[MAX_BUFFER_SIZE];
	int elementCounter;
	int head; //pointer to head
	int tail; //pointer to tail
	} circular_buffer;

//Inicijalizira strukturu
void initialize(circular_buffer *cb);

//Dodaje element u strukturu
void addElement(circular_buffer *cb, taskStruct *ts);

//Mice element iz strukture
void removeElement(circular_buffer *cb, int isRemoved);

//Provjerava da li je struktura prazna
int isEmpty(circular_buffer *cb);

//Provjerava da li je struktura puna
int isFull(circular_buffer *cb);

//Ispisuje buffer tj.strukturu
void printBuffer(circular_buffer *cb);

#endif
//End header guard
