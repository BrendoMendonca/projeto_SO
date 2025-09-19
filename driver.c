#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_de_tarefas>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {//tratamento caso os parâmetros sejam passados errados
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    //buffers de entrada
    char line[MAX_LINE_LENGTH];
    char name[20];

    int priority, burst;

    //lê o arquivo de tarefas e as adiciona ao escalonador
    while (fgets(line, sizeof(line), fp)) {
        //usa sscanf para obter as informações do buffer
        if (sscanf(line, " %19[^,], %d, %d", name, &priority, &burst) == 3) {
            add(name, priority, burst); //chamada do escalonador para adicionar a tarefa à lista
        } else {//tratamento caso a entrada esteja errada
            fprintf(stderr, "Formato de linha inválido: %s", line);
        }
    }

    fclose(fp);

    //invoca o escalonador
    schedule();

    return 0;
}