#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_blanks(void);                                                        //印出遊戲初始的格子
void open_cell(int *op_x, int *op_y);                                           //請使用者輸入要打開的位置 6
void put_mine(int cells[][11], int op_x, int op_y);                             //放置地雷 31
void assign_inf_after_open(int cells[][11], int op_x, int op_y);                //改變使用者打開的位置之資訊


int main()
{
	int  cells[11][11],
		open_x, open_y;
	print_blanks();
	open_cell(&open_x, &open_y);                                             //請使用者輸入要打開的位置
	put_mine(cells, open_x, open_y);                                         //放置地雷
	open_cell(&open_x, &open_y);                                             //請使用者輸入要打開的位置
	system("pause");
	return 0;
}
void print_blanks(void) {                                                       //印出遊戲初始的格子 
	int i, j;
	printf("              遊戲說明：\n");
	printf("---------------------------------------\n");

	printf("   祝您遊戲愉快！:)\n");
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
				printf("口");
		}
		printf("\n");
	}
}


void open_cell(int *op_x, int *op_y) {                                          //請使用者輸入要打開的位置
	int x, y;
	printf("\n輸入您要開啟的座標 >> ");
	scanf("%d%d", op_x, op_y);
}

void put_mine(int cells[][11], int op_x, int op_y) {                            //放置地雷
	srand(time(NULL));          //  亂數種子 
	int  n = 0,
		rand_num,
		cell_x,
		cell_y;

	do {
		rand_num = rand() % 81;     // ( rand() % (最大值-最小值+1)) + 最小值
		cell_x = (rand_num % 9) + 1;
		cell_y = ((rand_num - cell_x) / 9) + 1;
		if (cells[cell_x][cell_y] != -1 && !(cell_x == op_x && cell_y == op_y)) {
			cells[cell_x][cell_y] = -1;
			n++;
		}
	} while (n < 10);
}
void assign_inf_after_open(int cells[][11], int op_x, int op_y){               //改變使用者打開的位置之資訊 
	if (cells[op_x][op_y] == -1)
		cells[op_x][op_y] = -2;
	if (cells[op_x][op_y] >= 0 && cells[op_x][op_y] <= 8)
		cells[op_x][op_y] += 10;
}