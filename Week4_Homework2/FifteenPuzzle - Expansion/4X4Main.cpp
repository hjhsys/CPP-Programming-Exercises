#include "Ranking.h"
#include <conio.h>
extern int playFifteenPuzzle();
extern int playFifteenPuzzle3();
extern int playFifteenPuzzle4();
extern int playFifteenPuzzle5();
void main()
{
	printf("\t3:3X3, 4:4X4(�ƽ�Ű ��Ʈ), 5:5X5, �� ��:4X4(�Ϲ�)\n");
	printf("\n\t�÷����� ��� ����: \n\t");

	int key = _getch();

	if ((key == 51))
	{
		loadRanking("ranking3.txt");
		int rank = playFifteenPuzzle3();
		printRanking();
		storeRanking("ranking3.txt");
	}
	else if ((key == 52))
	{
		loadRanking("ranking4.txt");
		int rank = playFifteenPuzzle4();
		printRanking();
		storeRanking("ranking4.txt");
	}
	else if ((key == 53))
	{
		loadRanking("ranking5.txt");
		int rank = playFifteenPuzzle5();
		printRanking();
		storeRanking("ranking5.txt");
	}
	else
	{
		loadRanking("ranking.txt");
		int rank = playFifteenPuzzle();
		printRanking();
		storeRanking("ranking.txt");
	}
}