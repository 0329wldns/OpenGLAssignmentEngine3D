#include "pch.h"
#include "UIButton.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "TimeManager.h"
#include "ShaderManager.h"
#include "MeshManager.h"

UIButton::UIButton()
	: targetScene(SCENE_TYPE::START)
	, isHover(false)
	, degree(30.0f)
{
	setScale(width, height, 0.08f);
	setColor(COLOR_GRAY);
}

void UIButton::update()
{
	Vector3 myScale{ getScale() };

	float dt = TimeManager::getInstance().getDeltaTime();

	if (isHover)
	{
		myScale.x += width * 3.0f * dt;
		myScale.y += height * 3.0f * dt;
		myScale.z += height * 3.0f * dt;
		degree += 90.0f * dt;
		
	}
	else
	{
		myScale.x -= width * 3.0f * dt;
		myScale.y -= height * 3.0f * dt;
		myScale.z -= height * 3.0f * dt;
	}

	if (myScale.x > width * 1.5f) myScale.x = width * 1.5f;
	else if (myScale.x < width) myScale.x = width;
	if (myScale.y > height * 1.5f) myScale.y = height * 1.5f;
	else if (myScale.y < height) myScale.y = height;
	if (myScale.z > height * 1.5f) myScale.z = height * 1.5f;
	else if (myScale.z < height) myScale.z = height;
	if (degree >= 360.0f) degree -= 360.0f;

	setScale(myScale);
}

void UIButton::onMouseEnter()
{
	isHover = true;
}

void UIButton::onMouseLeave()
{
	isHover = false;
	degree = 30.0f;
}

void UIButton::onMouseDownLeft()
{
	changeScene(targetScene);
}

void UIButton::render() const
{
	ShaderManager::getInstance().useProgram("default");

	Vector3 myPos{ getPos() };
	Vector3 myScale{ getScale() };

	glm::mat4 model{ 1.0f };
	model = glm::translate(model, myPos);
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, myScale * 2.0f);

	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", color);
	ShaderManager::getInstance().setFloat("default", "transparency", 1.0f);

	MeshManager::getInstance().drawMesh("cube", false);
}