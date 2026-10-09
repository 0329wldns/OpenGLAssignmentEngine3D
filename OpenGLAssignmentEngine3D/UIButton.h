#pragma once
#include "Object.h"

class UIButton : public Object
{
public:
	UIButton();
	~UIButton() = default;

	void update() override;

	void onMouseEnter() override;
	void onMouseLeave() override;
	void onMouseDownLeft() override;

	void render() const override;

	void setTargetScene(SCENE_TYPE nextScene) { targetScene = nextScene; }
	void setColor(float r, float g, float b) { color.r = r; color.g = g; color.b = b; }
	void setColor(Color _color) { color = _color; }

private:
	SCENE_TYPE targetScene; // 클릭 시 넘어갈 씬
	Color color; // 버튼 색상
	bool isHover; // 마우스가 버튼 위에 올라와 있는지 상태
	float degree;

	inline static const float width{ 0.12f };
	inline static const float height{ 0.08f };
};
