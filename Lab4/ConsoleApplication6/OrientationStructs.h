#pragma once

enum class Action
{
	MoveUP,
	RotateLeft,
	RotateRight,
	PickUp,
	Shoot
};

struct Pos
{
	int x, y;

	bool operator==(Pos const& pos) const;
};

enum class LookDirection
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
};
