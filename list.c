#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

//insere um novo nó no final da lista
void insert(struct node **head, Task *newTask) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = newTask;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

//deleta um nó da lista
void delete(struct node **head, Task *task) {
    struct node *temp = *head;
    struct node *prev = NULL;

    if (temp != NULL && temp->task == task) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->task != task) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

//percorre e imprime a lista-para debug)
void traverse(struct node *head) {
    struct node *temp = head;
    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n", temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}