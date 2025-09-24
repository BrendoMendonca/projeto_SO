#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "scheduler.h"
#include "list.h"
#include "cpu.h"


// ...
static struct node *task_list = NULL;
static struct node *completed_list = NULL;
static int tid_counter = 0;

void add(char *name, int priority, int burst) {
    Task *new_task = malloc(sizeof(Task));
    new_task->name = strdup(name);
    new_task->priority = priority;
    new_task->burst = burst;
    new_task->remaining_burst = burst;
    new_task->tid = __sync_fetch_and_add(&tid_counter, 1);
    new_task->response_time = -1;
    insert(&task_list, new_task);
}

void print_performance_metrics() {
    // ... (mesma função do FCFS)
    if (completed_list == NULL) return;
    struct node *current = completed_list;
    int count = 0;
    float total_turnaround_time = 0.0, total_waiting_time = 0.0, total_response_time = 0.0;
    printf("\nMétricas de Desempenho:\n");
    while (current != NULL) {
        Task *task = current->task;
        task->waiting_time = task->turnaround_time - task->burst;
        printf("Tarefa %s (tid %d): Turnaround=%dms, Waiting=%dms, Response=%dms\n", task->name, task->tid, task->turnaround_time, task->waiting_time, task->response_time);
        total_turnaround_time += task->turnaround_time;
        total_waiting_time += task->waiting_time;
        total_response_time += task->response_time;
        count++;
        current = current->next;
    }
    printf("\nMédias:\n");
    printf("Tempo de Retorno (Turnaround) Médio: %.2f ms\n", total_turnaround_time / count);
    printf("Tempo de Espera Médio: %.2f ms\n", total_waiting_time / count);
    printf("Tempo de Resposta Médio: %.2f ms\n", total_response_time / count);
}


// Seleciona a próxima tarefa: a primeira da fila com a maior prioridade
Task *pickNextTask() {
    if (task_list == NULL) return NULL;

    struct node *current = task_list;
    Task *next_task = NULL;
    int highest_priority = INT_MIN;

    // Encontra o nível de prioridade mais alto na fila
    while (current != NULL) {
        if (current->task->priority > highest_priority) {
            highest_priority = current->task->priority;
        }
        current = current->next;
    }
    
    // Encontra a primeira tarefa na lista com essa prioridade
    current = task_list;
    while (current != NULL) {
        if (current->task->priority == highest_priority) {
            next_task = current->task;
            break;
        }
        current = current->next;
    }

    return next_task;
}

// Lógica principal do escalonador Prioridade com RR
void schedule() {
    int current_time = 0;
    printf("Escalonador Prioridade com Round-Robin (Quantum=%dms)\n", QUANTUM); // print com o quantum representando o tempo máximo que a tarefa vai rodar

    while (task_list != NULL) {
        Task *task = pickNextTask();

        if (task->response_time == -1) {  // verifica se a tarefa já foi executada
            task->response_time = current_time;
        }

        int slice = (task->remaining_burst < QUANTUM) ? task->remaining_burst : QUANTUM; //verifica: "O tempo de burst que resta para a tarefa é menor que o quantum?" Se sim, a slice será esse tempo restante (para a tarefa terminar exatamente).

        run(task, slice);
        current_time += slice;
//verifica se a tarefa terminou (se o tempo de burst restante é zero ou menos).
        if (task->remaining_burst <= 0) {
            task->turnaround_time = current_time;
            delete(&task_list, task);
            insert(&completed_list, task);
        } else {
            // Move a tarefa para o final da lista
            delete(&task_list, task);
            insert(&task_list, task);
        }
    }
    
    print_performance_metrics();
}