# Nome do Executável
PROJ_NAME=ted

# Compilador
CC=gcc

# Flags de Compilação (conforme PDF)
CFLAGS=-g -std=c99 -fstack-protector-all -Wall

# Flags de Linkagem
LDFLAGS=
LIBS=-lm

# ---- Arquivos Fonte ----
SRCS := $(wildcard *.c)

# Cria lista de arquivos .o
OBJS := $(SRCS:.c=.o)

# ---- Regras de Build ----

all: $(PROJ_NAME)

ted: $(PROJ_NAME)

# Linka todos os .o
$(PROJ_NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROJ_NAME) $(OBJS) $(LIBS)
	@echo "Executável '$(PROJ_NAME)' criado com sucesso em src/"

# Regra genérica para compilar .c para .o
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# ---- Dependências ----

main.o: arena.h chao.h processaGeo.h processaQry.h

arena.o: arena.h fila.h formas.h chao.h svg.h

carregador.o: carregador.h pilha.h formas.h chao.h

chao.o: chao.h fila.h formas.h

disparador.o: disparador.h carregador.h arena.h formas.h fila.h

estilo.o: estilo.h

fila.o: fila.h

formas.o: formas.h estilo.h svg.h

pilha.o: pilha.h

processaGeo.o: processaGeo.h chao.h fila.h formas.h estilo.h svg.h

processaQry.o: processaQry.h fila.h pilha.h chao.h arena.h carregador.h disparador.h formas.h svg.h

svg.o: svg.h

# Regra de Limpeza
clean:
	rm -f $(PROJ_NAME) *.o
	@echo "Limpeza concluída."

.PHONY: all ted clean