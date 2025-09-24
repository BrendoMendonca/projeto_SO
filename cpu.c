#include <stdio.h>
#include "cpu.h"

//execução de uma tarefa
void run(Task *task, int slice) {//slice representa o tempo que a tarefa roda na chamada
    printf("Executando tarefa %s [tid %d] [prioridade %d] por %d ms.\n",
           task->name, task->tid, task->priority, slice);
    
    //atualiza o tempo de burst restante
    task->remaining_burst -= slice;
}