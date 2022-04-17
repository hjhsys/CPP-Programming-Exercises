#include "MineSweeper.h"
void main()
{
	int total;
	int size_x;
	int size_y;
	printf(" <Mine Sweeper>\n");
	printf(" 맵의 가로 크기 입력 (최대 : 80): ");
	scanf_s("%d", &size_x);
	if (size_x > 80)
	{
		printf("초과");
			return;
	}
	printf(" 맵의 세로 크기 입력 (최대 : 40): ");
	scanf_s("%d", &size_y);
	if (size_y > 40)
	{
		printf("초과");
		return;
	}
	printf(" 매설할 총 지뢰의 개수 입력 (맵 크기 : %d) : ", size_x * size_y);
	scanf_s("%d", &total);
	if (total > size_x * size_y)
	{
		printf("초과");
		return;
	}
	playMineSweeper(total, size_x, size_y);
}