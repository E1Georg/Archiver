#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Main.h"

/*   ������������� ������ �������� ��� ��������� ������.     */
node *create_main(int frequency) {
	node *tmp = NULL;

	if ((tmp = (node*)malloc(sizeof(node))) == NULL) {
		printf("������ ������! ������ ��� ��������� node � create_main(), Tree.c �� ��������!\n");
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

/*   ������������� ������ ���� ��� ������ ��������. ������� ���� ����� ����� �������� ������ ������� � ������ �������.   */
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

// ���������� ������� �������� �� ������� ��������� ��� �������, �� ������� ����� ��������� ������ ��������.
void sorting(node *mass, int size, int position) {

	node tmp;
	for (int j = position; j < size; j++) {
		for (int i = position; i < size - 1; i++) { // size-1, ��� ��� ������������ ������� � ��������� �������.		
			if ((mass + i)->frequency > (mass + i + 1)->frequency) {
				tmp = *(mass + i);
				*(mass + i) = *(mass + i + 1);
				*(mass + i + 1) = tmp;
			}
		}
	}
}

/* ������������� �������. �� ������� symbol ��� ������� ������� � ��� �������� �������� ���������.
 * ���������� ��������� �������� ������ �������, ������� ����� ������ ��������, �� ������� ���������� ������ ��������.    */
node *waitingLine(int **symbol, int size) {

/*  ��� ����������� ����, �� ������� �������� ����� ������ ��������.
 *  ������ �������� ���� ���������� ����� ������������ �����. � ������ ������� ��������� ������� �����. */
	node *mass = NULL;

	if ((mass = (node*)malloc(size * sizeof(node))) == NULL) {
		printf("������ ������! ������ ��� ������ �������� � waitingLine(), Tree.c �� ��������!\n");
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

// ���������� ��������� ������� �� ������� ��������� ������� � ������.
	sorting(mass, size, 0); 
	return mass;
}

// ������� ���������� ��������� �� ������ ���(������������ ���� ������) "������ ��������". ����� ��������� ���� ������ ��������.
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
			printf("������ ������! ������ ��� ������ �������� � ATD(), Tree.c �� ������������!\n");
			getchar();
			exit(1);
		}
		
		mass[length - 1] = *root;
		root = NULL;
		tmp = NULL;
		sorting(mass, length, counter); // (� ����� �������, �������� �������, ��������� ������� ��� ������)
	}

	if (length - counter == 1) {
		sorting(mass, length, counter);
	}
	root = (mass + length - 1);
	return root;
}

/*  ����� ������. ����� ��� ��������� "����", ����� ����� �������� �����(��������, 1001) ��� ������� �� ������� ������. ����������� �������.
    ��� �������� "�����" ��������������� 1, ��� �������� "������" ��������������� 0.    */
void postorder(node *root, int code) {
	if (root == NULL) return;
	root->address = code;
	code = 1;
	postorder(root->left, code);
	code = 0;
	postorder(root->right, code);
	if (root->frequency) return;
}

/*  ������ ��������. ������� ������� "�����" ������ ����� � �� ����������� ������ ������� ������� � ������ �������� "�����" - "� ����� ���". */
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
			}//mass-��� ������ symbol. ����� �������, � [0][i] ����������� ASCII-��� �������, � � [1][i] ����� ��� (�� ��������).
		}
		code = code >> 1;
		return;
	}
}
