#include "Ranking.h"
#include <Windows.h>	// Sleep() 함수를 위해 포함
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define DIM 4			// 4X4 퍼즐

#define RecOrder 1000
#define ShuffleAmt 100
static RecInput Record[RecOrder];
static ReplayCopy Replay[RecOrder];

enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };
static int DirKey[4] = { Left, Right, Up, Down };
static int map[DIM][DIM];	// 퍼즐 맵
static int x, y;			// 빈칸의 위치 (행:y, 열:x)
static int nMove;			// 이동한 횟수
static clock_t tStart;		// 기준 시각



void SaveRecord4(const char* filename)
{
	FILE* fp = NULL;
	fopen_s(&fp, filename, "w");
	if (fp == NULL) return;
	for (int i = 0; i < RecOrder; i++)
	{
		fprintf(fp, " %4d   %5.5f\n", Record[i].MoveDir, Record[i].TimePassed);
	}
	fclose(fp);
}

void addRecord4(int Dir, double Time)
{
	int order = 0;
	for (int i = 0; i < RecOrder; i++)
	{
		if (Record[i].MoveDir == 0)
		{
			Record[i].MoveDir = Dir;
			Record[i].TimePassed = Time;
			break;
		}
	}
}




static void init()
{
	for (int i = 0; i < DIM * DIM - 1; i++)
		map[i / DIM][i % DIM] = i + 1;
	map[DIM - 1][DIM - 1] = 0;
	x = DIM - 1;
	y = DIM - 1;

	srand(time(NULL));		// 난수 발생 시작 설정
	tStart = clock();		// 기준 시각 설정
	nMove = 0;				// 이동 횟수 초기화
}

void ArtDisplay(int location, int number)
{
	if (location == 0)
	{
		if (number == 1)
			printf(" .---");	// 1 상
		else if (number == 2)
			printf("-----");	// 2 상
		else if (number == 3)
			printf("-----");	// 3 상
		else if (number == 4)
			printf("---. ");	// 4 상
		else if (number == 5)
			printf("| P  ");	// 5 상
		else if (number == 6)
			printf("|_   ");	// 6 상
		else if (number == 7)
			printf("__ \\ ");	// 7 상
		else if (number == 8)
			printf("  P |");	// 8 상
		else if (number == 9)
			printf("| Z  ");	// 9 상
		else if (number == 10)
			printf("  | |");	// 10 상
		else if (number == 11)
			printf("     ");	// 11 상
		else if (number == 12)
			printf("  Z |");	// 12 상
		else if (number == 13)
			printf("| |  ");	// 13 상
		else if (number == 14)
			printf("     ");	// 14 상
		else if (number == 15)
			printf("     ");	// 15 상
		else
			printf("     ");	// 16 상
	}
	else if (location == 1)
	{
		if (number == 1)
			printf("| .--");	// 1 중
		else if (number == 2)
			printf("--PUZ");	// 2 중
		else if (number == 3)
			printf("ZLE--");	// 3 중
		else if (number == 4)
			printf("--. |");	// 4 중
		else if (number == 5)
			printf("| U  ");	// 5 중
		else if (number == 6)
			printf("  | |");	// 6 중
		else if (number == 7)
			printf("__) |");	// 7 중
		else if (number == 8)
			printf("  U |");	// 8 중
		else if (number == 9)
			printf("| L  ");	// 9 중
		else if (number == 10)
			printf(" _| |");	// 10 중
		else if (number == 11)
			printf("_    ");	// 11 중
		else if (number == 12)
			printf("  L |");	// 12 중
		else if (number == 13)
			printf("| '--");	// 13 중
		else if (number == 14)
			printf("--PUZ");	// 14 중
		else if (number == 15)
			printf("ZLE--");	// 15 중
		else
			printf("     ");	// 16 중
	}
	else
	{
		if (number == 1)
			printf("| |  ");	// 1 하
		else if (number == 2)
			printf(" ____");	// 2 하
		else if (number == 3)
			printf("__   ");	// 3 하
		else if (number == 4)
			printf("  | |");	// 4 하
		else if (number == 5)
			printf("| Z  ");	// 5 하
		else if (number == 6)
			printf("  |  ");	// 6 하
		else if (number == 7)
			printf("___/ ");	// 7 하
		else if (number == 8)
			printf("  Z |");	// 8 하
		else if (number == 9)
			printf("| E  ");	// 9 하
		else if (number == 10)
			printf("|____");	// 10 하
		else if (number == 11)
			printf("_|   ");	// 11 하
		else if (number == 12)
			printf("  E |");	// 12 하
		else if (number == 13)
			printf(" '---");	// 13 하
		else if (number == 14)
			printf("-----");	// 14 하
		else if (number == 15)
			printf("-----");	// 15 하
		else
			printf("     ");	// 16 하
	}
}


static void display()
{
	system("cls");
	printf("\tFifteen Puzzle\n\t");
	printf("--------------------------\n\t");
	for (int r = 0; r < 3 * DIM; r++)
	{
		for (int c = 0; c < DIM; c++)
		{
			if (map[r / 3][c] > 0)
				ArtDisplay(r % 3, map[r / 3][c]);
			else
				ArtDisplay(r % 3, 16);;
		}
		printf("\n\t");
	}
	printf("--------------------------\n\t");
	clock_t t1 = clock();
	double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
	printf("\n\t이동 횟수:%6d\n\t소요 시간:%6.1f\n\n", nMove, d);
}
static bool move(int dir)
{
	if (dir == Right && x > 0)
	{									// → : 맨 왼쪽 열인지 검사
		map[y][x] = map[y][x - 1];
		map[y][--x] = 0;
	}
	else if (dir == Left && x < DIM - 1)
	{									// ← : 맨 오른쪽 열인지 검사
		map[y][x] = map[y][x + 1];
		map[y][++x] = 0;
	}
	else if (dir == Up && y < DIM - 1)
	{									// ↑ : 맨 아래행이지 검사
		map[y][x] = map[y + 1][x];
		map[++y][x] = 0;
	}
	else if (dir == Down && y > 0)
	{									// ↓ : 맨 윗행인지 검사
		map[y][x] = map[y - 1][x];
		map[--y][x] = 0;
	}
	else return false;


	clock_t t1 = clock();	// 현재 시각
	double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
	addRecord4(dir, d);
	SaveRecord4("Record4.txt");

	nMove++;
	return true;
}
static void shuffle(int nShuffle)
{
	for (int i = 0; i < nShuffle; i++)
	{
		int key = DirKey[rand() % 4];
		if (move(key) == false) { i--; continue; }
		display();
		Sleep(50);
	}
}
static bool isDone()
{
	for (int r = 0; r < DIM; r++)
	{
		for (int c = 0; c < DIM; c++)
		{
			if (map[r][c] != r * DIM + c + 1)
				return (r == DIM - 1) && (c == DIM - 1);
		}
	}
	return true;
}
static int getDirKey() { return _getche() == 224 ? _getche() : 0; }

void LoadRecord4(const char* filename)
{
	FILE* fp = NULL;
	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		printf("\n 저장된 세이브가 없습니다\n");
		_getche();
		return;
	}
	else
	{
		for (int i = 0; i < RecOrder; i++)
			fscanf_s(fp, "%d %lf", &Record[i].MoveDir, &Record[i].TimePassed);
		fclose(fp);
	}
	if (Record[1].MoveDir == 0)
	{
		printf("\n 저장된 게임이 없습니다\n\n 게임을 새로 시작합니다\n");
		_getche();
		shuffle(ShuffleAmt);			// 퍼즐 조각을 100번 이동해 섞음
		printf("\n 게임이 시작됩니다...\n");
		_getche();

		nMove = 0;				// 이동 횟수 초기화
		tStart = clock();		// 기준 시각을 재설정

		return;

	}
	for (int i = 0; Record[i].MoveDir != 0; i++)
	{
		Replay[i].MoveDir = Record[i].MoveDir;
		Replay[i].TimePassed = Record[i].TimePassed;
		Record[i].MoveDir = 0;
	}
	printf("\n 시작 상태를 불러옵니다\n");
	_getch();
	int count = 0;
	for (int i = 0; i < ShuffleAmt; i++)
	{
		int key = Replay[i].MoveDir;
		if (move(key) == false) { i--; continue; }
		display();
		Sleep(50);
		count++;
	}
	nMove = 0;
	printf("\n 플레이 기록을 불러옵니다\n");
	_getche();
	for (int i = ShuffleAmt; Replay[i].MoveDir != 0; i++)
	{
		int key = Replay[i].MoveDir;
		if (move(key) == false) { i--; continue; }
		display();
		Sleep(50);
		count++;
	}
	printf("\n 게임이 시작됩니다\n");
	tStart = clock() - (Replay[count - 1].TimePassed * CLOCKS_PER_SEC);
	_getche();

}

void EndReplay4()
{
	for (int i = 0; Record[i].MoveDir != 0; i++)
	{
		Replay[i].MoveDir = Record[i].MoveDir;
		Replay[i].TimePassed = Record[i].TimePassed;
	}
	init();
	display();

	for (int i = 0; i < ShuffleAmt; i++)
	{
		int key = Replay[i].MoveDir;
		if (move(key) == false) { i--; continue; }
		display();
		Sleep(50);
	}
	nMove = 0;
	printf("\n 리플레이를 시작합니다\n");
	_getche();
	for (int i = ShuffleAmt; Replay[i].MoveDir != 0; i++)
	{
		int key = Replay[i].MoveDir;
		if (move(key) == false) { i--; continue; }
		display();
		Sleep(250);
	}
}


int playFifteenPuzzle4()
{
	int input;
	init();
	display();
	printRanking();
	printf("\n 퍼즐을 섞어주세요(L : 저장된 게임 불러오기)\n");

	int key = _getch();

	if ((key == 76) || (key == 108))
		LoadRecord4("Record4.txt");
	else
	{
		shuffle(ShuffleAmt);			// 퍼즐 조각을 100번 이동해 섞음
		printf("\n 게임이 시작됩니다\n");
		_getche();

		nMove = 0;				// 이동 횟수 초기화
		tStart = clock();		// 기준 시각을 재설정
	}
	while (!isDone())
	{						// 게임 종료 검사
		move(getDirKey());	// 키를 받아 퍼즐조각 이동
		display();			// 현재 상태를 화면에 출력
	}
	clock_t t1 = clock();	// 현재 시각
	double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;

	printf("\n 리플레이를 준비합니다\n");
	_getche();
	EndReplay4();
	int r;
	r = remove("Record4.txt");
	return addRanking(nMove, d);	// 랭킹 갱신
}