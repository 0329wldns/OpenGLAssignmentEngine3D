#include "pch.h"
#include "TimeManager.h"
#include "Core.h"

TimeManager::TimeManager()
	: prevTime()
	, curTime()
	, frequancy()
	, deltaTime()
	, accTime()
	, callCount()
	, FPS()
{
}

void TimeManager::init()
{
	QueryPerformanceCounter(&prevTime);
	QueryPerformanceFrequency(&frequancy);
}

void TimeManager::update()
{
	QueryPerformanceCounter(&curTime);

	deltaTime = (float)(curTime.QuadPart - prevTime.QuadPart) / (float)frequancy.QuadPart;

	prevTime = curTime;

	++callCount;
	accTime += deltaTime;

	if (accTime >= 1.f)
	{
		FPS = callCount;
		callCount = 0;
		accTime = 0.f;

		string titleText{ "FPS: " + to_string(FPS) + " DT: " + to_string(deltaTime)};
		glfwSetWindowTitle(Core::getInstance().getWindow(), titleText.c_str());
	}
}
