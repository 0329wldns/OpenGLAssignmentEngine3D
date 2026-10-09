#pragma once
#include "pch.h"
#include "Singleton.h"

class Core : public Singleton<Core>
{
    friend class Singleton<Core>;

public:
    int init();
    void progress();

    // 메인 루프 실행 조건 (ESC 누르거나 X 버튼 클릭 시 종료)
    bool isRunning() const;
    GLFWwindow* getWindow() const { return window; }

private:
    Core() = default;
    ~Core();

    void update();
    void finalUpdate();
    void render();

private:
    GLFWwindow* window{};
};