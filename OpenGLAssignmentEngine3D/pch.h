#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <windows.h>
#include <cmath>
#include <array>

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include "Struct.h"

using namespace std;

static random_device rd{};
static mt19937 gen(rd());
static uniform_int_distribution<int> intDist(1, 10000);
static uniform_real_distribution<float> realDist(0.0f, 1.0f);

static const int SCREEN_WIDTH = 1600;
static const int SCREEN_HEIGHT = 1200;

static const Color COLOR_BLACK{ 0.0f, 0.0f, 0.0f };
static const Color COLOR_RED{ 1.0f, 0.0f, 0.0f };
static const Color COLOR_YELLOW{ 1.0f, 1.0f, 0.0f };
static const Color COLOR_GREEN{ 0.0f, 1.0f, 0.0f };
static const Color COLOR_BLUE{ 0.0f, 0.0f, 1.0f };
static const Color COLOR_GRAY{ 0.5f, 0.5f, 0.5f };
static const Color COLOR_WHITE{ 1.0f, 1.0f, 1.0f };

enum class SCENE_TYPE
{
	START,
	ASSIGNMENT13,
	ASSIGNMENT14,
	ASSIGNMENT15,
	ASSIGNMENT16,
	ASSIGNMENT17,
	ASSIGNMENT18,

	END
};

enum class OBJECT_GROUP
{
	DEFAULT,
	UIBUTTON,
	POLYHENDRON,

	END
};
