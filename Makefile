# Makefile para o Projeto de Escalonador de CPU

# Compilador e Flags
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -g

# Fontes comuns a todos os executáveis
COMMON_SRCS = driver.c cpu.c list.c
COMMON_OBJS = $(COMMON_SRCS:.c=.o)

# Alvos para cada algoritmo
all: fcfs sjf priority rr priority_rr

fcfs: scheduler_fcfs.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o fcfs scheduler_fcfs.o $(COMMON_OBJS)

sjf: scheduler_sjf.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o sjf scheduler_sjf.o $(COMMON_OBJS)

priority: scheduler_priority.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o priority scheduler_priority.o $(COMMON_OBJS)

rr: scheduler_rr.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o rr scheduler_rr.o $(COMMON_OBJS)

priority_rr: scheduler_priority_rr.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o priority_rr scheduler_priority_rr.o $(COMMON_OBJS)

# Regras de compilação
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f *.o fcfs sjf priority rr priority_rr schedule.txt