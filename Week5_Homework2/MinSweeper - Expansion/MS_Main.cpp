#include "MineSweeper.h"
void main()
{
	int total;
	int size_x;
	int size_y;
	printf(" <Mine Sweeper>\n");
	printf(" 맵의 크기 입력 (가로) : ");
	scanf_s("%d", &size_x);
	printf(" 맵의 크기 입력 (세로) : ");
	scanf_s("%d", &size_y);
	printf(" 매설할 총 지뢰의 개수 입력 : ");
	scanf_s("%d", &total);
	playMineSweeper(total, size_x, size_y);
}