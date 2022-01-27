#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

/*   ������� ���������� ��������� �� ������, � ������� ���������� ���� �������� [��� �������]-[������� ���������] �� ������� �����.
 *   ������� ���������: 
 *    ��������� �� ���� ��� ������, 
 *    ��������� �� ���������� "size", � ������� ����� ��������� ����� ��������� ��������(�������) �������� �����.  */
int **frequency_array(FILE *ptr, int *sizePointer) {

	int **signArray = NULL;
	
	if ((signArray = (int**)malloc(2 * sizeof(int*))) == NULL) {
		printf("������ ������! ������ ��� ������ signArray, frequencyArray.c �� ��������!\n");
		getchar();
		exit(1);
	}	

	/*   � signArray[0][i] ������������ ��� �����, � signArray[1][i] ������������ ������� ��������� � ������ ��� ������ �����.   */
	for (int i = 0; i < 2; i++) {		
		if ((signArray[i] = (int*)malloc(256 * sizeof(int))) == NULL) {
			printf("������ ������! ������ ��� ������ signArray[%d],frequencyArray.c �� ��������!\n", i);
			getchar();
			exit(1);
		}
	}
	
	/*   ���������� ������, � ������� ����� ����� ����������� �������, � ������� ���������� ��� ��� ���� ������ �� ������� �����.   */
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

	/*  �������� �������� �������� �� ������� ����� � �������� ��������������� ���� �������� ������ "symbol".  */
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
		printf("������ ������! ������ ��� ������ symbol,frequencyArray.c �� ��������!\n");
		getchar();
		exit(1);
	}	

	/*   � symbol[0][i] ������������ ��� �������, � symbol[1][i] ������������ ������� ��������� � ������ ��� ������� �������.   */
	for (int i = 0; i < 2; i++) {		
		if ((symbol[i] = (int*)malloc(size * sizeof(int))) == NULL) {
			printf("������ ������! ������ ��� ������ symbol[%d],frequencyArray.c �� ��������!\n", i);
			getchar();
			exit(1);
		}
	}
	*sizePointer = size;

	/*   ��������� � �������� ������ ���� �������� [��� �����]-[������� ��������� � ������].   */
	int index = 0;

	for (int i = 0; i < 256; i++) {
		if (signArray[1][i] != 0) {
			symbol[0][index] = signArray[0][i];
			symbol[1][index] = signArray[1][i];
			index++;
		}
	}

	/*   ��������� ������ ������� � ���������� ��������� �� ������������ ������.   */
	for (int i = 0; i < 2; i++) {
		free(signArray[i]);
	}free(signArray);

	return symbol;
}