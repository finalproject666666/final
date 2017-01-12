#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_blanks(void);                                                        //�L�X�C����l����l
void open_cell(int *op_x, int *op_y);                                           //�ШϥΪ̿�J�n���}����m 6
void put_mine(int cells[][11], int op_x, int op_y);								//��m�a�p 31
void calculate_num_of_cells(int cells[][11]);
void assign_inf_after_open(int cells[][11], int op_x, int op_y);


int main()
{
	int  cells[11][11],
		open_x, open_y;
	print_blanks();
	open_cell(&open_x, &open_y);                                             //�ШϥΪ̿�J�n���}����m
	put_mine(cells, open_x, open_y);										//��m�a�p
	calculate_num_of_cells(cells);											//�p��D�a�p�Ϫ��񦳴X���a�p
	assign_inf_after_open(cells, open_x, open_y);							//���ܨϥΪ̥��}����m����T

	
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
void calculate_num_of_cells(int cells[][11]) {                                  //�p��D�a�p�Ϫ��񦳴X�u�a�p 
	int i, j, u, v;
	for (i = 1; i <= 9; i++)
	for (j = 1; j <= 9; j++)
	if (cells[i][j] == 0)							    //�Y�S����a�p�h�N�ˬd�g�򦳴X�Ӧa�p�N
	for (u = i - 1; u <= i + 1; u++)					//�N������m�ƭȥ[�h��
	for (v = j - 1; v <= j + 1; v++)
	if (cells[u][v] == -1)
		cells[i][j]++;
}
void assign_inf_after_open(int cells[][11], int op_x, int op_y) {               //���ܨϥΪ̥��}����m����T 
	if (cells[op_x][op_y] == -1)
		cells[op_x][op_y] = -2;
	if (cells[op_x][op_y] >= 0 && cells[op_x][op_y] <= 8)
		cells[op_x][op_y] += 10;
}
