#include "MineSweeper.h"
void main()
{
	int total;
	int size_x;
	int size_y;
	printf(" <Mine Sweeper>\n");
	printf(" ���� ���� ũ�� �Է� (�ִ� : 80): ");
	scanf_s("%d", &size_x);
	if (size_x > 80)
	{
		printf("�ʰ�");
			return;
	}
	printf(" ���� ���� ũ�� �Է� (�ִ� : 40): ");
	scanf_s("%d", &size_y);
	if (size_y > 40)
	{
		printf("�ʰ�");
		return;
	}
	printf(" �ż��� �� ������ ���� �Է� (�� ũ�� : %d) : ", size_x * size_y);
	scanf_s("%d", &total);
	if (total > size_x * size_y)
	{
		printf("�ʰ�");
		return;
	}
	playMineSweeper(total, size_x, size_y);
}