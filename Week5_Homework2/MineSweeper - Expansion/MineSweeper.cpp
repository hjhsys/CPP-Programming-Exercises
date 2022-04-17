#include "MineSweeper.h"
#define DIM 9

enum LabelTyple { Empty = 0, Bomb = 9 };;
enum MaskType { Hide = 0, Open, Flag };;
static int MineMapMask[40][80];		// Hide, Open, Flag
static int MineMapLabel[40][80];		// 0~8, 9(Bomb)
static int nx = 80, ny = 40;
static int nBomb = DIM;

// 여러 거지 작은 함수들, 매우 중요함
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx&& y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

static void dig(int x, int y)
{										// (x, y)를 파는(여는) 함수
	if (isValid(x, y) && mask(x, y) != Open)
	{
		mask(x, y) = Open;
		if (label(x, y) == 0)
		{
			dig(x - 1, y - 1);
			dig(x - 1, y);
			dig(x - 1, y + 1);
			dig(x, y - 1);
			dig(x, y + 1);
			dig(x + 1, y - 1);
			dig(x + 1, y);
			dig(x + 1, y + 1);
		}
	}
}
static void mark(int x, int y)
{										// (x, y)에 깃발을 꽂는 함수
	if (isValid(x, y) && mask(x, y) == Hide)
		mask(x, y) = Flag;
}
static int getBombCount()
{										// 깃발의 수를 계산하는 함수
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
			if (mask(x, y) == Flag)
				count++;
	return count;
}
static void print()
{										// 지뢰 맵의 화면 출력 함수
	system("cls");
	printf(" 발견:%2d 전체:%2d\n", getBombCount(), nBomb);
	printf("\n   ");
	for (int i = 0; i < nx; i++)
		printf("%2d", (i + 1) / 10);
	printf("\n   ");
	for (int i = 0; i < nx; i++)
		printf("%2d", (i + 1) % 10);
	printf("\n");
	for (int y = 0; y < ny; y++)
	{
		if (y < 9)
			printf("0%d ", 1 + y);
		else
			printf("%2d ", 1 + y);
		for (int x = 0; x < nx; x++)
		{
			if (mask(x, y) == Hide)
				printf("□");			// 파지 않은 곳
			else if (mask(x, y) == Flag)
				printf("⊙");			// 지뢰예상 자리
			else
			{							// 판 자리
				if (isBomb(x, y))
					printf("※");		// 9 : 폭발!!
				else if (isEmpty(x, y))
					printf("  ");		// 0 : 빈칸 표시
				else
					printf("%2d", label(x, y));	// 1~8 : 숫자 표시
			}
		}
		if (y < 9)
			printf("0%d ", 1 + y);
		else
			printf("%2d ", 1 + y);
		printf("\n");
	}
	printf("   ");
	for (int i = 0; i < nx; i++)
		printf("%2d", (i + 1) / 10);
	printf("\n   ");
	for (int i = 0; i < nx; i++)
		printf("%2d", (i + 1) % 10);
}
static int countNbrBombs(int x, int y)
{										// 인접한 지뢰의 수 계산 함수
	int count = 0;
	for (int yy = y - 1; yy <= y + 1; yy++)
		for (int xx = x - 1; xx <= x + 1; xx++)
			if (isValid(xx, yy) && label(xx, yy) == Bomb)
				count++;
	return count;
}
static void init(int total = 9)
{
	srand((unsigned int)time(NULL));
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
		{								// 지뢰 맵, 마스크 초기화
			mask(x, y) = Hide;
			label(x, y) = 0;
		}
	nBomb = total;
	for (int i = 0; i < nBomb; i++)
	{									// 지뢰 매설(total 개)
		int x, y;
		do
		{
			x = rand() % nx;
			y = rand() % ny;
		} while (label(x, y) != Empty);
		label(x, y) = Bomb;
	}
	for (int y = 0; y < ny; y++)				// 인접한 지뢰의 수 계산
		for (int x = 0; x < nx; x++)
			if (label(x, y) == Empty)
				label(x, y) = countNbrBombs(x, y);
}
static bool getPos(int& y, int& x)
{												// 키보드 좌표 입력 함수
	printf("\n지뢰(P), 열(01~%d), 행(01~%d)\n 입력 --> ", nx, ny);
	bool isBomb = false;
	y = 10 * (_getch() - '0');				// '1' --> 1
	if ((y == 10 * ('P' - '0')) || (y == 10 * ('p' - '0')))
	{
		isBomb = true;
		y = 10 * (_getch() - '0');			// '1' --> 1
		y = y + (_getch() - '1');
	}
	else
		y = y + (_getch() - '1');
	x = 10 * (_getch() - '0');							// '1' --> 1
	x = x + (_getch() - '1');
	return isBomb;
}
static int checkDone()
{												// 게임 종료 검사 함수
	int count = 0;
	for (int y = 0; y < ny; y++)
		for (int x = 0; x < nx; x++)
		{
			if (mask(x, y) != Open)
				count++;
			else if (isBomb(x, y))
				return -1;
		}
	return(count == nBomb) ? 1 : 0;
}
void playMineSweeper(int total, int sizex, int sizey)
{												// 지뢰 찾기 주 함수
	nx = sizex;
	ny = sizey;
	int x, y, status;
	init(total);								// 지뢰 맵과 마스크 초기화
	do {
		print();
		bool isBomb = getPos(x, y);				// 위치 입력
		if (isBomb)
			mark(x, y);							// 깃발 위치이면 ==> mark() 호출
		else
			dig(x, y);							// 아니면 ==> dig() 호출
		status = checkDone();					// 게임 종료 상황 검사
	} while (status == 0);						// 진행 중이면 반복
	print();
	if (status < 0)								// 실패/성공 출력
		printf("\n실패: 지뢰 폭발!!!\n\n");
	else
		printf("\n성공: 탐색 성공!!!\n\n");
}