#define MAX_FILE_NAME 1024
#define MAX_CODE 10
#define BUFFER_SIZE 50

char ptr_file[MAX_FILE_NAME];
char out_file[MAX_FILE_NAME];
char code[MAX_CODE];

/*  Буфер, в который помещается перекодированная строка. Далее из буфера данные записываются в файл. */
char buffer[BUFFER_SIZE];

/*  Структура узла для дерева Хаффмана. */
typedef struct tree {
	int frequency;			// Частота повторения буквы;
	char letter;			// Код символа;
	int address;     		// Адрес узла. По адресу формируется новый код для символа;
	struct tree *left;
	struct tree *right;
	struct tree *parent;
}node;
