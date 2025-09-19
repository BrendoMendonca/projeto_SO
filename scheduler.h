#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

#define QUANTUM 10//macro de tempo usada no escalonamento round robin

//protótipos das funções do escalonador
void add(char *name, int priority, int burst);
void schedule();

#endif