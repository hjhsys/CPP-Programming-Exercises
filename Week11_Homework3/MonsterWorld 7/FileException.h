#pragma once
#include <string>
using namespace std;
struct FileException						// 파일 예외 클라스
{
	string filename;						// 파일 이름
	bool bRead;								// 파일 모드
	FileException(string name, bool b) : filename(name), bRead(b) {}
};