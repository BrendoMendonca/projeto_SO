#ifndef LIST_H
#define LIST_H

#include "task.h"

//protótipos das funções da lista
void insert(struct node **head, Task *task);
void delete(struct node **head, Task *task);
void traverse(struct node *head);

#endif