#pragma once
#include "pch.h"

#include "Core.h"
#include "Object.h"

class Object;

class Collider {
public:
	Collider();

	void finalUpdate();
	void render();

	void onCollision(Collider*);	// 충돌 중인 경우 호출
	void onCollisionEnter(Collider*);	// 충돌을 시작 할 때 호출
	void onCollisionExit(Collider*);	// 충돌을 벗어날 때 호출

	void setPos(Vector2 _pos) { pos = _pos; }
	void setPos(float _posX, float _posY) { pos.x = _posX; pos.y = _posY; }
	void setScale(Vector2 _scale) { scale = _scale; }
	void setScale(float _scaleX, float _scaleY) { scale.x = _scaleX; scale.y = _scaleY; }
	void setOffset(Vector2 _offset) { offset = _offset; }
	void setOffset(float _offsetX, float _offsetY) { offset.x = _offsetX; offset.y = _offsetY; }

	Object* getObj() const { return owner; }
	Vector2 getPos() const { return pos; }
	Vector2 getScale() const { return scale; }
	Vector2 getOffset() const { return offset; }
	unsigned int getId() const { return id; }

private:
	Object* owner;
	Vector2 pos;
	Vector2 scale;
	Vector2 offset;

	unsigned int id;

	bool isCol;

	friend class Object;
};