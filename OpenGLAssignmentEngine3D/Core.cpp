#include "pch.h"
#include "Core.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "ShaderManager.h"
#include "MeshManager.h"

Core::~Core()
{
	if (window)
	{
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}

int Core::init()
{
	// GLFW 초기화
	if (!glfwInit())
	{
		cerr << "GLFW 초기화 실패!\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 윈도우 생성
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Game Engine", nullptr, nullptr);
	if (!window)
	{
		cerr << "윈도우 생성 실패!\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// GLEW 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW 초기화 실패!\n";
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// 각 매니저 초기화
	TimeManager::getInstance().init();
	KeyManager::getInstance().init();
	SceneManager::getInstance().init();
	ShaderManager::getInstance().init();
	MeshManager::getInstance().init();

	// z부호 변경
	glm::mat4 nagativeZ
	{ 
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f,-1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f 
	};
	ShaderManager::getInstance().useProgram("default");
	ShaderManager::getInstance().setMat4("default", "nagativeZ", nagativeZ);

	// 배경색 설정
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLineWidth(3);

	// 깊이 테스트 활성화
	glEnable(GL_DEPTH_TEST);

	// 알파 블렌딩 활성화
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void Core::progress()
{
	// 입력 이벤트 폴링
	glfwPollEvents();

	TimeManager::getInstance().update();
	KeyManager::getInstance().update();
	SceneManager::getInstance().update();
	
	finalUpdate();
	CollisionManager::getInstance().update();
	render();

	EventManager::getInstance().update();
}

bool Core::isRunning() const
{
	return !glfwWindowShouldClose(window);
}

void Core::update()
{
}

void Core::finalUpdate()
{
	SceneManager::getInstance().finalUpdate();
}

void Core::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SceneManager::getInstance().render();

	// 버퍼 교체
	glfwSwapBuffers(window);
}