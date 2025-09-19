#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "list.h"
#include "cpu.h"

static struct node *task_list = NULL;//ponteiro para a lista de prontos
static struct node *completed_list = NULL;////ponteiro para a lista de concluidos
static int tid_counter = 0;//contador para gerar os IDs das tarefas

//adiciona uma tarefa à lista do escalonador
void add(char *name, int priority, int burst) {
    Task *new_task = malloc(sizeof(Task));
    new_task->name = strdup(name);
    new_task->priority = priority;
    new_task->burst = burst;
    new_task->remaining_burst = burst;
    new_task->tid = __sync_fetch_and_add(&tid_counter, 1);
    new_task->response_time = -1; //indica que ainda não foi executado
    insert(&task_list, new_task);
}

//seleciona a próxima tarefa-primeira da lista para FCFS
Task *pickNextTask() {
    if (task_list == NULL) return NULL;
    return task_list->task;
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
        //calcula o tempo de espera
        task->waiting_time = task->turnaround_time - task->burst;
        //impressão das métricas
        printf("Tarefa %s (tid %d): Turnaround=%dms, Waiting=%dms, Response=%dms\n",
               task->name, task->tid, task->turnaround_time, task->waiting_time, task->response_time);

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


//lógica do FCFS-executa a simulação do escalonador FCFS
void schedule() {
    int current_time = 0;//inicialização do tempo da tarefa
    printf("Escalonador FCFS\n");

    while (task_list != NULL) {
        Task *task = pickNextTask();

        if (task->response_time == -1) {//para a primeira execução da tarefa
            task->response_time = current_time;
        }

        //a tarefa roda de uma vez - não preeptivo
        int slice = task->burst;
        run(task, slice);
        current_time += slice;//atualiza o tempo com a duração da execução da tarefa
        
        //o tempo de turnaround é o tempo de conclusão, como a tarefa acabou de terminar, é o tempo atual.
        task->turnaround_time = current_time;
        
        delete(&task_list, task);//remoção da tarefa da lista após sua conclusão
        insert(&completed_list, task);//inserção na lista de tarefas concluídas
    }
    
    print_performance_metrics();//exibição dos resultados
}