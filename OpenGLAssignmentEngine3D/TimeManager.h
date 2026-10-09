#pragma once
#include "pch.h"
#include "Singleton.h"

// 시간 동기화 - 컴퓨터 사양과 현재 처리 중인 프로그램 수에 따라 update를 처리하는 속도가 달라짐 
class TimeManager : public Singleton<TimeManager>
{
	friend class Singleton<TimeManager>;

public:
	void init();
	void update();

	float getDeltaTime() const { return deltaTime; }

private:
	TimeManager();
	~TimeManager() = default;

private:
	LARGE_INTEGER curTime;
	LARGE_INTEGER prevTime;
	LARGE_INTEGER frequancy;

	int callCount;			// update호출 카운트

	float deltaTime;		// 프레임 간의 시간
	float accTime;			// 누적 시간

	int FPS;				// 초당 프레임
};