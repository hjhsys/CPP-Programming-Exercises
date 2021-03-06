#include <cstdio>

struct PlayInfo
{
	char   name[200];		// 산수의 이름
	int    nMove;			// 퍼즐 조각을 움직인 횟수
	double tElapsed;		// 경기 소요 시간
};
struct RecInput
{
	int    MoveDir;			// 퍼즐 조각을 움직인 횟수
	double TimePassed;		// 경기 소요 시간
};
struct ReplayCopy
{
	int    MoveDir;			// 퍼즐 조각을 움직인 횟수
	double TimePassed;		// 경기 소요 시간
};
extern void loadRanking(const char* filename);
extern void storeRanking(const char* filename);
extern void printRanking();
extern int addRanking(int nMove, double tElap);