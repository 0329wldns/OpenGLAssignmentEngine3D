#include "pch.h"
#include "Core.h"
#include "KeyManager.h"

int main()
{
	// c++ 표준 입출력 한국어로 설정
	SetConsoleOutputCP(CP_UTF8);

	if (Core::getInstance().init() != 0)
	{
		return -1;
	}

	while (Core::getInstance().isRunning())
	{
		Core::getInstance().progress();
	}

	return 0;
}