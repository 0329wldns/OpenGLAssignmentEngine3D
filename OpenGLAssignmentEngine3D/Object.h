#pragma once
#include "pch.h"
#include "Struct.h"
#include "collider.h"

struct FaceData
{
	Color color{};
	bool isVisible{ false };
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