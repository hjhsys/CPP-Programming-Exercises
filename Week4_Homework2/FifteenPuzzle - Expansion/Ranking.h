#include <cstdio>

struct PlayInfo
{
	char   name[200];		// ����� �̸�
	int    nMove;			// ���� ������ ������ Ƚ��
	double tElapsed;		// ��� �ҿ� �ð�
};
struct RecInput
{
	int    MoveDir;			// ���� ������ ������ Ƚ��
	double TimePassed;		// ��� �ҿ� �ð�
};
struct ReplayCopy
{
	int    MoveDir;			// ���� ������ ������ Ƚ��
	double TimePassed;		// ��� �ҿ� �ð�
};
extern void loadRanking(const char* filename);
extern void storeRanking(const char* filename);
extern void printRanking();
extern int addRanking(int nMove, double tElap);