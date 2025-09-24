#ifndef TASK_H
#define TASK_H

//estrutura de representação de uma tarefa
typedef struct task {
    char *name;//ponteiro para armazenar o endereço do nome
    int tid;//id para identificar as tarefas
    int priority;
    int burst;//tempo total qua a tarefa precisa
    int remaining_burst;//tempo de burst restante-rr

    //métricas de desempenho
    int waiting_time;//tempo que ficou na fila de prontos - esperando ser executada
    int turnaround_time;//tempo total - desde a chegada até a aexecução
    int response_time;//tempo da chegada até sua primeira execução
} Task;

//nó da lista ligada
struct node {
    Task *task;
    struct node *next;
};

#endif