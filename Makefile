CC = gcc
CFLAGS = -Wall -Wextra -g

EXECUTABLES = Final Guiao_1 Guiao_2

all: $(EXECUTABLES)

Final: Final.c
	$(CC) $(CFLAGS) -o Final Final.c

Guiao_1: Guiao_1.c
	$(CC) $(CFLAGS) -o Guiao_1 Guiao_1.c

Guiao_2: Guiao_2.c
	$(CC) $(CFLAGS) -o Guiao_2 Guiao_2.c
	
Guiao_3: Guiao_3.c
	$(CC) $(CFLAGS) -o Guiao_3 Guiao_3.c

run: all
	@echo "Executando Final.c:"
	./Final < input.txt
	@echo "\nExecutando Guiao_1.c:"
	./Guiao_1 < input.txt
	@echo "\nExecutando Guiao_2.c:"
	./Guiao_2 < input.txt
	@echo "\nExecutando Guiao_3.c:"
	./Guiao_3 < input.txt

clean:
	rm -f $(EXECUTABLES)
