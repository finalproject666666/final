#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void ZERO(int cells[][17]);                                                 //初始化CELL  6
void BEGINNING(void);                                                       //顯示出剛開始的狀態  6
void OPEN(int *op_x, int *op_y);                                            //輸入打開的位置 6
void PUT_BOMB(int cells[][17], int op_x, int op_y);                         //把地雷放入CELL 31
void HOW_MANY_BOMB(int cells[][17]);                                        //計算附近的地雷數 31
void CHANGE(int cells[][17], int op_x, int op_y);                           //改變打開的位置的資訊  31
void OPEN_SURROUNDING(int cells[][17], int p_x, int op_y);                  //打開附近的區域  33 
void CHECK_BOMB(int cells[][17], int op_x, int op_y);                       //檢查附近的區域有沒有地雷 33
int  WIN_LOSE(int cells[][17], int op_x, int op_y);                         //檢查WIN OR LOSE 33
void PRINT_STATUS(int cells[][17], int op_x, int op_y, int over);           //印出目前的狀況   37
void PRINT_PLAYING_STATUS(int cells[][17]);                                 //印出尚未結束的狀況  37
void PRINT_ENDING_STATUS(int cells[][17], int over);                        //印出遊戲結束的狀況 23 
char AGAIN(void);                                                           //PLAY AGAIN ?  23

int main(void) {
	int  cells[17][17],
		open_x, open_y,
		over;
	char again;

	do {
		system("cls");
		ZERO(cells);                                                        //初始化CELL
		BEGINNING();                                                        //顯示出剛開始的狀態 
		OPEN(&open_x, &open_y);                                             //輸入打開的位置
		PUT_BOMB(cells, open_x, open_y);                                    //把地雷放入CELL
		HOW_MANY_BOMB(cells);                                               //計算非地雷區附近有幾彈地雷
		CHANGE(cells, open_x, open_y);                                      //改變打開的位置的資訊
		CHECK_BOMB(cells, open_x, open_y);                                  //檢查附近的區域有沒有地雷，並將無地雷的區域打開
		over = WIN_LOSE(cells, open_x, open_y);                             //檢查WIN OR LOSE
		PRINT_STATUS(cells, open_x, open_y, over);                          //印出目前的狀況
		while (over == 0) {
			OPEN(&open_x, &open_y);
			CHANGE(cells, open_x, open_y);                                  //輸入打開的位置
			CHECK_BOMB(cells, open_x, open_y);                              //檢查附近的區域有沒有地雷，並將無地雷的區域打開
			over = WIN_LOSE(cells, open_x, open_y);                         //檢查WIN OR LOSE
			PRINT_STATUS(cells, open_x, open_y, over);                      //印出目前的狀況
		}
		again = AGAIN();                                                    //PLAY AGAIN ?
	} while (again == 'Y' || again == 'y');

	return(0);
}

void ZERO(int cells[][17]) {                                                //初始化CELL 
	int i, j;
	for (i = 0; i < 17; i++)
	for (j = 0; j < 17; j++)
		cells[i][j] = 0;
}

void BEGINNING(void) {                                                     //顯示出剛開始的狀態 
	int i, j;
	printf("         踩地雷\n");
	printf("輸入一個位址,若沒地雷則會顯示數字\n");
	printf("數字代表周圍地雷數量\n");
	printf("祝你們玩得開心^^\n");
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
				printf("●");
		}
		printf("\n");
	}
}

void OPEN(int *op_x, int *op_y) {                                           //輸入打開的位置
	int x, y;
	printf("\n輸入您要開啟的座標 >> ");
	scanf("%d%d", op_x, op_y);
}

void PUT_BOMB(int cells[][17], int op_x, int op_y) {                        //把地雷放入CELL
	srand(time(NULL));          //  亂數種子 
	int  n = 0,
		rand_num,
		cell_x,
		cell_y;

	do {
		rand_num = rand() % 225;     // ( rand() % (最大值-最小值+1)) + 最小值
		cell_x = (rand_num % 15) + 1;
		cell_y = ((rand_num - cell_x) / 15) + 1;
		if (cells[cell_x][cell_y] != -1 && !(cell_x == op_x && cell_y == op_y)) {
			cells[cell_x][cell_y] = -1;
			n++;
		}
	} while (n < 40);
}

void HOW_MANY_BOMB(int cells[][17]) {                                     //計算非地雷區附近有幾彈地雷 
	int i, j, u, v;
	for (i = 1; i <= 15; i++)
	for (j = 1; j <= 15; j++)
	if (cells[i][j] == 0)
	for (u = i - 1; u <= i + 1; u++)
	for (v = j - 1; v <= j + 1; v++)
	if (cells[u][v] == -1)
		cells[i][j]++;
}

void CHANGE(int cells[][17], int op_x, int op_y) {                      //改變打開的位置的資訊 
	if (cells[op_x][op_y] == -1)
		cells[op_x][op_y] = -2;
	if (cells[op_x][op_y] >= 0 && cells[op_x][op_y] <= 8)
		cells[op_x][op_y] += 16;
}

void OPEN_SURROUNDING(int cells[][17], int op_x, int op_y) {           //打開附近的區域          ++++++++++++++
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

void CHECK_BOMB(int cells[][17], int op_x, int op_y) {                 //檢查附近的區域有沒有地雷                    +++++++++++++++
	if (cells[op_x][op_y] == 16)        //附近沒地雷 
		OPEN_SURROUNDING(cells, op_x, op_y);
}

void PRINT_PLAYING_STATUS(int cells[][17]) {                           //印出尚未結束的狀況
	int i, j;
	printf("      ");
	for (i = 1; i <= 15; i++)
		printf("%2d", i);
	printf("\n    ┌－－－－－－－－－－－－－－－┐\n");
	for (i = 1; i <= 15; i++) {
		for (j = 0; j <= 15; j++) {
			if (j == 0)
				printf("%4d｜", i);
			else if (cells[i][j] < 16)
				printf("●");
			else if (cells[i][j] == 16)
				printf(" 0");
			else if (cells[i][j] > 16 && cells[i][j] <= 30)
				printf(" %d", cells[i][j] - 16);
			if (j == 15)
				printf("｜%d", i);
		}
		printf("\n");
	}
	printf("    └－－－－－－－－－－－－－－－┘\n");
	printf("      ");
	for (i = 1; i <= 15; i++)
		printf("%2d", i);
	printf("\n");
}


void PRINT_ENDING_STATUS(int cells[][17], int over) {                       //印出遊戲結束的狀況
	int i, j;
	printf("  ┌－－－－－－－－－－－－－－－┐\n");
	for (i = 1; i <= 15; i++) {
		for (j = 0; j <= 16; j++) {
			if (j == 0)
				printf("  ｜");
			else if (j == 16)
				printf("｜");
			else if (cells[i][j] % 16 == 0)
				printf("  ");
			else if (cells[i][j] == -1)
				printf("○");
			else if (cells[i][j] == -2)
				printf("●");
			else
				printf("%2d", cells[i][j] % 16);
		}
		printf("\n");
	}
	printf("  └－－－－－－－－－－－－－－－┘\n");
	if (over == 1)
		printf("YOU ARE A WONER！\n\n");
	else
		printf("YOU ARE A LOSER \n\n");
	printf("數字代表周圍八格地雷總數量\n");
	printf("○代表地雷\n");
	printf("●代表爆炸的地雷。\n");
	printf("\n");
}

void PRINT_STATUS(int cells[][17], int op_x, int op_y, int over) {               //印出目前的狀況
	system("cls");
	printf("\n");
	int i, j;
	if (over == 0) {
		PRINT_PLAYING_STATUS(cells);
	}
	else
		PRINT_ENDING_STATUS(cells, over);
}

int  WIN_LOSE(int cells[][17], int op_x, int op_y) {                          //檢查WIN OR LOSE      ++++++++++++++++++++++++++
	//result == 0 ->尚未結束，result == 1 ->贏，result == -1 ->輸
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
	printf("\n還要再玩一次嗎？");
	do {
		printf("\n要再玩一次的話請輸入Y，\n");
		printf("或輸入N關閉程式。 >>");
		scanf(" %c", &again);
	} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
	return(again);
}
