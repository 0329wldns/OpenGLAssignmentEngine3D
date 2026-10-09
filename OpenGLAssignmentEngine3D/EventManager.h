#pragma once
#include "pch.h"
#include "Singleton.h"

class Object;

enum class EVENT_TYPE
{
    CREATE_OBJECT,
    DELETE_OBJECT,
    SCENE_CHANGE
};

struct Event
{
    EVENT_TYPE event{};
    void* lParam{};
    int wParam{};   // 그룹 타입 등은 int로 처리
};

class EventManager : public Singleton<EventManager>
{
    friend class Singleton<EventManager>;

public:
    void addEvent(const Event& _event) { vecEvent.push_back(_event); }
    void update();
    void excute(const Event& _event);

private:
    EventManager() = default;
    ~EventManager(); // 지연 삭제된 객체들의 최종 메모리 해제 보장

private:
    vector<Event> vecEvent;
    vector<Object*> vecDead;
};