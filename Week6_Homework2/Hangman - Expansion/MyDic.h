#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#define MAXWORDS 1000
using namespace std;

struct WordPair {													// 하나의 단어 쌍을 위한 클래스
	string eng;														// 영어 단어
	string kor;														// 한글 단어
};
class MyDic {
	WordPair words[MAXWORDS];										// 저장된 단어 배열
	int nWords = 0;													// 현재 등록된 단어의 수
public:
	void add(string eng, string kor)								// 하나의 단어 추가
	{
		if (nWords == MAXWORDS)
			cout << "단어장 꽉 참" << endl;
		else
		{
			for (int i = 0; i < eng.length(); i++)						// 한글 : 10101100_00000000 ~ 11010111_10100011
			{															// 영어 : 00100000 ~ 01111111
				if (eng[i] & 0x80)
				{
					cout << "영어 아님" << endl;
					exit(0);
				}
			}
			for (int i = 0; i < kor.length(); i++)
			{
				if (!(kor[i] & 0x80))
				{
					cout << "한글 아님" << endl;
					exit(0);
				}
			}
			for (int i = 0; i < eng.length(); i++)
			{
				if (!(eng[i] >= 97))									// 대문자 A : 65
					eng[i] += 32;										// 소문자 a : 97
			}
			words[nWords].eng = eng;
			words[nWords].kor = kor;
			nWords++;
		}
	}
	void load(string filename)										// 파일에서 단어 읽기
	{
		ifstream fs(filename);
		if (fs)
		{
			fs >> nWords;
			for (int i = 0; i < nWords; i++)
			{
				fs >> words[i].eng >> words[i].kor;
			}
			fs.close();
		}
		else
		{
			cout << "불러오기 실패" << endl;
			_getch();
		}
	}
	void store(string filename)										// 파일에서 모든 단어 저장
	{
		ofstream fs(filename);
		fs << nWords << endl;
		if (fs)
		{
			for (int i = 0; i < nWords; i++)
			{
				fs << words[i].eng << " " << words[i].kor << endl;
			}
		}
		fs.close();
	}
	void print()													// 모든 단어를 화면에 출력
	{
		system("cls");
		cout << "<단어 목록>\n" << endl;
		for (int i = 0; i < nWords; i++)
			cout << words[i].eng << " : " << words[i].kor << endl;
	}
	string getEng(int id)											// id 번째의 영어단어 반환
	{
		return words[id].eng;
	}
	string getKor(int id)											// id 번째의 한글 설명 반환
	{
		return words[id].kor;
	}
	int count()
	{
		return nWords;
	}
};