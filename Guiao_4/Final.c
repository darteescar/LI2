#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#define CARDNUM 4*14

//tipos
typedef struct maoJogador {
    wchar_t cartas[CARDNUM]; // cartas na mao
    wchar_t maiorCarta; // maior carta na mao
    int numCartas; // numero de cartas na mao
} *MAO;

typedef struct ultimaCombinacao{
    wchar_t ultima[CARDNUM]; //ultima combinacao
    wchar_t maiorUltima; //maior carta da ultima combinacao
    int numUltima; //numero de cartas na ultima combinacao
} *ULTIMA;

//funcoes
void swap(int a[], int i, int j) {
    int aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

int naipe(wchar_t carta) {
    wchar_t baralho[4][14] = {
        {0x1F0A1, 0x1F0A2, 0x1F0A3, 0x1F0A4, 0x1F0A5, 0x1F0A6, 0x1F0A7, 0x1F0A8, 0x1F0A9, 0x1F0AA, 0x1F0AB, 0x1F0AC, 0x1F0AD, 0x1F0AE}, // Espadas
        {0x1F0B1, 0x1F0B2, 0x1F0B3, 0x1F0B4, 0x1F0B5, 0x1F0B6, 0x1F0B7, 0x1F0B8, 0x1F0B9, 0x1F0BA, 0x1F0BB, 0x1F0BC, 0x1F0BD, 0x1F0BE}, // Copas
        {0x1F0C1, 0x1F0C2, 0x1F0C3, 0x1F0C4, 0x1F0C5, 0x1F0C6, 0x1F0C7, 0x1F0C8, 0x1F0C9, 0x1F0CA, 0x1F0CB, 0x1F0CC, 0x1F0CD, 0x1F0CE}, // Ouros
        {0x1F0D1, 0x1F0D2, 0x1F0D3, 0x1F0D4, 0x1F0D5, 0x1F0D6, 0x1F0D7, 0x1F0D8, 0x1F0D9, 0x1F0DA, 0x1F0DB, 0x1F0DC, 0x1F0DD, 0x1F0DE}  // Paus
    };
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            if (carta == baralho[i][j]) return i;
        }
    }
    return -1;
}

int valor(wchar_t carta) {
    wchar_t baralho[4][14] = {
        {0x1F0A1, 0x1F0A2, 0x1F0A3, 0x1F0A4, 0x1F0A5, 0x1F0A6, 0x1F0A7, 0x1F0A8, 0x1F0A9, 0x1F0AA, 0x1F0AB, 0x1F0AC, 0x1F0AD, 0x1F0AE}, // Espadas
        {0x1F0B1, 0x1F0B2, 0x1F0B3, 0x1F0B4, 0x1F0B5, 0x1F0B6, 0x1F0B7, 0x1F0B8, 0x1F0B9, 0x1F0BA, 0x1F0BB, 0x1F0BC, 0x1F0BD, 0x1F0BE}, // Copas
        {0x1F0C1, 0x1F0C2, 0x1F0C3, 0x1F0C4, 0x1F0C5, 0x1F0C6, 0x1F0C7, 0x1F0C8, 0x1F0C9, 0x1F0CA, 0x1F0CB, 0x1F0CC, 0x1F0CD, 0x1F0CE}, // Ouros
        {0x1F0D1, 0x1F0D2, 0x1F0D3, 0x1F0D4, 0x1F0D5, 0x1F0D6, 0x1F0D7, 0x1F0D8, 0x1F0D9, 0x1F0DA, 0x1F0DB, 0x1F0DC, 0x1F0DD, 0x1F0DE}  // Paus
    };
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            if (carta == baralho[i][j]) return j;
        }
    }
    return -1;
}

int maior(wchar_t a, wchar_t b) {
    if (valor(a) == valor(b)) {
        if (naipe(a) > naipe(b)) return 1;
    } else if (naipe(a) == naipe(b)) {
        if (valor(a) > valor(b)) return 1;
    } else if (naipe(a) != naipe(b)) {
        if (valor(a) > valor(b)) return 1;
    }
    return 0;
}

void bubble(wchar_t a[], int n) {
    int i;
    for (i = 1; i < n; i++)
        if (maior(a[i - 1], a[i]))
            swap(a, i - 1, i);
}

void organiza(wchar_t a[], int n) {
    int i;
    for (i = n; i > 0; i--)
        bubble(a, i);
}

wchar_t ultima(wchar_t linha[], int n) {
    return linha[n - 1];
}

int eDuplaSequencia(wchar_t linha[], int n) {
    int i;
    if(n < 6) return 0;
    for(i = 0; i < n-2; i+=2){
        if(valor(linha[i]) == valor(linha[i+2]) - 1) continue;
        else return 0;
    }
    for(i = 0; i < n-1; i+=2){
        if(valor(linha[i]) == valor(linha[i+1])) continue;
        else return 0;
    }
    return 1;
}

int tipoSequencia(wchar_t linha[], int n) {
    if(eDuplaSequencia(linha, n)) return 2;
    return 0;
}

void completaMao(MAO m) {
    m->numCartas = wcslen(m->cartas) - 1;
    organiza(m->cartas, m->numCartas);
    m->maiorCarta = ultima(m->cartas, m->numCartas);
}

void completaUltima(ULTIMA u) {
    u->numUltima = wcslen(u->ultima) - 1;
    organiza(u->ultima, u->numUltima);
    u->maiorUltima = ultima(u->ultima, u->numUltima);
}

void imprimeMao(MAO m) {
    if (m->numCartas == 0) {
        wprintf(L"\n");
    } else {
        int j;
        for (j = 0; j < m->numCartas - 1; j++) {
            wprintf(L"%C ", m->cartas[j]);
        }
        wprintf(L"%C\n", m->cartas[j]);
    }
}

// Função para calcular o fatorial
int fatorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * fatorial(n - 1);
}

// Função para calcular o número de combinações 2 a 2
int combinacoes(int n) {
    return fatorial(n) / (fatorial(2) * fatorial(n - 2));
}


/*
-----------------------
Gera Duplas Sequencias
-----------------------
*/

void insereCombNaMatriz (wchar_t matrizCartas[], wchar_t matriz[][2], int numElementosPorLinhaNaLinhaJ, wchar_t maior) {
    if ( numElementosPorLinhaNaLinhaJ == 2 ) {
        memcpy(matriz[0], matrizCartas, 2 * sizeof(wchar_t));
    }
    if ( numElementosPorLinhaNaLinhaJ == 3 ) {
        // Imaginando que temos uma array de 3 elementos [1, 2, 3]
        // Insere [1, 2] na linha 0
        memcpy(matriz[0], matrizCartas, 2 * sizeof(wchar_t));
        // Insere [1, 3] na linha 1
        matriz[1][0] = matrizCartas[0];
        matriz[1][1] = matrizCartas[2];
        // Insere [2, 3] na linha 2
        memcpy(matriz[2], matrizCartas + 1, 2 * sizeof(wchar_t));
    
    }
    if ( numElementosPorLinhaNaLinhaJ == 4 ) {
        // Imaginando que temos uma array de 4 elementos [1, 2, 3, 4]
        // Insere [1, 2] na linha 0
        memcpy(matriz[0], matrizCartas, 2 * sizeof(wchar_t));
        // Insere [1, 3] na linha 1
        matriz[1][0] = matrizCartas[0];
        matriz[1][1] = matrizCartas[2];
        matriz[1][2] = '\0';
        // Insere [1, 4] na linha 2
        matriz[2][0] = matrizCartas[0];
        matriz[2][1] = matrizCartas[3];
        matriz[2][2] = '\0';
        // Insere [2, 3] na linha 3
        memcpy(matriz[3], matrizCartas + 1, 2 * sizeof(wchar_t));
        // Insere [2, 4] na linha 4
        matriz[4][0] = matrizCartas[1];
        matriz[4][1] = matrizCartas[3];
        matriz[4][2] = '\0';
        // Insere [3, 4] na linha 5
        memcpy(matriz[5], matrizCartas + 2, 2 * sizeof(wchar_t));

    }
    return;
}

void geraDuplasSequencias6 ( wchar_t** matrizCartas, int j, int i, int i1 , int i2, wchar_t maior, int r) {

    int colunas1 = combinacoes(i);
    int colunas2 = combinacoes(i1);
    int colunas3 = combinacoes(i2);

    wchar_t matriz1 [colunas1][2];
    wchar_t matriz2 [colunas2][2]; 
    wchar_t matriz3 [colunas3][2];

    insereCombNaMatriz (matrizCartas[j], matriz1, i, maior);
    insereCombNaMatriz (matrizCartas[j+1], matriz2, i1, maior);
    insereCombNaMatriz (matrizCartas[j+2], matriz3, i2, maior);

    for ( int i = 0 ; i < colunas1 ; i++ ) {
        for ( int i1 = 0 ; i1 < colunas2 ; i1++ ) {
            for ( int i2 = 0 ; i2 < colunas3 ; i2++ ) {
                wprintf(L"%C %C %C %C %C %C\n",matriz1[i][0],matriz1[i][1],matriz2[i1][0],matriz2[i1][1],matriz3[i2][0],matriz3[i2][1]);
            } 
        }
    }

    return;
}

void geraDuplasSequencias8 ( wchar_t** matrizCartas,int j, int i, int i1 , int i2, int i3, wchar_t maiorDaUlt, int r) {

    int colunas1 = combinacoes(i);
    int colunas2 = combinacoes(i1);
    int colunas3 = combinacoes(i2);
    int colunas4 = combinacoes(i3);

    wchar_t matriz1 [colunas1][2];
    wchar_t matriz2 [colunas2][2]; 
    wchar_t matriz3 [colunas3][2];
    wchar_t matriz4 [colunas4][2];

    insereCombNaMatriz (matrizCartas[j], matriz1, i, maiorDaUlt);
    insereCombNaMatriz (matrizCartas[j+1], matriz2, i1, maiorDaUlt);
    insereCombNaMatriz (matrizCartas[j+2], matriz3, i2, maiorDaUlt);
    insereCombNaMatriz (matrizCartas[j+3], matriz4, i3, maiorDaUlt);

    for ( int i = 0 ; i < colunas1 ; i++ ) {
        for ( int i1 = 0 ; i1 < colunas2 ; i1++ ) {
            for ( int i2 = 0 ; i2 < colunas3 ; i2++ ) {
                for ( int i3 = 0 ; i3 < colunas4 ; i3++ ) {
                    wprintf(L"%C %C %C %C %C %C %C %C\n",matriz1[i][0],matriz1[i][1],matriz2[i1][0],matriz2[i1][1],matriz3[i2][0],matriz3[i2][1],matriz4[i3][0],matriz4[i3][1]);}
        }
    }
    }

    return;
}

void geraDuplasSequencias10 ( wchar_t** matrizCartas,int j, int i, int i1 , int i2, int i3, int i4, wchar_t maior, int r) {

    int colunas1 = combinacoes(i);
    int colunas2 = combinacoes(i1);
    int colunas3 = combinacoes(i2);
    int colunas4 = combinacoes(i3);
    int colunas5 = combinacoes(i4);

    wchar_t matriz1 [colunas1][2];
    wchar_t matriz2 [colunas2][2]; 
    wchar_t matriz3 [colunas3][2];
    wchar_t matriz4 [colunas4][2];
    wchar_t matriz5 [colunas5][2];

    insereCombNaMatriz (matrizCartas[j], matriz1, i, maior);
    insereCombNaMatriz (matrizCartas[j+1], matriz2, i1, maior);
    insereCombNaMatriz (matrizCartas[j+2], matriz3, i2, maior);
    insereCombNaMatriz (matrizCartas[j+3], matriz4, i3, maior);
    insereCombNaMatriz (matrizCartas[j+4], matriz5, i4, maior);

    for ( int i = 0 ; i < colunas1 ; i++ ) {
        for ( int i1 = 0 ; i1 < colunas2 ; i1++ ) {
            for ( int i2 = 0 ; i2 < colunas3 ; i2++ ) {
                for ( int i3 = 0 ; i3 < colunas4 ; i3++ ) {
                    for ( int i4 = 0 ; i4 < colunas5 ; i4++ ) {
                        wprintf(L"%C %C %C %C %C %C %C %C %C %C\n",matriz1[i][0],matriz1[i][1],matriz2[i1][0],matriz2[i1][1],matriz3[i2][0],matriz3[i2][1],matriz4[i3][0],matriz4[i3][1],matriz5[i4][0],matriz5[i4][1]);
                    } 
                }
            } 
        }
    }

    return;
}


wchar_t** divideEmLinhas(MAO m, int *numElementosPorLinha) {

    wchar_t** matriz = malloc(14 * sizeof(wchar_t*)); // Aloca memória para as linhas
    int contador[14] = {0}; // Contador para cada linha
    int i;
    for (i = 0; i < 14 ; i++) {
        matriz[i] = malloc(4 * CARDNUM * sizeof(wchar_t)); // Aloca memória para cada linha
    }
    
    // Copia para cada linha as cartas com o mesmo valor
    for (i = 0; i < m->numCartas; i++) {
         
        int valorAtual = valor(m->cartas[i]);

        wcscpy(matriz[valorAtual] + contador[valorAtual]++, &m->cartas[i]);

    }

    // Calcula o número de elementos em cada linha
    for (i = 0; i < 14; i++) {
        numElementosPorLinha[i] = contador[i];
    }

    return matriz;
}

void duplaSequenciaUtil(MAO m, ULTIMA u, wchar_t data[], int start, int index, int r, int *passo) {

    int numElementosPorLinha[14] = {0}; // Array para armazenar o número de elementos em cada linha

    wchar_t** matrizCartas = divideEmLinhas(m, numElementosPorLinha);

    wchar_t maiorCarta = u->maiorUltima;

    if ( r == 6 ) {

        for ( int i = 0 ; i < 11 ; i++ ) {
            if ( numElementosPorLinha[i] >= 2 && numElementosPorLinha[i+1] >= 2 && numElementosPorLinha[i+2] >= 2 && ( maior(matrizCartas[i+2][(numElementosPorLinha[i+2]-1)], maiorCarta) )) {
                geraDuplasSequencias6 (matrizCartas, i, numElementosPorLinha[i], numElementosPorLinha[i+1], numElementosPorLinha[i+2], maiorCarta, r);
                *passo = 1;
            }
        }

    } else if ( r == 8 ) {

    for ( int i = 0 ; i < 10 ; i++ ) {

        if ( numElementosPorLinha[i] >= 2 && numElementosPorLinha[i+1] >= 2 && numElementosPorLinha[i+2] >= 2 && numElementosPorLinha[i+3] >= 2 && ( maior(matrizCartas[i+3][(numElementosPorLinha[i+3]-1)], maiorCarta) )) {
            geraDuplasSequencias8 (matrizCartas,i, numElementosPorLinha[i], numElementosPorLinha[i+1], numElementosPorLinha[i+2], numElementosPorLinha[i+3], maiorCarta, r);
            *passo = 1;
            }
        }
    } else if ( r == 10 ) {
            
    for ( int i = 0 ; i < 9 ; i++ ) {

            if ( numElementosPorLinha[i] >= 2 && numElementosPorLinha[i+1] >= 2 && numElementosPorLinha[i+2] >= 2 && numElementosPorLinha[i+3] >= 2 && numElementosPorLinha[i+4] >= 2 && ( maior(matrizCartas[i+3][(numElementosPorLinha[i+4]-1)], maiorCarta) )) {
            geraDuplasSequencias10 (matrizCartas, i, numElementosPorLinha[i], numElementosPorLinha[i+1], numElementosPorLinha[i+2], numElementosPorLinha[i+3], numElementosPorLinha[i+4] ,  maiorCarta, r);
            *passo = 1;
            }
        }
    }    
    return;
}

int printDuplaSequencia (MAO m, ULTIMA u) {
    wchar_t data[u->numUltima];
    int passo = 0;
    duplaSequenciaUtil(m, u, data, 0, 0, u->numUltima, &passo);
    return passo;
}


/*
-----
Main
-----
*/

void printPasso(int passo){
    if(!passo){
        wprintf(L"PASSO\n");
    }
}


int tseqUtil(int tseq, MAO m, ULTIMA u){
    
    if (tseq == 2) return printDuplaSequencia(m,u);
    
    return -1;
}

void decide(MAO m, ULTIMA u, int tseq) {
    int passo;
    if(tseq == 2){
            passo = printDuplaSequencia(m,u);
            printPasso(passo);
    }
}

int main(){
    setlocale(LC_CTYPE, "C.UTF-8");

    int nTestes;
    assert(wscanf(L"%d\n", &nTestes) == 1);
    for(int i = 0; i < nTestes; i++){
        MAO m;
        ULTIMA u;

        m = malloc(sizeof(struct maoJogador));//inicializa a mao
        u = malloc(sizeof(struct ultimaCombinacao));//inicializa a ultima combinacao

        assert(fgetws(u->ultima, CARDNUM, stdin) != NULL);
        assert(fgetws(m->cartas, CARDNUM, stdin) != NULL);

        completaUltima(u);
        completaMao(m);
        
        int tseq = tipoSequencia(u->ultima, u->numUltima);
        wprintf(L"Teste %d\n", i + 1);

        decide ( m ,u , tseq);
           
    }
    return 0;
}