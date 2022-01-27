#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

/*  ������� ���������� ��������� � ��������� ����. 
 *  1-�� ������ ������������ ������ ������� [������]-[��� ���], ������� �������������� ��� ������,
 *  2-������ ������������ ���������� �������� ��� � ��������� �����, ����� ������������ ���� ������� [������]-[��� ���].
 *  size - ������ ������� [������]-[��� ���], ��� �� ����� ������� symbol[i],
 *  symbol - ������, � ������� �������� �������,
 *  Out - ���� ��� ������ ���������� �������.     */
void writeHeader(int size, int **symbol, FILE *Out) {

	unsigned char data = 0;	

	fwrite(&data, sizeof(char), 1, Out); // ������������� ������(fix)
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

/*  ������� ���������� ������ �� ���������� ������� � ����. ������ ��������� � ������.
 *  ������� ������� �� ������� � 8 ���������, ����� �� ��������� �������� ����������� ����, ������� ������������ � ����.
 *  ���������� ��������, ��� ������� �� ������� ������������ ����(��� ��� �� ������ 8), �� ���� ����� �������� � ������.
 *  size - ����� �������������� ������ � ������, Out - ���� ��� ������ ���������� �������.   */
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

/*  ������� ���������� � ���� ���������� ���� �������������� ������. ������ ��������� � ������.
 *  ���� ��������� ���� ������� �������������, �� �������� ���� ���������� �����, ����� ���� ���������� ������ �����.
 *  ���������� �������� ��� � ��������� ����� ������������ � ��������� �� ������� 2-�� �����.
 *  size - ����� �������������� ������ � ������, Out - ���� ��� ������ ���������� �������.   */
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