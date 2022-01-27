#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

/* ������� ��������� ������ �� ��������������� �����, ������� ��������������� ������� ASCII-���, 
   ����� ���������� � ���� ������ ������ ��������� ������, �� ��� � ASCII-���������.  */
void readeRecodeFile(FILE *ptr, FILE *Out) {

	unsigned char tableSize = 0;
	fread(&tableSize, sizeof(char), 1, ptr); 
	
	int **symbol;

	if ((symbol = (int**)malloc(2 * sizeof(int*))) == NULL) {
		printf("������ ������! ������ ��� ������ symbol, Reader.c �� ��������!\n");
		getchar();
		exit(1);
	}

	for (int i = 0; i < 2; i++) {
		if ((symbol[i] = (int*)malloc(tableSize * sizeof(int))) == NULL) {
			printf("������ ������! ������ ��� ������ symbol[%d], Reader.c �� ��������!\n", i);
			getchar();
			exit(1);
		}		
	}

	unsigned char reservedBits = 0;
	fread(&reservedBits, sizeof(char), 1, ptr);
	
	long position = 0;
	unsigned char counter = 0;
	unsigned char byte = 0;

	while (counter != tableSize) { //���������� � [0][i]����� �����, � � [1][i] �� ����������� ���

		fread(&byte, sizeof(char), 1, ptr);
		symbol[0][counter] = byte;

		fread(&byte, sizeof(char), 1, ptr);
		symbol[1][counter] = byte;

		symbol[1][counter] = dec2bin(symbol[1][counter]);
		counter++;		
	}	

	byte = 0;
	int input = 0;
	unsigned char word = 0;
	unsigned char mask = 0;
	unsigned char maskLength = 0;

	while (fread(&byte, sizeof(char), 1, ptr) == 1) {

		if (byte == EOF) {
			if (feof(ptr) != 0) {
				printf("\n������ ���������!\n");				
				break;
			}
			else {
				printf("\n������ ������ �� �����!\n");				
				break;
			}
		}

		mask = 128;
		maskLength = 7;
		
		while (mask != 0) { 

			if ((byte & mask) != 0) {
				input = input * 10 + 1;
			}
			else input = input * 10;

			for (int counter = 0; counter < tableSize; counter++) {

				if (input == symbol[1][counter]) {
					word = symbol[0][counter];
					fwrite(&word, sizeof(char), 1, Out);
					input = 0;
				}
			}
			mask = mask >> 1;
			maskLength--;
			if (maskLength == -1) break;
		}
		//��������� ���� ��� ���������� �����
	}

	for (int i = 0; i < 2; i++) {
		free(symbol[i]);
	}free(symbol);
}