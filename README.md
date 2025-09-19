# Projeto Sistemas Operacionais
# #Escalonador de CPU - Cap. 5

O objetivo é simular a execução de um conjunto de tarefas em um processador, aplicando cinco algoritmos distintos de escalonamento:
1.  First-Come, First-Served (FCFS) 
2.  [cite_start]Shortest-Job-First (SJF) (não preemptivo)
3.  Prioridade (não preemptivo)
4.  [cite_start]Round-Robin (RR)
5.  [cite_start]Prioridade com Round-Robin

O projeto foi desenvolvido em **C/C++** e foi projetado para ser executado em um ambiente **Linux**

O projeto consiste em um simulador que recebe uma lista de tarefas, cada uma com um nome, prioridade e tempo de burst de CPU. O simulador então executa essas tarefas de acordo com o algoritmo de escalonamento selecionado e, ao final, calcula e exibe métricas de desempenho, como tempo de espera, tempo de retorno (turnaround) e tempo de resposta médios. Além disso, como desafio adicional, a atribuição de identificadores de tarefa (TID) foi implementada de forma segura para ambientes concorrentes (SMP) usando um inteiro atômico, e o cálculo das métricas de desempenho foi incluído

## Instruções de Como Compilar e Executar

### Dependências
* `g++` (ou `gcc`)
* `make`

### Compilação
O projeto utiliza um `Makefile` para facilitar a compilação dos diferentes algoritmos. Para compilar um algoritmo específico, utilize o comando `make` seguido do nome do algoritmo.
Os arquivos disponíveis são: `fcfs`, `sjf`, `priority`, `rr`, `priority_rr`.

**Exemplo para compilar o FCFS:**
```bash
make fcfs
```
### Execução
Após a compilação, o executável correspondente é criado. Para executar, é necessário passar como argumento o caminho para o arquivo "schedule.txt" que contém a lista de tarefas
* O arquivo possui uma tarefa por linha, com os campos separados por vírgula e espaço, no seguinte formato:
  ```bash
  [nome_da_tarefa], [prioridade], [burst_cpu]
  ```
  Exemplo:
  ```bash
  T1, 4, 20
  T2, 2, 25
  T3, 3, 25
  T4, 3, 15
  T5, 10, 10
  ```
