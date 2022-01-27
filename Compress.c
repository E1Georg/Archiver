#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "Main.h"

// Функция, отвечающая за перекодировку(сжатие) входных данных и запись их в файл вывода данных.
int compression(ptr_file) {

	FILE *ptr = NULL;
	int size;

	if ((ptr = fopen(ptr_file, "rb")) == NULL) {
		printf("Невозможно открыть файл с исходным сообщением.\n");
		getchar();
		exit(1);
	}

	//-----------------------Построение дерева Хаффмана. Получение таблицы [код символа]-[новый код символа]-----------------------//
	// Получим массив [код буквы]-[частота появления в тексте].		
	int **symbol = frequency_array(ptr, &size);
	
	// Получим указатель на массив структур, из которых потом построится дерево Хаффмана. Здесь каждая структура - будущий лист дерева.	
	node *mass = waitingLine(symbol, size); 

	// Получим указатель на корень дерева Хаффмана. На данном этапе дерево уже построено.
	node *root = ATD(mass, size);

	// Обход дерева. При повороте налево каждому узлу в поле address установится 1, при повороте направо каждому узлу в поле address установится 0.
	postorder(root, 1);	
	
	// Получим адрес каждого узла, после чего в массив symbol запишем новые коды символов.
	list(root, 0, symbol, size);

	fseek(ptr, 0, SEEK_SET);
	free(mass);

	//-----------------------Получение перекодированной строки и запись её в файл----------------------------------------------//

	FILE *Out = NULL;

	if ((Out = fopen("Output.bin", "wb")) == NULL) {
		printf("Невозможно открыть файл для записи перекодированного сообщения.\n");
		getchar();
		exit(1);
	}
	writeHeader(size, symbol, Out);	
	recodeData(symbol, size, ptr, Out); // Здесь формируется и записывается в файл перекодированная строка.	

	for (int i = 0; i < 2; i++) {
		free(symbol[i]);
	}free(symbol);
	
	fclose(ptr);
	fclose(Out);
	return 1;
}