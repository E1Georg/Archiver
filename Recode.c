#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

/*  Функция формирует закодированную строку данных, затем записывает перекодированные данные в файл вывода данных.
 *  Из файла считывается символ, для которого находится соответствующий кодирующий код.
 *  Далее новый код символа записывается в буфер и таким образом в буфере создаётся перекодированная строка.
 *  Если буфер заполнен или достигнут конец файла, функция записывает из буфера перекодированную строку в файл вывода данных.  */
void recodeData(int **symbol, int size, FILE *input, FILE *Out) {
	
	int tmp = 0;
	int word = 0;
	int counter = 0;
	char newCode[10];
	int codeLength = 0;	

	for (int i = 0; i < size; i++) {
		symbol[1][i] = dec2bin(symbol[1][i]); // symbol[0]-обычный код символа, symbol[1]-соответствующий  новый код.
	}	

	while ((word = fgetc(input)) != EOF) {

		for (int i = 0; i < size; i++) {
			if (word == symbol[0][i]) {
				
				codeLength = numberLength(symbol[1][i]);

				if ((counter + codeLength) > BUFFER_SIZE) {
					writeBody(counter, Out);
					tmp = counter / 8;
					tmp *= 8;										
					counter = counter - tmp;				
				}

				sprintf(newCode, "%d", symbol[1][i]);
				strncat(buffer, newCode, codeLength);
				counter = counter + codeLength;				
			}
		}
	}
	if (counter != 0) writeTail(counter, Out);
}

