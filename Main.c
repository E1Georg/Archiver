#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

int main() {	
	setlocale(LC_ALL, "Rus");
	printf("����� ����������!\n");
	helpPrint();
	printf("\n������� ����: ");

	for (;;) {

		gets(code);

		if (strcmp(code, "1") == 0) {
			printf("\n������� ��� �����, ������� ����� �����. ��� ������ ���� � ��������� ����������!\n");
			printf("��� �����: ");
			gets(ptr_file);			
			if(compression(ptr_file)) printf("\n���� ��� ������� ����! ��� ������� ����� --> Output.bin\n");			
		}

		if (strcmp(code, "2") == 0) {
			printf("\n������� ��� �����, ������� ����� �������. ���� ��� �������� ������ ���� � ������� .bin!\n");
			printf("�����: ");
			gets(ptr_file);
			printf("\n������� ��� �����, ������� ����� ������ � ���������� ��������. ��� ������ ���� � ��������� ����������!\n");
			printf("��� �����: ");
			gets(out_file);
			if(unPacking(ptr_file, out_file)) printf("\n���� ��� ������� ������!");			
		}

		if (strcmp(code, "3") == 0) {
			helpPrint();
		}

		if (strcmp(code, "4") == 0) {
			printf("\n��������� ������� ��������� ���� ������!\n");
			break;
		}
		printf("\n������� ����: ");
	}
	return 0;
}