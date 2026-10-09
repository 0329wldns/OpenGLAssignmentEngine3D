#include "pch.h"
#include "EventFunc.h"
#include "EventManager.h"

void createObject(Object* newObject, OBJECT_GROUP group)
{
    Event event{};
    event.event = EVENT_TYPE::CREATE_OBJECT;
    event.lParam = static_cast<void*>(newObject); // 포인터는 void* 로 넘김
    event.wParam = static_cast<int>(group);       // 그룹(Enum)은 int로 넘김
    EventManager::getInstance().addEvent(event);
}

void deleteObject(Object* delObject)
{
    Event event{};
    event.event = EVENT_TYPE::DELETE_OBJECT;
    event.lParam = static_cast<void*>(delObject);
    EventManager::getInstance().addEvent(event);
}

void changeScene(SCENE_TYPE nextScene)
{
    Event event{};
    event.event = EVENT_TYPE::SCENE_CHANGE;
    event.lParam = static_cast<void*>(nullptr); // 씬 전환 로직에 맞게 조정 필요
    event.wParam = static_cast<int>(nextScene);
    EventManager::getInstance().addEvent(event);
}