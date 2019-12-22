#pragma once

#include "Homa.h"
#include <vector>

class Environment
{
public:
	struct Arrow
	{
		Pos m_pos;
		LookDirection m_dir;
		bool m_isLaunched;
	};

	Environment();
	~Environment();

	void InitField(size_t const goldCount, size_t const pannaCount);
	void PrintField() const;

	void StartLoop(bool const usePrint);
	int GetScore() const { return m_homa.GetScore(); }

	Homa::ReceptorsState GetReceptorsState(Homa const& homa) const;

private:
	Pos GetRandomFreePosExclude(std::vector<Pos> const& poses) const;

	void SetPannas();
	bool UpdateArrow();

	//returns is is Homa alive after action
	bool TryMakeAction(Homa& homa);

	bool TryMove(Homa& homa) const;
	bool TryPickUp(Homa& homa);
	bool TryShoot(Homa& homa);
	bool Rotate(Homa& homa, Action const nextAction);

	//Receptors methods
	bool HasSmell(Pos const pos) const;
	bool HasGold(Pos const pos) const;
	bool ArrowKilled() const;
	bool FeelWind(Pos const pos) const;

	Arrow m_arrow;
	Homa m_homa;
	Pos m_wiyPos;
	size_t m_pannaCount;
	std::vector<Pos> m_pannaPoses;
	std::vector<Pos> m_goldPoses;
};

