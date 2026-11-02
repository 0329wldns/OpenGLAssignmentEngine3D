#pragma once
#include "pch.h"
#include "Struct.h"
#include "collider.h"

// 기본적으로 무한 반복하도록 되어있음
struct RotateData
{
	void update();
	glm::mat4 getRotationMatrix() const
	{
		glm::mat4 rotation{ 1.0f };
		rotation = glm::translate(rotation, offset);
		rotation = glm::rotate(rotation, glm::radians(degree), axis);
		rotation = glm::translate(rotation, -offset);
		return rotation;
	}

	void toggleActive() { isActive = !isActive; }

	float degree{};
	float targetDegree{ 360.0f };
	float speed{ 90.0f };			// 방향 포함
	Vector3 offset{};
	Vector3 axis{0.0f, 1.0f, 0.0f};
	int rotateType{};				// 정렬기준, 행렬곱을 먼저 적용해야 할 수록 큰 값 부여
	char id{};						// 어떤 키에 대한 회전인지
	bool isActive{ false };			// 회전이 활성화 되었는지, update 여부 결정
	bool isEnd{ false };			// targetDegree에 도달했는지, isExpire가 true일 때만 의미 있음
	
	// targetDegree에 도달했을 때
	bool isExpire{ false };			// 없앨까?
	bool isReverse{ false };		// 방향을 바꿀까?
	bool isStop{ false };			// 멈출까?
};

struct FaceData
{
	void update();
	void addRotateData(const RotateData&);

	Color color{};
	bool isVisible{ false };

	Vector3 scale{};
	vector<RotateData> rotateData;
};

class Collider;

class Object
{
public:
	Object();
	virtual ~Object();

	void createCollider();
	void creaeteAnimator() {};

	virtual void update() = 0;
	virtual void finalUpdate() final;

	virtual void onMouseEnter() {};
	virtual void onMouseLeave() {};
	virtual void onMouseDownLeft() {};
	virtual void onMouseDownRight() {};
	virtual void onMouseUpLeft() {};
	virtual void onMouseUpRight() {};

	virtual void render() const = 0;
	void componantRender() const;

	virtual void onCollision(Collider*) {};
	virtual void onCollisionEnter(Collider*) {};
	virtual void onCollisionExit(Collider*) {};

	void setPos(Vector2 _pos) { pos.x = _pos.x; pos.y = _pos.y; }
	void setPos(int _posX, int _posY) { pos.x = (float)_posX; pos.y = (float)_posY; }
	void setPos(double _posX, double _posY) { pos.x = (float)_posX; pos.y = (float)_posY; }
	void setScale(Vector2 _scale) { scale.x = _scale.x; scale.y = _scale.y; }
	void setScale(int _scaleX, int _scaleY) { scale.x = (float)_scaleX; scale.y = (float)_scaleY; }
	void setScale(double _scaleX, double _scaleY) { scale.x = (float)_scaleX; scale.y = (float)_scaleY; }

	void setPos(Vector3 _pos) { pos.x = _pos.x; pos.y = _pos.y; pos.z = _pos.z; }
	void setPos(int _posX, int _posY, int _posZ) { pos.x = (float)_posX; pos.y = (float)_posY; pos.z = (float)_posZ; }
	void setPos(double _posX, double _posY, double _posZ) { pos.x = (float)_posX; pos.y = (float)_posY; pos.z = (float)_posZ; }
	void setScale(Vector3 _scale) { scale.x = _scale.x; scale.y = _scale.y; scale.z = _scale.z; }
	void setScale(int _scaleX, int _scaleY, int _scaleZ) { scale.x = (float)_scaleX; scale.y = (float)_scaleY; scale.z = (float)_scaleZ; }
	void setScale(double _scaleX, double _scaleY, double _scaleZ) { scale.x = (float)_scaleX; scale.y = (float)_scaleY; scale.z = (float)_scaleZ; }

	Vector3 getPos() const { return pos; }
	Vector3 getScale() const { return scale; }
	Collider* getCollider() const { return collider; }
	bool isDead() const { return !alive; }

private:
	void setDead() { alive = false; }

private:
	Vector3 pos;
	Vector3 scale;

	Collider* collider;

	bool alive;

	friend class EventManager;
};