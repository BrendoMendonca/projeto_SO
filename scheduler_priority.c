#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "list.h"
#include "cpu.h"

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

// Seleciona a próxima tarefa com a maior prioridade
Task *pickNextTask() {
    if (task_list == NULL) return NULL;

    struct node *current = task_list;
    Task *highest_priority_job = current->task;
    
    while (current != NULL) {
        if (current->task->priority > highest_priority_job->priority) {
            highest_priority_job = current->task;
        }
        current = current->next;
    }
    return highest_priority_job;
}

// Lógica principal do escalonador por Prioridade
void schedule() {
    int current_time = 0; //inicializa o relógio da simulação em 0
    printf("Escalonador por Prioridade\n");

    while (task_list != NULL) {
        Task *task = pickNextTask(); //seleciona a próxima tarefa a ser executada baseada na sua lista de prioridade

        if (task->response_time == -1) {   //verifica se é a primeira vez que a tarefa está sendo executada
            task->response_time = current_time;
        }
        //slice recebe o tempo completo do burst para tornar o algoritmo não preemptivo
        int slice = task->burst;
        run(task, slice);
        current_time += slice;
        
        task->turnaround_time = current_time;
        //deleta a tarefa completa da lista e insere na lista de completas
        delete(&task_list, task);
        insert(&completed_list, task);
    }
    
    print_performance_metrics();
}