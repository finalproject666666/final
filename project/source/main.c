#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_blanks(void);                                                        //�L�X�C����l����l


int main()
{
	print_blanks();
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