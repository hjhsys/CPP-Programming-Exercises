#pragma once
#include <string>
using namespace std;
struct FileException						// ���� ���� Ŭ��
{
	string filename;						// ���� �̸�
	bool bRead;								// ���� ���
	FileException(string name, bool b) : filename(name), bRead(b) {}
};