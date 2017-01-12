#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_blanks(void);                                                        //印出遊戲初始的格子


int main()
{
	print_blanks();
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