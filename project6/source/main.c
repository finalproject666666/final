#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void ZERO(int cells[][17]);                                                 //��l��CELL  6
void BEGINNING(void);                                                       //��ܥX��}�l�����A  6
void OPEN(int *op_x, int *op_y);                                            //��J���}����m 6
void PUT_BOMB(int cells[][17], int op_x, int op_y);                         //��a�p��JCELL 31
void HOW_MANY_BOMB(int cells[][17]);                                        //�p����񪺦a�p�� 31
void CHANGE(int cells[][17], int op_x, int op_y);                           //���ܥ��}����m����T  31
void OPEN_SURROUNDING(int cells[][17], int p_x, int op_y);                  //���}���񪺰ϰ�  33 
void CHECK_BOMB(int cells[][17], int op_x, int op_y);                       //�ˬd���񪺰ϰ즳�S���a�p 33
int  WIN_LOSE(int cells[][17], int op_x, int op_y);                         //�ˬdWIN OR LOSE 33
void PRINT_STATUS(int cells[][17], int op_x, int op_y, int over);           //�L�X�ثe�����p   37
void PRINT_PLAYING_STATUS(int cells[][17]);                                 //�L�X�|�����������p  37
void PRINT_ENDING_STATUS(int cells[][17], int over);                        //�L�X�C�����������p 23 
char AGAIN(void);                                                           //PLAY AGAIN ?  23

int main(void) {
	int  cells[17][17],
		open_x, open_y,
		over;
	char again;

	do {
		system("cls");
		ZERO(cells);                                                        //��l��CELL
		BEGINNING();                                                        //��ܥX��}�l�����A 
		OPEN(&open_x, &open_y);                                             //��J���}����m
		PUT_BOMB(cells, open_x, open_y);                                    //��a�p��JCELL
		HOW_MANY_BOMB(cells);                                               //�p��D�a�p�Ϫ��񦳴X�u�a�p
		CHANGE(cells, open_x, open_y);                                      //���ܥ��}����m����T
		CHECK_BOMB(cells, open_x, open_y);                                  //�ˬd���񪺰ϰ즳�S���a�p�A�ñN�L�a�p���ϰ쥴�}
		over = WIN_LOSE(cells, open_x, open_y);                             //�ˬdWIN OR LOSE
		PRINT_STATUS(cells, open_x, open_y, over);                          //�L�X�ثe�����p
		while (over == 0) {
			OPEN(&open_x, &open_y);
			CHANGE(cells, open_x, open_y);                                  //��J���}����m
			CHECK_BOMB(cells, open_x, open_y);                              //�ˬd���񪺰ϰ즳�S���a�p�A�ñN�L�a�p���ϰ쥴�}
			over = WIN_LOSE(cells, open_x, open_y);                         //�ˬdWIN OR LOSE
			PRINT_STATUS(cells, open_x, open_y, over);                      //�L�X�ثe�����p
		}
		again = AGAIN();                                                    //PLAY AGAIN ?
	} while (again == 'Y' || again == 'y');

	return(0);
}

void ZERO(int cells[][17]) {                                                //��l��CELL 
	int i, j;
	for (i = 0; i < 17; i++)
	for (j = 0; j < 17; j++)
		cells[i][j] = 0;
}

void BEGINNING(void) {                                                     //��ܥX��}�l�����A 
	int i, j;
	printf("         ��a�p\n");
	printf("��J�@�Ӧ�},�Y�S�a�p�h�|��ܼƦr\n");
	printf("�Ʀr�N��P��a�p�ƶq\n");
	printf("���A�̪��o�}��^^\n");
	printf("\n\n");
	printf("    ");
	for (i = 1; i <= 15; i++)
		printf("%2d", i);
	printf("\n");
	for (i = 1; i <= 15; i++) {
		for (j = 0; j <= 15; j++) {
			if (j == 0)
				printf("%4d", i);
			else
				printf("��");
		}
		printf("\n");
	}
}

void OPEN(int *op_x, int *op_y) {                                           //��J���}����m
	int x, y;
	printf("\n��J�z�n�}�Ҫ��y�� >> ");
	scanf("%d%d", op_x, op_y);
}

void PUT_BOMB(int cells[][17], int op_x, int op_y) {                        //��a�p��JCELL
	srand(time(NULL));          //  �üƺؤl 
	int  n = 0,
		rand_num,
		cell_x,
		cell_y;

	do {
		rand_num = rand() % 225;     // ( rand() % (�̤j��-�̤p��+1)) + �̤p��
		cell_x = (rand_num % 15) + 1;
		cell_y = ((rand_num - cell_x) / 15) + 1;
		if (cells[cell_x][cell_y] != -1 && !(cell_x == op_x && cell_y == op_y)) {
			cells[cell_x][cell_y] = -1;
			n++;
		}
	} while (n < 40);
}

void HOW_MANY_BOMB(int cells[][17]) {                                     //�p��D�a�p�Ϫ��񦳴X�u�a�p 
	int i, j, u, v;
	for (i = 1; i <= 15; i++)
	for (j = 1; j <= 15; j++)
	if (cells[i][j] == 0)
	for (u = i - 1; u <= i + 1; u++)
	for (v = j - 1; v <= j + 1; v++)
	if (cells[u][v] == -1)
		cells[i][j]++;
}

void CHANGE(int cells[][17], int op_x, int op_y) {                      //���ܥ��}����m����T 
	if (cells[op_x][op_y] == -1)
		cells[op_x][op_y] = -2;
	if (cells[op_x][op_y] >= 0 && cells[op_x][op_y] <= 8)
		cells[op_x][op_y] += 16;
}

void OPEN_SURROUNDING(int cells[][17], int op_x, int op_y) {           //���}���񪺰ϰ�          ++++++++++++++
	int i, j;
	for (i = op_x - 1; i <= op_x + 1; i++) {
		for (j = op_y - 1; j <= op_y + 1; j++) {
			if (cells[i][j] >= 0 && cells[i][j] <= 8 && i % 16 != 0 && j % 16 != 0) {
				cells[i][j] += 16;
				CHECK_BOMB(cells, i, j);
			}
		}
	}
}

void CHECK_BOMB(int cells[][17], int op_x, int op_y) {                 //�ˬd���񪺰ϰ즳�S���a�p                    +++++++++++++++
	if (cells[op_x][op_y] == 16)        //����S�a�p 
		OPEN_SURROUNDING(cells, op_x, op_y);
}

void PRINT_PLAYING_STATUS(int cells[][17]) {                           //�L�X�|�����������p
	int i, j;
	printf("      ");
	for (i = 1; i <= 15; i++)
		printf("%2d", i);
	printf("\n    �z�ССССССССССССССТ{\n");
	for (i = 1; i <= 15; i++) {
		for (j = 0; j <= 15; j++) {
			if (j == 0)
				printf("%4d�U", i);
			else if (cells[i][j] < 16)
				printf("��");
			else if (cells[i][j] == 16)
				printf(" 0");
			else if (cells[i][j] > 16 && cells[i][j] <= 30)
				printf(" %d", cells[i][j] - 16);
			if (j == 15)
				printf("�U%d", i);
		}
		printf("\n");
	}
	printf("    �|�ССССССССССССССТ}\n");
	printf("      ");
	for (i = 1; i <= 15; i++)
		printf("%2d", i);
	printf("\n");
}


void PRINT_ENDING_STATUS(int cells[][17], int over) {                       //�L�X�C�����������p
	int i, j;
	printf("  �z�ССССССССССССССТ{\n");
	for (i = 1; i <= 15; i++) {
		for (j = 0; j <= 16; j++) {
			if (j == 0)
				printf("  �U");
			else if (j == 16)
				printf("�U");
			else if (cells[i][j] % 16 == 0)
				printf("  ");
			else if (cells[i][j] == -1)
				printf("��");
			else if (cells[i][j] == -2)
				printf("��");
			else
				printf("%2d", cells[i][j] % 16);
		}
		printf("\n");
	}
	printf("  �|�ССССССССССССССТ}\n");
	if (over == 1)
		printf("YOU ARE A WONER�I\n\n");
	else
		printf("YOU ARE A LOSER \n\n");
	printf("�Ʀr�N��P��K��a�p�`�ƶq\n");
	printf("���N��a�p\n");
	printf("���N���z�����a�p�C\n");
	printf("\n");
}

void PRINT_STATUS(int cells[][17], int op_x, int op_y, int over) {               //�L�X�ثe�����p
	system("cls");
	printf("\n");
	int i, j;
	if (over == 0) {
		PRINT_PLAYING_STATUS(cells);
	}
	else
		PRINT_ENDING_STATUS(cells, over);
}

int  WIN_LOSE(int cells[][17], int op_x, int op_y) {                          //�ˬdWIN OR LOSE      ++++++++++++++++++++++++++
	//result == 0 ->�|�������Aresult == 1 ->Ĺ�Aresult == -1 ->��
	int i, j, result = 1;
	if (cells[op_x][op_y] == -2) {
		result = -1;
	}
	else {
		for (i = 1; i <= 15 && result == 1; i++)
		for (j = 1; j <= 15 && result == 1; j++)
		if ((cells[i][j] >= 0 && cells[i][j] <= 8))
			result = 0;
	}
	return(result);
}

char AGAIN(void) {                                                         //PLAY AGAIN ?
	char again;
	printf("\n�٭n�A���@���ܡH");
	do {
		printf("\n�n�A���@�����ܽп�JY�A\n");
		printf("�ο�JN�����{���C >>");
		scanf(" %c", &again);
	} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
	return(again);
}
