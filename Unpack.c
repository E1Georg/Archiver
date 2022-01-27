#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

// Функция, отвечающая за раскодировку(разжатие) входных данных и запись их в файл вывода данных.
int unPacking(ptr_file, out_file) {

	FILE *ptr = NULL;
	FILE *Out = NULL;

	if ((ptr = fopen(ptr_file, "rb")) == NULL) {
		printf("Невозможно открыть файл с закодированным сообщением.\n");
		getchar();
		exit(1);
	}

	if ((Out = fopen(out_file, "wb")) == NULL) {
		printf("Невозможно открыть файл с раскодированным сообщением.\n");
		getchar();
		exit(1);
	}

	readeRecodeFile(ptr, Out);

	fclose(ptr);
	fclose(Out);
	return 1;
}