#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

/*   Функция возвращает указатель на массив, в котором содержится пара значений [код символа]-[Частота появления] во входном файле.
 *   Входные параметры: 
 *    Указатель на файл для чтения, 
 *    указатель на переменную "size", в которую далее запишется число различных символов(алфавит) входного файла.  */
int **frequency_array(FILE *ptr, int *sizePointer) {

	int **signArray = NULL;
	
	if ((signArray = (int**)malloc(2 * sizeof(int*))) == NULL) {
		printf("Ошибка памяти! Память под массив signArray, frequencyArray.c не выделена!\n");
		getchar();
		exit(1);
	}	

	/*   В signArray[0][i] записывается код буквы, в signArray[1][i] записывается частота появления в тексте для данной буквы.   */
	for (int i = 0; i < 2; i++) {		
		if ((signArray[i] = (int*)malloc(256 * sizeof(int))) == NULL) {
			printf("Ошибка памяти! Память под массив signArray[%d],frequencyArray.c не выделена!\n", i);
			getchar();
			exit(1);
		}
	}
	
	/*   Сформируем массив, в котором затем будем фиксировать частоту, с которой появляется тот или иной символ во входном файле.   */
	for (int i = 0; i < 256; i++) {
		signArray[0][i] = i;
		signArray[1][i] = 0;
	}

	int word = 0;

	while ((word = fgetc(ptr)) != EOF) {			
		for (int i = 0; i < 256; i++) {
			if (word == signArray[0][i]) signArray[1][i]++;
		}
	}

	/*  Вычислим мощность алфавита во входном файле и создадим соответствующий этой мощности массив "symbol".  */
	int size = 0;

	for (int i = 0; i < 256; i++) {
		if (signArray[1][i] != 0) size++;
	}

	if (size == 0) {
		fclose(ptr);

		for (int i = 0; i < 2; i++) {
			free(signArray[i]);
		}free(signArray);

		printf("\nEmpty input file!");
		getchar();
		exit(1);
	}

	int **symbol = NULL;

	if ((symbol = (int**)malloc(2 * sizeof(int*))) == NULL) {
		printf("Ошибка памяти! Память под массив symbol,frequencyArray.c не выделена!\n");
		getchar();
		exit(1);
	}	

	/*   В symbol[0][i] записывается код символа, в symbol[1][i] записывается частота появления в тексте для данного символа.   */
	for (int i = 0; i < 2; i++) {		
		if ((symbol[i] = (int*)malloc(size * sizeof(int))) == NULL) {
			printf("Ошибка памяти! Память под массив symbol[%d],frequencyArray.c не выделена!\n", i);
			getchar();
			exit(1);
		}
	}
	*sizePointer = size;

	/*   Перепишем в конечный массив пары значений [код буквы]-[частота появления в тексте].   */
	int index = 0;

	for (int i = 0; i < 256; i++) {
		if (signArray[1][i] != 0) {
			symbol[0][index] = signArray[0][i];
			symbol[1][index] = signArray[1][i];
			index++;
		}
	}

	/*   Завершаем работу функции и возвращаем указатель на получившийся массив.   */
	for (int i = 0; i < 2; i++) {
		free(signArray[i]);
	}free(signArray);

	return symbol;
}