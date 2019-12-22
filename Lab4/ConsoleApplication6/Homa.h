#pragma once
#include "OrientationStructs.h"
#include <vector>

class Homa
{
public:
	struct ReceptorsState
	{
		bool smell, wind, blink, hit, cry;
	};

	Homa()
		: m_hit(false)
		, m_isArrowAvaliable(true)
		, m_score(0)
		, m_homaPos({ 0, 0 })
		, m_lookDir(LookDirection::RIGHT)
		, m_movementDir(LookDirection::RIGHT)
		, m_facedWiy(false)
	{
	}

	~Homa() {}

	Action GetDesiredAction(ReceptorsState const& state);
	void AddScore(int const score) { m_score += score; }
	int GetScore() const { return m_score; }

public:
	bool m_hit;
	bool m_isArrowAvaliable;
	int m_score;

	Pos m_homaPos;
	LookDirection m_lookDir;
	LookDirection m_movementDir;
	LookDirection m_nextMovementDir;

private:
	Action RestoreDirection();
	
	bool m_facedWiy;
	std::vector<LookDirection> m_actionSequence;
};

