#pragma once
#include "pch.h"
#include "Struct.h"
#include "Singleton.h"

enum class KEY
{
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,
	NUM0,

	W, A, S, D,
	I, J, K, L,

	P, E, T, C,
	Q,
	R,
	MINUS, EQUAL,
	ENTER,
	LEFT_SHIFT,
	MOUSE_L, MOUSE_R,
	ESC,
	LAST
};

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY
};

struct KeyInfo
{
	KEY_STATE keyState{};
	bool prevPush{};
};

class KeyManager : public Singleton<KeyManager>
{
	friend class Singleton<KeyManager>;

public:
	void init();
	void update();

	KEY_STATE getKeyState(KEY _key) const { return keyInfo[(int)_key].keyState; }
	Vector2 getMousePos() const { return curMousePos; }

private:
	KeyManager() = default;

private:
	vector<KeyInfo> keyInfo;
	Vector2 curMousePos{};
};