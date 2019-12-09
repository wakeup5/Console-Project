﻿// Project.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "RenderBuffer.h"
#include "UnicodeImage.h"

#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 200
//#define SCREEN_RATE 0.625f // (5 / 8)

int main()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 5;
    cfi.dwFontSize.Y = 4;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    if (!SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi)) {
        std::cout << "SetCurrentConsoleFontEx failed with error " << GetLastError() << std::endl;
        return -1;
    }

    SMALL_RECT windowSize = { 0, 0, 230, 230 };
    if (!SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize))
    {
        std::cout << "SetConsoleWindowInfo failed with error " << GetLastError() << std::endl;
        return -1;
    }

    if (!SetConsoleTitle(L"Console Project"))
    {
        std::cout << "SetConsoleTitle failed with error " << GetLastError() << std::endl;
        return -1;
    }

    UnicodeSprite sprite("a.jpg", 100, 100, 4, 4);
    RenderBuffer buffer(SCREEN_WIDTH, SCREEN_HEIGHT);

    int i = -1;
    while (i++ < 100) {
        buffer.Clear('=');
        sprite.DrawTo(&buffer, { 10 + i, 10 + i }, i % 4, (i / 4) % 4);

        buffer.Render();
        Sleep(500);
    }
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
