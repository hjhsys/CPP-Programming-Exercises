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
		printf("�ܾ� �߰��Ϸ��� D, �ܾ� ��� ������ L �Է�\n");
		key = _getche();
		printf("\n");
		if ((key == 68) || (key == 100))
		{
			Dic.print();
			printf("\n�ܾ� �Է� (���� ��)\n");
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
		printf("�ܾ� �Է� (���� ��)\n");
		cin >> eng >> kor;
		Dic.add(eng, kor);
		Dic.store("MyDic.txt");
	}
}