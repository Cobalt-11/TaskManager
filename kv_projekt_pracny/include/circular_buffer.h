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
	 } TaskStatus;

typedef struct  {
	char title[MAX_TITLE_LENGTH];
	priorityLevel priority;
	short day;
	short month;
	TaskStatus status;
	} Task;

typedef struct{

	Task tasks[MAX_BUFFER_SIZE];
	int elementCounter;
	int head; //pointer to head
	int tail; //pointer to tail
	} circular_buffer;


//Pomocna funkcija da mi pretvori enum brojve u string (tj. da mi vrati ime varijable)
const char* getStatusString(TaskStatus tStatus);

//Inicijalizira strukturu
void initialize(circular_buffer *cb);

//Dodaje element u strukturu
void addElement(circular_buffer *cb, Task *ts);

//Provjerava da li je struktura prazna
int isEmpty(circular_buffer *cb);

//Provjerava da li je struktura puna
int isFull(circular_buffer *cb);

//Ispisuje buffer tj.strukturu
void printBuffer(circular_buffer *cb);

void clearBuffer(circular_buffer *cb);

#endif
//End header guard
