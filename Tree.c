#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Main.h"

/*   Инициализация нового элемента для бинарного дерева.     */
node *create_main(int frequency) {
	node *tmp = NULL;

	if ((tmp = (node*)malloc(sizeof(node))) == NULL) {
		printf("Ошибка памяти! Память под структуру node в create_main(), Tree.c не выделена!\n");
		getchar();
		exit(1);
	}

	tmp->frequency = frequency;
	tmp->letter = NULL;
	tmp->address = 5;  /* default initialization*/
	tmp->parent = NULL;
	tmp->left = tmp->right = NULL;	
	return tmp;
}

/*   Инициализация нового узла для дерева Хаффмана. Частота узла будет равна сложению частот правого и левого потомка.   */
node *create_unit(node *mass, int offset) {
	node *elem_one = NULL;
	node *elem_two = NULL;
	node *new_Node = NULL;
	int frequency;

	elem_one = mass + offset;
	elem_two = mass + offset + 1;

	frequency = (elem_one->frequency) + (elem_two->frequency);
	new_Node = create_main(frequency);

	elem_one->parent = new_Node;
	elem_two->parent = new_Node;

	new_Node->left = elem_one;
	new_Node->right = elem_two;
	return new_Node;
}

// Сортировка массива структур по частоте элементов для очереди, по которой будет строиться дерево Хаффмана.
void sorting(node *mass, int size, int position) {

	node tmp;
	for (int j = position; j < size; j++) {
		for (int i = position; i < size - 1; i++) { // size-1, так как используется текущий и следующий элемент.		
			if ((mass + i)->frequency > (mass + i + 1)->frequency) {
				tmp = *(mass + i);
				*(mass + i) = *(mass + i + 1);
				*(mass + i + 1) = tmp;
			}
		}
	}
}

/* Инициализация очереди. Из массива symbol для каждого символа с его частотой создаётся структура.
 * Полученная структура является частью массива, который далее станет очередью, из которой построится дерево Хаффмана.    */
node *waitingLine(int **symbol, int size) {

/*  Это изначальные узлы, из которых строится потом дерево Хаффмана.
 *  Дерево строится путём добавления новых родительских узлов. В данной функции создаются будущие листы. */
	node *mass = NULL;

	if ((mass = (node*)malloc(size * sizeof(node))) == NULL) {
		printf("Ошибка памяти! Память под массив структур в waitingLine(), Tree.c не выделена!\n");
		getchar();
		exit(1);
	}

	for (int i = 0; i < size; i++) {
		mass[i].letter = symbol[0][i];
		mass[i].frequency = symbol[1][i];
		(mass + i)->parent = NULL;
		(mass + i)->left = NULL;
		(mass + i)->right = NULL;
		(mass + i)->address = 5;
	}

// Сортировка исходного массива по частоте появления символа в тексте.
	sorting(mass, size, 0); 
	return mass;
}

// Функция возвращает указатель на корень АТД(абстрактного типа данных) "дерево Хаффмана". Здесь создается само дерево Хаффмана.
node *ATD(node *mass, int size) {

	node *root = NULL;
	node *tmp = NULL;
	int length = size;
	int counter = 0;

	while (length - counter != 1) {
		root = create_unit(mass, counter);
		counter = counter + 2;
		length++;

		tmp = mass;
		mass = NULL;		

		if ((mass = (node*)realloc(tmp, length * sizeof(node))) == NULL) {
			printf("Ошибка памяти! Память под массив структур в ATD(), Tree.c не перевыделена!\n");
			getchar();
			exit(1);
		}
		
		mass[length - 1] = *root;
		root = NULL;
		tmp = NULL;
		sorting(mass, length, counter); // (в каком массиве, конечная позиция, начальная позиция для старта)
	}

	if (length - counter == 1) {
		sorting(mass, length, counter);
	}
	root = (mass + length - 1);
	return root;
}

/*  Обход дерева. Нужно для установки "веса", чтобы потом получить адрес(например, 1001) для каждого из листьев дерева. Рекурсивная функция.
    При повороте "влево" устанавливается 1, при повороте "вправо" устанавливается 0.    */
void postorder(node *root, int code) {
	if (root == NULL) return;
	root->address = code;
	code = 1;
	postorder(root->left, code);
	code = 0;
	postorder(root->right, code);
	if (root->frequency) return;
}

/*  Список Хаффмана. Функция получит "адрес" каждой буквы и по переданному адресу массива запишет в массив значения "Буква" - "её новый код". */
void list(node *root, int code, int **mass, int size) {

	if (root == NULL) return;

	if (root->address == 1) {
		code = code << 1;
		code++;
	}
	else code = code << 1;

	list(root->left, code, mass, size);
	list(root->right, code, mass, size);

	if (root->frequency) {
		if ((root->left == NULL) && (root->right == NULL)) {
			for (int i = 0; i < size; i++) {
				if (mass[0][i] == root->letter) mass[1][i] = code; 
			}//mass-это массив symbol. Таким образом, в [0][i] оказывается ASCII-код символа, а в [1][i] новый код (по Хаффману).
		}
		code = code >> 1;
		return;
	}
}
