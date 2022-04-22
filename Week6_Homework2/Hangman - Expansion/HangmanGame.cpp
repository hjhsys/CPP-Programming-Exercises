#include "Hangman.h"
#include "MyDic.h"
void main()
{
	Hangman game;
	MyDic Dic;
	string eng;
	string kor;
	int key;

	Dic.load("MyDic.txt");
	if (Dic.count())
	{
		printf("단어 추가하려면 D, 단어 목록 보려면 L 입력\n");
		key = _getche();
		printf("\n");
		if ((key == 68) || (key == 100))
		{
			Dic.print();
			printf("\n단어 입력 (영어 뜻)\n");
			cin >> eng >> kor;
			Dic.add(eng, kor);
			Dic.store("MyDic.txt");
		}
		else if ((key == 76) || (key == 108))
		{
			Dic.print();
		}
		else
		{
			srand((unsigned int)time(NULL));
			int i = rand() % Dic.count();
			game.play(Dic.getEng(i), Dic.getKor(i));
		}
	}
	else
	{
		Dic.print();
		printf("단어 입력 (영어 뜻)\n");
		cin >> eng >> kor;
		Dic.add(eng, kor);
		Dic.store("MyDic.txt");
	}
}