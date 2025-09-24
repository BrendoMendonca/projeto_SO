#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

//insere um novo nó no final da lista
void insert(struct node **head, Task *newTask) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = newTask;//o nó aponta para a terefa
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct node *current = *head;
        while (current->next != NULL) {//percorre até o último nó
            current = current->next;
        }
        current->next = newNode;
    }
}

//deleta um nó da lista
void delete(struct node **head, Task *task) {
    struct node *temp = *head;
    struct node *prev = NULL;//ponteiro para o nó anterior - faz o religamento

    if (temp != NULL && temp->task == task) {//caso seja o primeiro nó
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->task != task) {
        prev = temp;//o anterior passa a ser o nó atual
        temp = temp->next;//o nó atual avança para o próximo.
    }

    if (temp == NULL) return;//caso a tarefa não esteja na lista

    prev->next = temp->next;//religa a lista
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