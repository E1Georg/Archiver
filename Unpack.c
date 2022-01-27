#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

// �������, ���������� �� ������������(��������) ������� ������ � ������ �� � ���� ������ ������.
int unPacking(ptr_file, out_file) {

	FILE *ptr = NULL;
	FILE *Out = NULL;

	if ((ptr = fopen(ptr_file, "rb")) == NULL) {
		printf("���������� ������� ���� � �������������� ����������.\n");
		getchar();
		exit(1);
	}

	if ((Out = fopen(out_file, "wb")) == NULL) {
		printf("���������� ������� ���� � ��������������� ����������.\n");
		getchar();
		exit(1);
	}

	readeRecodeFile(ptr, Out);

	fclose(ptr);
	fclose(Out);
	return 1;
}