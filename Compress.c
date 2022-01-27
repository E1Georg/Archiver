#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

// �������, ���������� �� �������������(������) ������� ������ � ������ �� � ���� ������ ������.
int compression(ptr_file) {

	FILE *ptr = NULL;
	int size;

	if ((ptr = fopen(ptr_file, "rb")) == NULL) {
		printf("���������� ������� ���� � �������� ����������.\n");
		getchar();
		exit(1);
	}

	//-----------------------���������� ������ ��������. ��������� ������� [��� �������]-[����� ��� �������]-----------------------//
	// ������� ������ [��� �����]-[������� ��������� � ������].		
	int **symbol = frequency_array(ptr, &size);
	
	// ������� ��������� �� ������ ��������, �� ������� ����� ���������� ������ ��������. ����� ������ ��������� - ������� ���� ������.	
	node *mass = waitingLine(symbol, size); 

	// ������� ��������� �� ������ ������ ��������. �� ������ ����� ������ ��� ���������.
	node *root = ATD(mass, size);

	// ����� ������. ��� �������� ������ ������� ���� � ���� address ����������� 1, ��� �������� ������� ������� ���� � ���� address ����������� 0.
	postorder(root, 1);	
	
	// ������� ����� ������� ����, ����� ���� � ������ symbol ������� ����� ���� ��������.
	list(root, 0, symbol, size);

	fseek(ptr, 0, SEEK_SET);
	free(mass);

	//-----------------------��������� ���������������� ������ � ������ � � ����----------------------------------------------//

	FILE *Out = NULL;

	if ((Out = fopen("Output.bin", "wb")) == NULL) {
		printf("���������� ������� ���� ��� ������ ����������������� ���������.\n");
		getchar();
		exit(1);
	}
	writeHeader(size, symbol, Out);	
	recodeData(symbol, size, ptr, Out); // ����� ����������� � ������������ � ���� ���������������� ������.	

	for (int i = 0; i < 2; i++) {
		free(symbol[i]);
	}free(symbol);
	
	fclose(ptr);
	fclose(Out);
	return 1;
}