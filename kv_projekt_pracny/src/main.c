#include <stdio.h>
#include <string.h>
#include "circular_buffer.h"
#include "task_manager.h"



int main() {

	test_addTask();
    return 0;
}

void test_addTask() {
	circular_buffer cb;
	initialize(&cb); // Inicijalizacija buffer-a

	addTask(&cb);
	displayTasks(&cb);
	saveTasksToFile("task.txt", &cb);

}

