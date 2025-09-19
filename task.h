#ifndef TASK_H
#define TASK_H

//estrutura de representação de uma tarefa
typedef struct task {
    char *name;
    int tid;
    int priority;
    int burst;
    int remaining_burst;

    //métricas de desempenho
    int waiting_time;
    int turnaround_time;
    int response_time;
} Task;

//nó da lista ligada
struct node {
    Task *task;
    struct node *next;
};

#endif