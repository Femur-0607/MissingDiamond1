#include <iostream>
#include <windows.h>
#include "GameManager.h"

using namespace std;

int main() {
	// 콘솔 창의 출력 인코딩을 UTF-8(65001)로 설정하여 한글 깨짐을 방지합니다.
	SetConsoleOutputCP(CP_UTF8);
	
	cout << "===========================================" << endl;
	cout << "  저택의 사라진 다이아몬드 살인사건" << endl;
	cout << "===========================================" << endl;
	cout << "\n게임을 시작하려면 'enter'를 누르세요..." << endl;
	
	system("pause > nul");
	
	system("cls");
	
	GameManager gm;
	gm.Run();

	return 0;
}