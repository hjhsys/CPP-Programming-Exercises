#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#define MAXWORDS 1000
using namespace std;

struct WordPair {													// �ϳ��� �ܾ� ���� ���� Ŭ����
	string eng;														// ���� �ܾ�
	string kor;														// �ѱ� �ܾ�
};
class MyDic {
	WordPair words[MAXWORDS];										// ����� �ܾ� �迭
	int nWords = 0;													// ���� ��ϵ� �ܾ��� ��
public:
	void add(string eng, string kor)								// �ϳ��� �ܾ� �߰�
	{
		if (nWords == MAXWORDS)
			cout << "�ܾ��� �� ��" << endl;
		else
		{
			for (int i = 0; i < eng.length(); i++)						// �ѱ� : 10101100_00000000 ~ 11010111_10100011
			{															// ���� : 00100000 ~ 01111111
				if (eng[i] & 0x80)
				{
					cout << "���� �ƴ�" << endl;
					exit(0);
				}
			}
			for (int i = 0; i < kor.length(); i++)
			{
				if (!(kor[i] & 0x80))
				{
					cout << "�ѱ� �ƴ�" << endl;
					exit(0);
				}
			}
			for (int i = 0; i < eng.length(); i++)
			{
				if (!(eng[i] >= 97))									// �빮�� A : 65
					eng[i] += 32;										// �ҹ��� a : 97
			}
			words[nWords].eng = eng;
			words[nWords].kor = kor;
			nWords++;
		}
	}
	void load(string filename)										// ���Ͽ��� �ܾ� �б�
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
			cout << "�ҷ����� ����" << endl;
			_getch();
		}
	}
	void store(string filename)										// ���Ͽ��� ��� �ܾ� ����
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
	void print()													// ��� �ܾ ȭ�鿡 ���
	{
		system("cls");
		cout << "<�ܾ� ���>\n" << endl;
		for (int i = 0; i < nWords; i++)
			cout << words[i].eng << " : " << words[i].kor << endl;
	}
	string getEng(int id)											// id ��°�� ����ܾ� ��ȯ
	{
		return words[id].eng;
	}
	string getKor(int id)											// id ��°�� �ѱ� ���� ��ȯ
	{
		return words[id].kor;
	}
	int count()
	{
		return nWords;
	}
};