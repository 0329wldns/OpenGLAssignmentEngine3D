#include "pch.h"
#include "KeyManager.h"
#include "Core.h"

// GLFW 키 매핑 배열
int arrVK[(int)KEY::LAST]
{
	GLFW_KEY_1,
	GLFW_KEY_2,
	GLFW_KEY_3,
	GLFW_KEY_4,
	GLFW_KEY_5,
	GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D,
	GLFW_KEY_I, GLFW_KEY_J, GLFW_KEY_K, GLFW_KEY_L,
	GLFW_KEY_P, GLFW_KEY_E, GLFW_KEY_T, GLFW_KEY_C,
	GLFW_KEY_Q,
	GLFW_KEY_R,
	GLFW_KEY_EQUAL, GLFW_KEY_MINUS,
	GLFW_KEY_ENTER,
	GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, // 마우스
	GLFW_KEY_ESCAPE
};

void KeyManager::init()
{
	for (int i{}; i < (int)KEY::LAST; ++i)
	{
		keyInfo.push_back(KeyInfo{ KEY_STATE::NONE, false });
	}
}

void KeyManager::update()
{
	GLFWwindow* window{ Core::getInstance().getWindow() };
	if (!window) return;

	double mouseX{};
	double mouseY{};

	glfwGetCursorPos(window, &mouseX, &mouseY);
	mouseY = SCREEN_HEIGHT - mouseY;

	// 화면 좌표를 NDC (-1..1)로 변환
	float ndcX = static_cast<float>((mouseX / SCREEN_WIDTH) * 2.0 - 1.0);
	float ndcY = static_cast<float>((mouseY / SCREEN_HEIGHT) * 2.0 - 1.0);
	// 간단한 클램프 (정상 범위를 벗어나지 않도록)
	if (ndcX < -1.0f) ndcX = -1.0f; else if (ndcX > 1.0f) ndcX = 1.0f;
	if (ndcY < -1.0f) ndcY = -1.0f; else if (ndcY > 1.0f) ndcY = 1.0f;

	curMousePos.x = ndcX;
	curMousePos.y = ndcY;

	for (int i{}; i < (int)KEY::LAST; ++i)
	{
		bool isPressed{};

		// 마우스와 키보드는 GLFW 검사 함수가 서로 다름
		if (arrVK[i] == GLFW_MOUSE_BUTTON_LEFT || arrVK[i] == GLFW_MOUSE_BUTTON_RIGHT)
		{
			// 마우스 버튼 체크는 픽셀 좌표 기준으로 검사
			if (mouseX > 0 && mouseX < SCREEN_WIDTH
				&& mouseY > 0 && mouseY < SCREEN_HEIGHT)
				isPressed = (glfwGetMouseButton(window, arrVK[i]) == GLFW_PRESS);
		}
		else
		{
			isPressed = (glfwGetKey(window, arrVK[i]) == GLFW_PRESS);
		}

		if (isPressed)
		{
			if (keyInfo[i].prevPush) keyInfo[i].keyState = KEY_STATE::HOLD;
			else keyInfo[i].keyState = KEY_STATE::TAP;

			keyInfo[i].prevPush = true;
		}
		else
		{
			if (keyInfo[i].prevPush) keyInfo[i].keyState = KEY_STATE::AWAY;
			else keyInfo[i].keyState = KEY_STATE::NONE;

			keyInfo[i].prevPush = false;
		}
	}
}