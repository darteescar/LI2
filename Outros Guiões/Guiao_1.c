#include <stdio.h>

#include <locale.h>

#include <wchar.h>

#include <assert.h>

#define CARDNUM 4*14

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



//numero de cartas lidas na linha

int contaCartas(wchar_t linha[]){

	int counter = 0;

	//int tamanho = sizeof(wchar_t);

	for (int i = 0; linha[i]; i++){

		counter++;

	}

	return counter - 1;

}



// funcoes para identificar o tipo de sequencia



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







//Funcao para ver se essa carta inicia uma sequencia

//pega no indice da carta e ve se nos proximos naipes a carta de valor a seguir existe;

//se existir, repete o processo, mudando o index para a carta encontrada

//se nao existir sai do 'while'

//retorna o numero de cartas encontradas

//se retornar 0 significa que nao é uma sequencia

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



wchar_t cartaMaisAlta(int cartasLidas[]){

	

	wchar_t matriz[4][14] = {

		{0x1F0A1, 0x1F0A2, 0x1F0A3, 0x1F0A4, 0x1F0A5, 0x1F0A6, 0x1F0A7, 0x1F0A8, 0x1F0A9, 0x1F0AA, 0x1F0AB, 0x1F0AC, 0x1F0AD, 0x1F0AE}, // Espadas

		{0x1F0B1, 0x1F0B2, 0x1F0B3, 0x1F0B4, 0x1F0B5, 0x1F0B6, 0x1F0B7, 0x1F0B8, 0x1F0B9, 0x1F0BA, 0x1F0BB, 0x1F0BC, 0x1F0BD, 0x1F0BE}, // Copas

		{0x1F0C1, 0x1F0C2, 0x1F0C3, 0x1F0C4, 0x1F0C5, 0x1F0C6, 0x1F0C7, 0x1F0C8, 0x1F0C9, 0x1F0CA, 0x1F0CB, 0x1F0CC, 0x1F0CD, 0x1F0CE}, // Ouros

		{0x1F0D1, 0x1F0D2, 0x1F0D3, 0x1F0D4, 0x1F0D5, 0x1F0D6, 0x1F0D7, 0x1F0D8, 0x1F0D9, 0x1F0DA, 0x1F0DB, 0x1F0DC, 0x1F0DD, 0x1F0DE}  // Paus

	    };

	int curr_index = 0;

	for(int i = 0; i < CARDNUM; i++){

		if (cartasLidas[i] > 0) curr_index = i;

	}

	int array = curr_index % 4;

	return matriz[array][curr_index/4];

}





//funcao para identificar as sequencias dado o array com as cartas encontradas

//para a carta ser de naipe diferente com mesmo valor deve ser so somar o nº de cartas por naipe

//para ver se sao seguidas é so verificar o index seguinte para cada naipe.

//nao sei se tem mais possiveis sequencias

int identificaSequencia(int cartasLidas[], int numeroCartas){

	int counter = 0;

	int carta_mais_alta = cartaMaisAlta(cartasLidas);

	int dupla = eDuplaSequencia(cartasLidas);

	if (numeroCartas == 1){

		wprintf(L"conjunto com 1 cartas onde a carta mais alta é %C\n", carta_mais_alta);

               	return 0;

	}

	for(int i = 0; i <CARDNUM; i++){

		if(cartasLidas[i] != 0){		



			counter = eConjunto(cartasLidas, i);

			if(counter == numeroCartas){

				wprintf(L"conjunto com %d cartas onde a carta mais alta é %C\n", counter, carta_mais_alta);

				return 0;

			}

			counter = eSequencia(cartasLidas, i);

			if(counter == numeroCartas){

				wprintf(L"sequência com %d cartas onde a carta mais alta é %C\n", counter, carta_mais_alta);

				return 0;

			}

		}

	}



	if (dupla > 2 && dupla * 2 >= numeroCartas) {

		wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %C\n", numeroCartas/2, carta_mais_alta);

		return 0;

	}



	wprintf(L"Nada!\n");

	return 0;

}







//funcao para meter as cartas encontradas no array; Adiciona 1 na posicao

int contaCartasLidas(wchar_t linha[], int numeroCartas, int cartasLidas[]){ //numeroCartas = numero de cartas lidas



	//talvez se deva separar este for noutra funcao por causa da complexidade

	for (int i = 0; i < numeroCartas; i++){

		int posicaoCarta = identificaCartas(linha[i]); // identifica a carta na posicao i.

		cartasLidas[posicaoCarta]++;

	}

		

	return 0;

}











int main() {

	setlocale(LC_CTYPE, "C.UTF-8");

	int num;

	assert(wscanf(L"%d\n", &num) == 1); //numero de linhas para ler

	//wchar_t inputs[num][BUFSIZ];

	for (int i = 0; i < num; i++){

		wchar_t input[BUFSIZ];

		assert(fgetws(input, BUFSIZ, stdin) != NULL);

		int cartasLidas[CARDNUM] = {0};

		int numeroCartas = contaCartas(input);

		contaCartasLidas(input, numeroCartas, cartasLidas);

		int r = identificaSequencia(cartasLidas, numeroCartas);

		if (r+1 != 0) continue;

	}

	

	//for(int j = 0; j < num; j++){



	//	int cartasLidas[CARDNUM] = {0};

	//	int numeroCartas = contaCartas(inputs[j]);

	//	contaCartasLidas(inputs[j], numeroCartas, cartasLidas);

	//	identificaSequencia(cartasLidas, numeroCartas);

	//}



	#ifdef DEBUG

	//int pos = identificaCartas(inputs[0][0]);

	int numero = contaCartas(inputs[0]);

	//wprintf(L"Numero de cartas : %d\n", numero);

	//wprintf(L"Posicao da primeira carta:%d\n", pos);

	contaCartasLidas(inputs[0], numero, cartasLidas);//para testes, passar uma das inputs de baixo, feitas para teste



	identificaSequencia(cartasLidas, numero);

	//wprintf(L"a carta mais alta é %ls\n", cartaMaisAlta(cartasLidas));

	#endif

	// compilar com gcc -DDEBUG file_name.c



	return 0;

}



//input teste conjunto : 🂡🂱🃁🃑

//input teste sequencia: 🂡🂢🂣🂤