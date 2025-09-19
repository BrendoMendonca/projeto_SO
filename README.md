# Projeto Sistemas Operacionais
## Escalonador de CPU - Cap. 5

O objetivo é simular a execução de um conjunto de tarefas em um processador, aplicando cinco algoritmos distintos de escalonamento:
1.  First-Come, First-Served (FCFS) 
2.  Shortest-Job-First (SJF) (não preemptivo)
3.  Prioridade (não preemptivo)
4.  Round-Robin (RR)
5.  Prioridade com Round-Robin

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

## Análise de Resultados Utilizando o Exemplo Acima
* SJF apresentou o melhor desempenho com menor tempo de espera, de retorno médios e de resposta o que é consistente com a teoria que o aponta como ótimo em cenários não preemptivos
* Round-Robin (RR) se destacou com o menor tempo de resposta, demonstrando sua superioridade para sistemas interativos, garantindo que todas as tarefas comecem a ser executadas rapidamente
* FCFS apresentou o desempenho mais baixo em geral, sofrendo com o "efeito comboio", onde tarefas curtas precisaram esperar a conclusão de todas as que chegaram antes
* Prioridade com RR ofereceu um bom equilíbrio, melhorando a responsividade em comparação com o algoritmo de Prioridade puro, ao mesmo tempo em que respeita a importância das tarefas

## Imagens de testes

### SJF
<img width="579" height="288" alt="image" src="https://github.com/user-attachments/assets/8a66c01d-47e3-4b7c-aa1c-6793f584e4ad" />

### RR

<img width="570" height="390" alt="image" src="https://github.com/user-attachments/assets/751e05b1-19da-4684-8de1-3a33731382d2" />

### FCFS
<img width="545" height="292" alt="image" src="https://github.com/user-attachments/assets/8964eeed-7bd1-4f84-ae90-68be8d4f7f19" />

### Priority com RR

<img width="548" height="387" alt="image" src="https://github.com/user-attachments/assets/8646094b-6961-4460-ab4b-368d532c1a1c" />

### Priority

<img width="532" height="292" alt="image" src="https://github.com/user-attachments/assets/2d460e13-0af2-407a-b4ea-5769cd826fe6" />



