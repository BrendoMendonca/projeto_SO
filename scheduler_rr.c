#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "list.h"
#include "cpu.h"


static struct node *task_list = NULL;//ponteiro para a lista de prontos
static struct node *completed_list = NULL;//ponteiro para a lista de concluidos
static int tid_counter = 0;//contador para gerar os IDs das tarefas

//adiciona uma tarefa à lista do escalonador
void add(char *name, int priority, int burst) {
    Task *new_task = malloc(sizeof(Task));
    new_task->name = strdup(name);
    new_task->priority = priority;
    new_task->burst = burst;
    new_task->remaining_burst = burst;
    new_task->tid = __sync_fetch_and_add(&tid_counter, 1);
    new_task->response_time = -1;//indica que ainda não foi executado
    insert(&task_list, new_task);
}

//imprime métricas de desempenho
void print_performance_metrics() {
    if (completed_list == NULL) return;
    //variáveis para calcular as médias
    struct node *current = completed_list;
    int count = 0;
    float total_turnaround_time = 0.0, total_waiting_time = 0.0, total_response_time = 0.0;
    printf("\nMétricas de Desempenho:\n");
    //percorre a lista de tarefas concluídas
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

//seleciona a próxima tarefa-primeira da fila para RR
Task *pickNextTask() {
    if (task_list == NULL) return NULL;
    return task_list->task;
}

//lógica do escalonador RR
void schedule() {
    int current_time = 0;//inicialização do tempo da tarefa
    printf("Escalonador Round-Robin (Quantum=%dms)\n", QUANTUM);

    while (task_list != NULL) {
        Task *task = pickNextTask();

        if (task->response_time == -1) {
            task->response_time = current_time;
        }

        /*se o burst restante for MENOR que o QUANTUM,o slice será o burst restante.
        senão, o slice será o QUANTUM completo.*/
        int slice = (task->remaining_burst < QUANTUM) ? task->remaining_burst : QUANTUM;//define o tempo que a tarefa vai rodar
        run(task, slice);//faz a execução pelo tempo calculado
        current_time += slice;//incremento de tempo

        //verifica se a tarefa terminou
        if (task->remaining_burst <= 0) {
            //tarefa concluida
            task->turnaround_time = current_time;//registra o tempo de conclusão.
            delete(&task_list, task); //remove da fila de prontos
            insert(&completed_list, task);//insere na lista de concluídos
        } else {
            //tarefa não conclída - move a tarefa para o final da lista
            delete(&task_list, task);//remove do início da lista
            insert(&task_list, task);//insere no fim da lista
        }
    }
    
    print_performance_metrics();
}