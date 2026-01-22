# Projeto de Análise e Validação de Combinações de Cartas

Este projeto implementa, em **C**, um conjunto de programas e funções para **ler, organizar, analisar e validar combinações de cartas** usando símbolos Unicode de cartas (🂡, 🂢, 🂣, etc.). O trabalho cobre várias fases (guiões), desde a identificação básica de cartas até à validação de jogadas num jogo de cartas.

O código utiliza `wchar_t` e Unicode para representar cartas reais, exigindo configuração correta de *locale*.

---

## ⚙️ Funcionalidades Principais

### Identificação e Contagem

* `identificaCartas` – converte uma carta Unicode num índice interno
* `contaCartas` – conta o número de cartas numa linha de input
* `contaCartasLidas` – preenche o array de frequência das cartas

### Organização

* Ordenação das cartas por valor e naipe
* Determinação da **carta mais alta** de uma combinação

### Tipos de Combinação

O projeto identifica automaticamente:

* **Carta simples**
* **Conjunto** (cartas do mesmo valor)
* **Sequência** (valores consecutivos)
* **Dupla sequência** (pares consecutivos)

---

## 🎮 Validação de Jogadas (Guiões Avançados)

Nos módulos mais avançados, o projeto passa a simular um jogo:

### Estruturas Principais

* `MAO` – cartas do jogador
* `ULTIMAS` – últimas jogadas realizadas
* `PRETENDIDA` – jogada que o jogador quer fazer

### Regras Implementadas

* A jogada tem de estar contida na mão do jogador
* A combinação tem de ser válida
* A jogada tem de ser do **mesmo tipo** da última jogada válida
* A jogada tem de ser **maior** do que a anterior
* Regras especiais para **Reis**
* Três passes consecutivos permitem jogar qualquer combinação

Funções-chave:

* `invalida`
* `eMaior`
* `SeqEnumIguais`
* `casoDosReis`

---

## 🧪 Input e Output

### Input

* Número de testes
* Número de jogadas anteriores
* Cartas na mão do jogador
* Histórico de jogadas
* Jogada pretendida

### Output

* Mão do jogador após a jogada (se válida)
* Mensagens de erro quando aplicável

---

## 🛠️ Compilação

É obrigatório usar **UTF-8** e ativar suporte a wide characters:

```bash
gcc -Wall -Wextra -std=c11 -o cartas programa.c
```

Para modo debug:

```bash
gcc -DDEBUG programa.c -o cartas
```

---

## 📌 Notas Importantes

* O programa depende de `setlocale(LC_CTYPE, "C.UTF-8")`
* Deve ser executado num terminal com suporte a Unicode
* O código está dividido por fases (guiões), refletindo evolução incremental do projeto

---

## 👨‍💻 Autor

Projeto académico em C para manipulação e validação de combinações de cartas usando Unicode.

---

✔️ Este README descreve a lógica geral, estrutura e regras implementadas, sem depender de um ficheiro específico do código.
