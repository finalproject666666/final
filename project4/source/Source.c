#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_blanks(void);                                                        //�L�X�C����l����l
void open_cell(int *op_x, int *op_y);                                           //�ШϥΪ̿�J�n���}����m 6
void put_mine(int cells[][11], int op_x, int op_y);                             //��m�a�p 31
void assign_inf_after_open(int cells[][11], int op_x, int op_y);                //���ܨϥΪ̥��}����m����T
void print_cells(int cells[][11], int op_x, int op_y, int over);
//�L�X�ثe�����p
void print_condition_playing(int cells[][11]);
//�L�X�|�����������p



int main()
{
	int  cells[11][11],
		open_x, open_y;
	print_blanks();
	open_cell(&open_x, &open_y);                                             //�ШϥΪ̿�J�n���}����m
	put_mine(cells, open_x, open_y);                                         //��m�a�p
	open_cell(&open_x, &open_y);                                             //�ШϥΪ̿�J�n���}����m
	system("pause");
	return 0;
}
void print_blanks(void) {                                                       //�L�X�C����l����l 
	int i, j;
	printf("              �C�������G\n");
	printf("---------------------------------------\n");

	printf("   ���z�C���r�֡I:)\n");
	printf("---------------------------------------\n\n");
	printf("    ");
	for (i = 1; i <= 9; i++)
		printf("%2d", i);
	printf("\n");
	for (i = 1; i <= 9; i++)
	{
		for (j = 0; j <= 9; j++)
		{
			if (j == 0)
				printf("%4d", i);
			else
				printf("�f");
		}
		printf("\n");
	}
}


void open_cell(int *op_x, int *op_y) {                                          //�ШϥΪ̿�J�n���}����m
	int x, y;
	printf("\n��J�z�n�}�Ҫ��y�� >> ");
	scanf("%d%d", op_x, op_y);
}

void put_mine(int cells[][11], int op_x, int op_y) {                            //��m�a�p
	srand(time(NULL));          //  �üƺؤl 
	int  n = 0,
		rand_num,
		cell_x,
		cell_y;

	do {
		rand_num = rand() % 81;     // ( rand() % (�̤j��-�̤p��+1)) + �̤p��
		cell_x = (rand_num % 9) + 1;
		cell_y = ((rand_num - cell_x) / 9) + 1;
		if (cells[cell_x][cell_y] != -1 && !(cell_x == op_x && cell_y == op_y)) {
			cells[cell_x][cell_y] = -1;
			n++;
		}
	} while (n < 10);
}
void assign_inf_after_open(int cells[][11], int op_x, int op_y){               //���ܨϥΪ̥��}����m����T 
	if (cells[op_x][op_y] == -1)
		cells[op_x][op_y] = -2;
	if (cells[op_x][op_y] >= 0 && cells[op_x][op_y] <= 8)
		cells[op_x][op_y] += 10;
}


void print_condition_playing(int cells[][11]) {                                 //�L�X�|�����������p
	int i, j;
	printf("      ");
	for (i = 1; i <= 9; i++)
		printf("%2d", i);
	printf("\n    �z�ССССССССТ{\n");
	for (i = 1; i <= 9; i++) {
		for (j = 0; j <= 9; j++) {
			if (j == 0)
				printf("%4d�U", i);
			else if (cells[i][j] < 10)
				printf("�f");
			else if (cells[i][j] == 10)
				printf(" 0");
			else if (cells[i][j] > 10 && cells[i][j] <= 18)
				printf(" %d", cells[i][j] - 10);
			if (j == 9)
				printf("�U%d", i);
		}
		printf("\n");
	}
	printf("    �|�ССССССССТ}\n");
	printf("      ");
	for (i = 1; i <= 9; i++)
		printf("%2d", i);
	printf("\n");
}

void print_cells(int cells[][11], int op_x, int op_y, int over) {               //�L�X�ثe�����p
	system("cls");
	printf("\n");
	int i, j;
	if (over == 0) {
		print_condition_playing(cells);
	}
	else
		print_condition_over(cells, over);
}

