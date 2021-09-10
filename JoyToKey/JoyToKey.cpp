
#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>

#include <mmsystem.h>
#include <bitset>
#include <bit>

#pragma comment(lib,"winmm.lib")

#include "JoyHook.h"

#pragma comment (lib,"JoyHook.lib")
using namespace std;

string numTobin(unsigned int num)
{
	string result = "";

	do {
		result += (num % 2) ? '1' : '0';

		num /= 2;
	} while (num > 0);

	reverse(result.begin(), result.end());

	if (result.length() < 32) {
		string zeroSet = "";
		for (int i = 0; i < 32 - result.length(); i++)
			zeroSet += '0';

		zeroSet += result;
		return zeroSet;
	}
	return result;
}

void clrscr()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}


void WINAPI JoyProc(UINT Id, JoyAram JAram) 
{
	if (Id == JOY_EVENT_BUTTONUP) {
		switch (JAram.r)
		{
		case BUTTON_X:
			MessageBox(0,L"X",L"",0);
			break;
		case BUTTON_LB:
			MessageBox(0, L"LB", L"", 0);
			break;
		}
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
//int main()
{
/*	//获取默认标准显示缓冲区句柄
	HANDLE hOutput;
	COORD coord = { 0,0 };
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	//创建新的缓冲区
	HANDLE hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);

	//设置新的缓冲区为活动显示缓冲
	SetConsoleActiveScreenBuffer(hOutBuf);

	//隐藏两个缓冲区的光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);

	//双缓冲处理显示
	DWORD bytes = 0;
	char data[800];
	*/
	SetProc(JoyProc);
	Start();

	while (1)Sleep(1);
	return 0;
}