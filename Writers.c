#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

/*  Функция записывает заголовок в сжимаемый файл. 
 *  1-ым байтом записывается размер таблицы [символ]-[его код], которая использовалась для сжатия,
 *  2-байтом записывается количество полезных бит в последнем байте, далее записывается сама таблица [символ]-[его код].
 *  size - размер таблицы [символ]-[его код], она же длина массива symbol[i],
 *  symbol - массив, в который помещена таблица,
 *  Out - файл для записи сжимаемого объекта.     */
void writeHeader(int size, int **symbol, FILE *Out) {

	unsigned char data = 0;	

	fwrite(&data, sizeof(char), 1, Out); // инициализация записи(fix)
	fseek(Out, 0, SEEK_SET);

	data = size;			
	fwrite(&data, sizeof(char), 1, Out);

	data = 0;
	fwrite(&data, sizeof(char), 1, Out);

	int input = 0;

	for (int i = 0; i < size; i++) {
		data = symbol[0][i];
		fwrite(&data, sizeof(char), 1, Out);

		data = symbol[1][i];
		fwrite(&data, sizeof(char), 1, Out);
	}
}

/*  Функция записывает строку со сжимаемыми данными в файл. Строка находится в буфере.
 *  Символы берутся по группам в 8 элементов, затем из выбранных символов формируется байт, который записывается в файл.
 *  Оставшиеся элементы, для которых не удалось сформировать байт(так как их меньше 8), на этом этапе остаются в буфере.
 *  size - длина закодированной строки в буфере, Out - файл для записи сжимаемого объекта.   */
void writeBody(int size, FILE *Out) {

	unsigned char byte = 0;
	int counter = 0;
	int index = 0;

	int permittedSize = size;
	permittedSize /= 8;
	permittedSize *= 8;

	while (index != permittedSize) {
		
		if (buffer[index] == '1') {
			byte = byte << 1;
			byte++;
			counter++;
		}else if (buffer[index] == '0') {
			byte = byte << 1;
			counter++;
		}
		if (counter == 8) {
			fwrite(&byte, sizeof(char), 1, Out);
			counter = 0;
		}
		index++;
	}
	
	index = 0;
	counter = permittedSize;
	
	while (counter != size) {
		buffer[index] = buffer[counter];		
		index++;
		counter++;
	}
	buffer[index] = '\0';
}

/*  Функция записывает в файл оставшиеся биты закодированной строки. Строка находится в буфере.
 *  Если последний байт остаётся незаполненным, то полезные биты сдвигаются влево, после чего происходит запись байта.
 *  Количество полезных бит в последнем байте записывается в заголовок на позицию 2-го байта.
 *  size - длина закодированной строки в буфере, Out - файл для записи сжимаемого объекта.   */
void writeTail(int size, FILE *Out) {

	int index = 0;
	int counter = 0;
	unsigned char byte = 0;

	while (index != size) {
		
		if (buffer[index] == '1') {
			byte = byte << 1;
			byte++;
			counter++;
		}else if (buffer[index] == '0') {
			byte = byte << 1;
			counter++;
		}
		if (counter == 8) {
			fwrite(&byte, sizeof(char), 1, Out);			
			counter = 0;
			byte = 0;
		}
		index++;
	}
	
	if (counter != 0) {
		counter = 8 - counter;
		byte = byte << counter;
		fwrite(&byte, sizeof(char), 1, Out);
		counter = 8 - counter;
	}

	fseek(Out, 1, SEEK_SET);	
	fwrite(&counter, sizeof(char), 1, Out);
}
