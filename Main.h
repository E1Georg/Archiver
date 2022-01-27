#define MAX_FILE_NAME 1024
#define MAX_CODE 10
#define BUFFER_SIZE 50

char ptr_file[MAX_FILE_NAME];
char out_file[MAX_FILE_NAME];
char code[MAX_CODE];

/*  �����, � ������� ���������� ���������������� ������. ����� �� ������ ������ ������������ � ����. */
char buffer[BUFFER_SIZE];

/*  ��������� ���� ��� ������ ��������. */
typedef struct tree {
	int frequency;			// ������� ���������� �����;
	char letter;			// ��� �������;
	int address;     		// ����� ����. �� ������ ����������� ����� ��� ��� �������;
	struct tree *left;
	struct tree *right;
	struct tree *parent;
}node;