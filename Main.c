#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

int main() {	
	setlocale(LC_ALL, "Rus");
	printf("Добро пожаловать!\n");
	helpPrint();
	printf("\nВведите ключ: ");

	for (;;) {

		gets(code);

		if (strcmp(code, "1") == 0) {
			printf("\nВведите имя файла, который нужно сжать. Имя должно быть с указанием расширения!\n");
			printf("Имя файла: ");
			gets(ptr_file);			
			if(compression(ptr_file)) printf("\nФайл был успешно сжат! Имя сжатого файла --> Output.bin\n");			
		}

		if (strcmp(code, "2") == 0) {
			printf("\nВведите имя файла, который нужно разжать. Файл для разжатия должен быть в формате .bin!\n");
			printf("Адрес: ");
			gets(ptr_file);
			printf("\nВведите имя файла, который будет создан в результате разжатия. Имя должно быть с указанием расширения!\n");
			printf("Имя файла: ");
			gets(out_file);
			if(unPacking(ptr_file, out_file)) printf("\nФайл был успешно разжат!");			
		}

		if (strcmp(code, "3") == 0) {
			helpPrint();
		}

		if (strcmp(code, "4") == 0) {
			printf("\nПрограмма успешно завершила свою работу!\n");
			break;
		}
		printf("\nВведите ключ: ");
	}
	return 0;
}
