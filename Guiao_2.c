#include <stdio.h>

#include <locale.h>

#include <wchar.h>

#include <assert.h>

#define CARDNUM 4*14

int comparaTamanhos( int array[],int h) {
	for ( int kaka = 1 ; kaka < h ; kaka++ ) {
		if ( array[kaka] != array[kaka-1] ) return 0;
			}
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int eDuplaSequencia(int cartasLidas[]){
	int counter = 0;
	int checked[CARDNUM] = {0};

	for(int index = 0; index < CARDNUM; index++){
		if (cartasLidas[index] == 0) continue;
		if(checked[index] == 0){
			checked[index]++;
			int new_index = index + 4;
			int check_index = new_index - (new_index % 4);
			for(int i = 0; i < 4; i++){
				int to_check = check_index + i;
				if (cartasLidas[to_check] > 0 && checked[to_check] == 0){
					i=3;
					counter++;
					checked[check_index + i]++;
				}
			}
		}
	}
	return counter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int eSequencia(int cartasLidas[], int index){
	int curr_index = index;
	int finished = 0, counter = 0;

	while(!finished){
		int new_index = curr_index + 4;
		int check_index = new_index - (new_index % 4);
		if (check_index >= CARDNUM) finished = 1;
		else{ 
			for (int j = 0; j < 4; j++){
				if(check_index + j >= CARDNUM) j = 3;
				else if(cartasLidas[check_index + j] > 0){
					counter++;
					curr_index = check_index;
					#ifdef DEBUG
					wprintf(L"S: Checking index: %d, %d\n", check_index + j, cartasLidas[check_index + j]);
					#endif
					j = 5;
				}
				if(j == 3) finished =  1;
			}			
		}
	}
	if (counter > 1) counter++;
	else counter = 0;
	return counter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int eConjunto(int cartasLidas[], int index){ // index da carta atual do array cartasLidas
	int count = 0;
	for(int i = 1; i < 4; i++){
		int new_index = index + i;
		if (new_index % 4 == 0) break;
		#ifdef DEBUG
		wprintf(L"C: checking index: %d, %d\n", new_index, cartasLidas[new_index]);
		#endif
		if (new_index > CARDNUM) break; // a carta esta num index onde nao tem naipes mais altos, nao sei se podemos usar breaks.
		else if (cartasLidas[new_index] > 0) count++;
	}
	if (count != 0) count++;
	return count;
	// se count for 0 nao e um conjunto. POde se verificar tipo bool.
	// count = 0: false, counta != 0: true -> significa que a sequencia e um conjunto
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int contaCartas(wchar_t linha[]){
	int counter = 0;
	//int tamanho = sizeof(wchar_t);
	for (int i = 0; linha[i]; i++){
		counter++;
	}
	return counter - 1;
}

int tipoSequencia(int cartasLidas[], int numeroCartas){
	int tipo = -1;

	for(int i = 0; i < CARDNUM; i++){
		if ( cartasLidas[i] == 0 ) continue;
		int dupla = eDuplaSequencia(cartasLidas);
		if (eConjunto(cartasLidas, i) == numeroCartas){
			tipo = 1;
			i = CARDNUM;
		}
		else if (eSequencia(cartasLidas, i) == numeroCartas){
			tipo = 2;
			i = CARDNUM;
		}
		else if (dupla > 2 && dupla*2 >= numeroCartas){
			tipo = 3;
			i = CARDNUM;
		}
		else{
			tipo = 0;
			i = CARDNUM;
		}
	}
	return tipo;
}

int identificaCartas(wchar_t carta){
	wchar_t matriz[4][14] = {
		{0x1F0A1, 0x1F0A2, 0x1F0A3, 0x1F0A4, 0x1F0A5, 0x1F0A6, 0x1F0A7, 0x1F0A8, 0x1F0A9, 0x1F0AA, 0x1F0AB, 0x1F0AC, 0x1F0AD, 0x1F0AE}, // Espadas
		{0x1F0B1, 0x1F0B2, 0x1F0B3, 0x1F0B4, 0x1F0B5, 0x1F0B6, 0x1F0B7, 0x1F0B8, 0x1F0B9, 0x1F0BA, 0x1F0BB, 0x1F0BC, 0x1F0BD, 0x1F0BE}, // Copas
		{0x1F0C1, 0x1F0C2, 0x1F0C3, 0x1F0C4, 0x1F0C5, 0x1F0C6, 0x1F0C7, 0x1F0C8, 0x1F0C9, 0x1F0CA, 0x1F0CB, 0x1F0CC, 0x1F0CD, 0x1F0CE}, // Ouros
		{0x1F0D1, 0x1F0D2, 0x1F0D3, 0x1F0D4, 0x1F0D5, 0x1F0D6, 0x1F0D7, 0x1F0D8, 0x1F0D9, 0x1F0DA, 0x1F0DB, 0x1F0DC, 0x1F0DD, 0x1F0DE}  // Paus
	    };
	for (int i = 0; i < 5; i++){
		for(int j = 0; j < 14; j++){ //14 cartas
			if (matriz[i][j] == carta){
				return ((j*4) + i); // posicao da carta, converte da matriz para array nao separado por naipes
			// esta separado por tamanho da carta, ou seja, 4 A's primeiro, depois os 4 dois...
			}
		}
	}
	return -1;//  n encontrou a carta
}

int contaCartasLidas(wchar_t linha[], int numeroCartas, int cartasLidas[]){ //numeroCartas = numero de cartas lidas
	//talvez se deva separar este for noutra funcao por causa da complexidade
	for (int i = 0; i < numeroCartas; i++){
		int posicaoCarta = identificaCartas(linha[i]); // identifica a carta na posicao i.
		cartasLidas[posicaoCarta]++;
	}
	return 0;
}

wchar_t traduzPosicao(int index){
	
	wchar_t matriz[4][14] = {
		{0x1F0A1, 0x1F0A2, 0x1F0A3, 0x1F0A4, 0x1F0A5, 0x1F0A6, 0x1F0A7, 0x1F0A8, 0x1F0A9, 0x1F0AA, 0x1F0AB, 0x1F0AC, 0x1F0AD, 0x1F0AE}, // Espadas
		{0x1F0B1, 0x1F0B2, 0x1F0B3, 0x1F0B4, 0x1F0B5, 0x1F0B6, 0x1F0B7, 0x1F0B8, 0x1F0B9, 0x1F0BA, 0x1F0BB, 0x1F0BC, 0x1F0BD, 0x1F0BE}, // Copas
		{0x1F0C1, 0x1F0C2, 0x1F0C3, 0x1F0C4, 0x1F0C5, 0x1F0C6, 0x1F0C7, 0x1F0C8, 0x1F0C9, 0x1F0CA, 0x1F0CB, 0x1F0CC, 0x1F0CD, 0x1F0CE}, // Ouros
		{0x1F0D1, 0x1F0D2, 0x1F0D3, 0x1F0D4, 0x1F0D5, 0x1F0D6, 0x1F0D7, 0x1F0D8, 0x1F0D9, 0x1F0DA, 0x1F0DB, 0x1F0DC, 0x1F0DD, 0x1F0DE}  // Paus
	    };
	int array = index % 4;
	return matriz[array][index/4];

}

int* orgIndices(wchar_t mat[][CARDNUM], int L, int ind[]){
    int i;
    for(i = 0; i < L ; i++) ind[i] = i;    int aux;
    for(int j = 1; i < L; j++){
        aux = ind[j];
        for(int k = j; k > 0 && mat[ind[k-1]][0] > mat[aux][0]; k--)ind[k] = ind[k-1];
        ind[j] = aux;
    }
}

void organizaLinha(int cartasLidas[], int numeroCartas, wchar_t linhaOrganizada[]) {
    int index = 0;
    for(int i = 0; i < CARDNUM; i++) {
        if (cartasLidas[i] != 0) {
            linhaOrganizada[index++] = traduzPosicao(i);
        }
    }
    // Adicione o terminador de string ao final da linha organizada
    linhaOrganizada[index] = L'\0';
}

int main() {
	setlocale(LC_CTYPE, "C.UTF-8");
	int numerodetestes;
	assert(wscanf(L"%d\n", &numerodetestes) == 1);
	for ( int i = 0 ; i < numerodetestes ; i++ ) {
		int numerodelinhas;
		assert(wscanf(L"%d\n", &numerodelinhas) == 1);
		int array1[numerodelinhas]; //array para o numero de cartas
		int array2[numerodelinhas]; //array para o tipo de sequencias  
		wchar_t arrayInputsOrg[numerodelinhas][CARDNUM];
		wchar_t linhaOrganizada[BUFSIZ];
		int j;
        for ( j = 0 ; j < numerodelinhas; j++) {
			wchar_t linha[BUFSIZ];
			assert(fgetws(linha, BUFSIZ, stdin) != NULL);
			int tamanhodalinha = wcslen(linha)-1;
			array1[j] = tamanhodalinha;
			int cartasLidas[CARDNUM] = {0};
			contaCartasLidas (linha,tamanhodalinha,cartasLidas);
			array2[j] = tipoSequencia (cartasLidas,tamanhodalinha);
			organizaLinha(cartasLidas, tamanhodalinha, linhaOrganizada);
			wprintf(L"%ls\n", linhaOrganizada); // Imprimir a linha organizada
		}
        if (comparaTamanhos (array1, numerodelinhas) == 0) {printf ("Combinações não iguais!\n");}
        if (comparaTamanhos (array2, numerodelinhas) == 0) {printf ("Combinações não iguais!2\n");}

    }
}