# LI2 (Português)

Programa que lê, organiza, analisa e valida combinações de cartas implementada no âmbito da cadeira de Laboratórios de Informática II. O trabalho cobre as várias fases (guiões), desde a identificação básica de cartas até à validação de jogadas num jogo de cartas. Pode consultar o [enunciado](enunciado.pdf) para saber as regras do jogo.

### Nota Final: 16 / 20 ⭐️

## Membros do grupo

* [darteescar](https://github.com/darteescar)
* [nabattis](https://github.com/NandoBF)
* [tiagofigueiredo7](https://github.com/tiagofigueiredo7)

## Input e Output

### Input

* Número de testes
* Número de jogadas anteriores
* Cartas na mão do jogador
* Histórico de jogadas
* Jogada pretendida

### Output

* Mão do jogador após a jogada (se válida)
* Mensagens de erro quando aplicável

## Compilação, Execução e Limpeza

Para compilar o projeto, utilize o `make`:

```bash
make
```

Para compilar e executar o programa principal faz-se:

```bash
make run
```

Para limpar os ficheiros objeto e executáveis basta:

```bash
make clean
```

## Notas

* O programa depende de `setlocale(LC_CTYPE, "C.UTF-8")`
* Deve ser executado num terminal com suporte a Unicode

# LI2 (English)
Program that reads, organizes, analyzes, and validates card combinations implemented within the scope of the Laboratory of Informatics II course. The work covers various phases (guides), from basic card identification to validating plays in a card game. You can read the [statement](enunciado.pdf) to understand the game rules.

### Final Grade: 16 / 20 ⭐️

## Group Members

* [darteescar](https://github.com/darteescar)
* [nabattis](https://github.com/NandoBF)
* [tiagofigueiredo7](https://github.com/tiagofigueiredo7)

## Input and Output

### Input

* Number of tests
* Number of previous plays
* Player's hand cards
* Play history
* Intended play

### Output

* Player's hand after the play (if valid)
* Error messages when applicable

## Compilation, Execution, and Cleanup

To compile the project, use `make`:

```bash
make
```

To compile and run the main program, use:

```bash
make run
```

To clean up object files and executables, use:

```bash
make clean
```

## Notes

* The program depends on `setlocale(LC_CTYPE, "C.UTF-8")`
* It should be run in a terminal that supports Unicode