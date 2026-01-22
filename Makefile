CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

EXECUTABLES = Final Guiao_1 Guiao_2 Guiao_3

all: $(EXECUTABLES)

# Regra genérica: nome.c -> nome
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

run: all
	@echo "Executando Final:"
	LC_ALL=C.UTF-8 ./Final < input.txt
	@echo "\nExecutando Guiao_1:"
	LC_ALL=C.UTF-8 ./Guiao_1 < input.txt
	@echo "\nExecutando Guiao_2:"
	LC_ALL=C.UTF-8 ./Guiao_2 < input.txt
	@echo "\nExecutando Guiao_3:"
	LC_ALL=C.UTF-8 ./Guiao_3 < input.txt

clean:
	rm -f $(EXECUTABLES)
