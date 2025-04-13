#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>

//tipos
typedef struct maoJogador {
    wchar_t cartas[20]; // cartas lidas
    wchar_t maiorCarta; // maior carta na mao
    int numCartas; // numero de cartas na mao
} *MAO;

typedef struct ultimasJogadas {
    wchar_t *ultima;
    wchar_t maiorUltima;
    int numUltima;
    wchar_t *penultima;
    wchar_t maiorPenultima;
    int numPenultima;
    wchar_t *antepenultima;
    wchar_t maiorAntepenultima;
    int numAntepenultima;
} *ULTIMAS;

typedef struct jogadaPretendida{
    wchar_t jogadaPretendida[20];
    wchar_t maiorPretendida;
    int numPretendida;
} *PRETENDIDA;

//funcoes referentes ao guiao A

//funcoes referentes ao guiao B
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

//funcoes referentes ao guiao C
void completaMao(MAO m) {
    m->numCartas = wcslen(m->cartas) - 1;
    organiza(m->cartas, m->numCartas);
    m->maiorCarta = ultima(m->cartas, m->numCartas);
}

void completaUltimas(ULTIMAS u, wchar_t jogadas[][20], int numJogadas) {
    u->ultima = jogadas[numJogadas - 1];
    u->numUltima = wcslen(u->ultima) - 1;
    organiza(u->ultima, u->numUltima);
    u->maiorUltima = ultima(u->ultima, u->numUltima);

    u->penultima = jogadas[numJogadas - 2];
    u->numPenultima = wcslen(u->penultima) - 1;
    organiza(u->penultima, u->numPenultima);
    u->maiorPenultima = ultima(u->penultima, u->numPenultima);

    u->antepenultima = jogadas[numJogadas - 3];
    u->numAntepenultima = wcslen(u->antepenultima) - 1;
    organiza(u->antepenultima, u->numAntepenultima);
    u->maiorAntepenultima = ultima(u->antepenultima, u->numAntepenultima);
}

void completaPretendida(PRETENDIDA p) {
    p->numPretendida = wcslen(p->jogadaPretendida) - 1;
    organiza(p->jogadaPretendida, p->numPretendida);
    p->maiorPretendida = ultima(p->jogadaPretendida, p->numPretendida);
}

void imprimeMao(MAO m) {
    int j;
    for (j = 0; j < m->numCartas-1; j++) {
        wprintf(L"%C ", m->cartas[j]);
    }
    wprintf(L"%C\n", m->cartas[j]);
    //wprintf(L"Numero de cartas: %d\n", m->numCartas);
    //wprintf(L"Maior carta: %C\n", m->maiorCarta);
}

void imprimeUltimas(ULTIMAS u) {
    wprintf(L"Ultima jogada: ");
    for (int j = 0; j < u->numUltima; j++) {
        wprintf(L"%C ", u->ultima[j]);
    }
    wprintf(L"\n");
    wprintf(L"Maior carta: %C\n", u->maiorUltima);
    wprintf(L"Numero de cartas: %d\n", u->numUltima);
    
    wprintf(L"Penultima jogada: ");
    for (int j = 0; j < u->numPenultima; j++) {
        wprintf(L"%C ", u->penultima[j]);
    }
    wprintf(L"\n");
    wprintf(L"Maior carta: %C\n", u->maiorPenultima);
    wprintf(L"Numero de cartas: %d\n", u->numPenultima);

    wprintf(L"Antepenultima jogada: ");
    for (int j = 0; j < u->numAntepenultima; j++) {
        wprintf(L"%C ", u->antepenultima[j]);
    }
    wprintf(L"\n");
    wprintf(L"Maior carta: %C\n", u->maiorAntepenultima);
    wprintf(L"Numero de cartas: %d\n", u->numAntepenultima);
}

void imprimePretendida(PRETENDIDA p) {
    wprintf(L"Pretendida: ");
    for (int j = 0; j < p->numPretendida; j++) {
        wprintf(L"%C ", p->jogadaPretendida[j]);
    }
    wprintf(L"\n");
    wprintf(L"Maior carta: %C\n", p->maiorPretendida);
    wprintf(L"Numero de cartas: %d\n", p->numPretendida);
}

void retiraJogada(MAO m, PRETENDIDA p) {
    if(m->numCartas == p->numPretendida){
        m->numCartas = 1;
        m->cartas[0] = (L'\0');
    }
    else{
        for (int i = 0; i < p->numPretendida; i++) {
            for (int j = 0; j < m->numCartas; j++) {
                if (m->cartas[j] == p->jogadaPretendida[i]) {
                    for (int k = j; k < m->numCartas - 1; k++) {
                        m->cartas[k] = m->cartas[k + 1];
                    }
                    m->numCartas--;
                    break;
                }
            }
        }
    }
}

int estaNaMao(MAO m, PRETENDIDA p){
    int i, flag;
    for (i = 0; i < p->numPretendida; i++) {
        flag = 0;
        for (int j = 0; j < m->numCartas; j++) {
            if (p->jogadaPretendida[i] == m->cartas[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) return 0;
    }
    return 1;
}

int tresPassos (ULTIMAS u) {
    if (u->ultima[0] == 'P' && u->penultima[0] == 'P' && u->antepenultima[0] == 'P'){
		return 1;
	}
    return 0;
}


int eMaior(PRETENDIDA p, ULTIMAS u){

    if(u->ultima[0]!='P'){
        if(maior(p->maiorPretendida, u->maiorUltima)) return 1;
    }else if(u->penultima[0]!='P'){
        if(maior(p->maiorPretendida, u->maiorPenultima)) return 1;
    }else if(u->antepenultima[0]!='P'){
        if(maior(p->maiorPretendida, u->maiorAntepenultima)) return 1;
    }
	return 0;
}

int eSequencia(wchar_t linha[], int n) {
    int i;
    if(n < 3) return 0;
    for(i = 0; i < n-1; i++){
        if(valor(linha[i]) == valor(linha[i+1]) - 1) continue;
        else return 0;
    }
    return 1;
}

int eDuplaSequencia(wchar_t linha[], int n) {
    int i;
    if(n < 6) return 0;
    for(i = 0; i < n-2; i+=2){
        if(valor(linha[i]) == valor(linha[i+2]) - 1) continue;
        else return 0;
    }
    return 1;
}  

int eCombinacao(wchar_t linha[], int n) {
    int i;
    if(n == 1) return 1;
    for(i = 0; i < n-1; i++){
        if(valor(linha[i]) == valor(linha[i+1])) continue;
        else return 0;
    }
    return 1;
}

int tipoSequencia(wchar_t linha[], int n) {
    if(eSequencia(linha, n)) return 1;
    if(eDuplaSequencia(linha, n)) return 2;
    if(eCombinacao(linha, n)) return 3;
    return 0;
}

int SeqEnumIguais(ULTIMAS u, PRETENDIDA p){
    if(u->ultima[0]!='P'){
        if((tipoSequencia(u->ultima, u->numUltima) == tipoSequencia(p->jogadaPretendida, p->numPretendida)) && (u->numUltima == p->numPretendida)) return 1;
    }else if(u->penultima[0]!='P'){ 
        if((tipoSequencia(u->penultima, u->numPenultima) == tipoSequencia(p->jogadaPretendida, p->numPretendida)) && (u->numPenultima == p->numPretendida)) return 1;
    }else if(u->antepenultima[0]!='P'){
        if((tipoSequencia(u->antepenultima, u->numAntepenultima) == tipoSequencia(p->jogadaPretendida, p->numPretendida)) && (u->numAntepenultima == p->numPretendida)) return 1;
    }
    return 0;
}

int eCombinacaoReis(wchar_t linha[], int n) {
    int i;
    if(n == 1 && valor(linha[0])== 14) return 1;
    for(i = 0; i < n-1; i++){
        if(valor(linha[i]) == 13 && valor(linha[i+1]) == 13) continue;
        else return 0;
    }
    return 1;
}

int casoDosReisUltima(ULTIMAS u, PRETENDIDA p){
    if((eCombinacaoReis(u->ultima, u->numUltima) && u->numUltima == 1) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 3 && p->numPretendida ==4)) return 1;
    else if((eCombinacaoReis(u->ultima, u->numUltima) && u->numUltima == 1) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 2 && p->numPretendida ==6)) return 1;
    else if((eCombinacaoReis(u->ultima, u->numUltima) && u->numUltima == 2) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 2 && p->numPretendida ==8)) return 1;
    else if((eCombinacaoReis(u->ultima, u->numUltima) && u->numUltima == 3) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 2 && p->numPretendida ==10)) return 1;
    return 0;
}

int casoDosReisPenultima(ULTIMAS u, PRETENDIDA p){
    if((eCombinacaoReis(u->penultima, u->numPenultima) && u->numPenultima == 1) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 3 && p->numPretendida ==4)) return 1;
    else if((eCombinacaoReis(u->penultima, u->numPenultima) && u->numPenultima == 1) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 2 && p->numPretendida ==6)) return 1;
    else if((eCombinacaoReis(u->penultima, u->numPenultima) && u->numPenultima == 2) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 2 && p->numPretendida ==8)) return 1;
    else if((eCombinacaoReis(u->penultima, u->numPenultima) && u->numPenultima == 3) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 2 && p->numPretendida ==10)) return 1;
    return 0;
}

int casoDosReisantePenultima(ULTIMAS u, PRETENDIDA p){
    if((eCombinacaoReis(u->antepenultima, u->numAntepenultima) && u->numAntepenultima == 1) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 3 && p->numPretendida ==4)) return 1;
    else if((eCombinacaoReis(u->antepenultima, u->numAntepenultima) && u->numAntepenultima == 1) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 2 && p->numPretendida ==6)) return 1;
    else if((eCombinacaoReis(u->antepenultima, u->numAntepenultima) && u->numAntepenultima == 2) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 2 && p->numPretendida ==8)) return 1;
    else if((eCombinacaoReis(u->antepenultima, u->numAntepenultima) && u->numAntepenultima == 3) && (tipoSequencia(p->jogadaPretendida, p->numPretendida)== 2 && p->numPretendida ==10)) return 1;
    return 0; 
}


int casoDosReis (ULTIMAS u, PRETENDIDA p){
    if(u->ultima[0]!='P'){
        if(casoDosReisUltima(u, p))return 1;
    }else if(u->penultima[0]!='P'){
        if(casoDosReisPenultima(u, p))return 1;
    }else if(u->antepenultima[0]!='P'){
        if(casoDosReisantePenultima(u, p))return 1;
    }
    return 0;

}


int invalida(MAO m , ULTIMAS u , PRETENDIDA p, int numJogadas) {
    if(!(estaNaMao(m, p))) return 1;
    if(!(tipoSequencia(p->jogadaPretendida, p->numPretendida))) return 1;
    if(numJogadas == 0) return 0; 
    if(tresPassos(u)) return 0;
    if(casoDosReis(u, p)) return 0;
    if(!(SeqEnumIguais(u, p))) return 1;
    if(!(eMaior(p,u))) return 1;
	return 0;
}

//main
int main(){
    setlocale(LC_CTYPE, "C.UTF-8");
    int numTestes;
    assert(wscanf(L"%d\n", &numTestes) == 1);
    for (int i = 0; i < numTestes; i++) {
        MAO mao;
        ULTIMAS ultimas;
        PRETENDIDA pretendida;

        mao = malloc(sizeof(struct maoJogador)); // inicializa a mao
        ultimas = malloc(sizeof(struct ultimasJogadas)); // inicializa as ultimas jogadas
        pretendida = malloc(sizeof(struct jogadaPretendida)); // inicializa a jogada pretendida

        int numJogadas;
        assert(wscanf(L"%d\n", &numJogadas) == 1); // numero de jogadas

        wchar_t jogadas[numJogadas][20]; // jogadas anteriores

        assert(fgetws(mao->cartas, 20, stdin) != NULL); // lê as cartas na mao

        for (int j = 0; j < numJogadas; j++) {
            assert(fgetws(jogadas[j], 20, stdin) != NULL); // lê as jogadas anteriores
        }
        
        assert(fgetws(pretendida->jogadaPretendida, 20, stdin) != NULL); // lê jogada pretendida
        
        completaMao(mao);
        completaUltimas(ultimas, jogadas, numJogadas);
        completaPretendida(pretendida);

        wprintf(L"Teste %d\n", i + 1);
        if(!(invalida(mao, ultimas, pretendida, numJogadas))){
			retiraJogada(mao, pretendida);
		}
		imprimeMao(mao);
        
    }
    return 0;
}