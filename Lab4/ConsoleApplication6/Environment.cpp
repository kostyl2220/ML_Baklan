#include "pch.h"
#include <random>
#include <stdlib.h>
#include "Environment.h"

namespace
{
	int const GOLD_SCORE = 1000;
	int const PENALTY_SCORE = -1000;
	int const ACTION_SCORE = -1;
	int const WIY_ID = 1000;
	int const PANNA_ID = 100;
	int const GOLD_ID = 10;
	int const HOMA_ID = 1;
	int const ARROW_LAUNCH_SCORE = -9;
	double const SPAWN_CHANCE = 0.2;
	size_t const FIELD_SIZE = 4;

	Pos GetMovement(LookDirection const lookDir)
	{
		switch (lookDir)
		{
		case LookDirection::UP:
			return { 0, -1 };
		case LookDirection::DOWN:
			return { 0, 1 };
		case LookDirection::LEFT:
			return { -1, 0 };
		case LookDirection::RIGHT:
			return { 1, 0 };
		}
		return { 0, 0 };
	}

	LookDirection GetRotationClockwise(LookDirection const lookDir)
	{
		switch (lookDir)
		{
		case LookDirection::UP:
			return LookDirection::RIGHT;
		case LookDirection::DOWN:
			return LookDirection::LEFT;
		case LookDirection::LEFT:
			return LookDirection::UP;
		case LookDirection::RIGHT:
			return LookDirection::DOWN;
		}
		return LookDirection::UP;
	}

	bool IsPosFree(std::vector<Pos> const& poses, Pos const posToCheck)
	{
		for (auto pos : poses)
		{
			if (pos == posToCheck)
			{
				return false;
			}
		}
		return true;
	}

	bool InBounds(Pos const& homaPos)
	{
		return homaPos.x >= 0 && homaPos.x < FIELD_SIZE
			&& homaPos.y >= 0 && homaPos.y < FIELD_SIZE;
	}
}

bool Pos::operator==(Pos const& pos) const
{
	return x == pos.x && y == pos.y;
}

Environment::Environment()
{
}


Environment::~Environment()
{
}

void Environment::InitField(size_t const goldCount, size_t const pannaCount)
{
	m_pannaCount = pannaCount;
	m_wiyPos = GetRandomFreePosExclude(m_goldPoses);
	for (size_t g = 0; g < goldCount; ++g)
	{
		m_goldPoses.push_back(GetRandomFreePosExclude(m_goldPoses));
	}
}

void Environment::PrintField() const
{
	system("cls");
	int field[FIELD_SIZE][FIELD_SIZE];
	for (size_t i = 0; i < FIELD_SIZE; ++i)
	{
		for (size_t j = 0; j < FIELD_SIZE; ++j)
		{
			field[i][j] = 0;
		}
	}

	if (m_wiyPos.y != -1000)
	{
		field[m_wiyPos.y][m_wiyPos.x] = WIY_ID;
	}	
	field[m_homa.m_homaPos.y][m_homa.m_homaPos.x] += HOMA_ID;

	for (auto gold : m_goldPoses)
	{
		field[gold.y][gold.x] += GOLD_ID;
	}

	for (auto panna : m_pannaPoses)
	{
		field[panna.y][panna.x] += PANNA_ID;
	}

	for (size_t i = 0; i < FIELD_SIZE; ++i)
	{
		for (size_t j = 0; j < FIELD_SIZE; ++j)
		{
			printf("%5d", field[i][j]);
		}
		printf("\n");
	}
	system("pause");
}

void Environment::StartLoop(bool const usePrint)
{
	while (!m_goldPoses.empty())
	{
		SetPannas();
		UpdateArrow();
		if (usePrint)
		{
			PrintField();
		}
		if (!TryMakeAction(m_homa))
		{
			//game over
			m_homa.AddScore(PENALTY_SCORE);
			printf("Game over! Homa died! Score: %d\n", m_homa.GetScore());
			return;
		}
	}
	printf("Your score: %d\n", m_homa.GetScore());

}

void Environment::SetPannas()
{
	m_pannaPoses.clear();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	for (size_t i = 0; i < m_pannaCount; ++i)
	{
		if (dis(gen) < SPAWN_CHANCE)
		{
			m_pannaPoses.push_back(GetRandomFreePosExclude(m_pannaPoses));
		}
	}
}

bool Environment::UpdateArrow()
{
	while (m_arrow.m_isLaunched && InBounds(m_arrow.m_pos))
	{
		if (m_arrow.m_pos == m_wiyPos)
		{
			m_arrow.m_isLaunched = false;
			m_wiyPos = { -1000, -1000 };
			return true;
		}
		auto const pos = GetMovement(m_arrow.m_dir);
		m_arrow.m_pos.x += pos.x;
		m_arrow.m_pos.y += pos.y;
	}
	m_arrow.m_isLaunched = false;
	return false;
}

Pos Environment::GetRandomFreePosExclude(std::vector<Pos> const& poses) const
{
	Pos pos;
	while (true)
	{
		pos = { rand() % FIELD_SIZE, rand() % FIELD_SIZE };
		
		if (IsPosFree(poses, pos) && !(m_wiyPos == pos) && !(m_homa.m_homaPos == pos))
		{
			return pos;
		}
	}  
	return { 0, 0 };
}

bool Environment::HasSmell(Pos const pos) const
{
	return std::abs((int)pos.x - (int)m_wiyPos.x) + abs((int)pos.y - (int)m_wiyPos.y) <= 1;
}

bool Environment::HasGold(Pos const pos) const
{
	return !IsPosFree(m_goldPoses, pos);
}

bool Environment::ArrowKilled() const
{
	return m_wiyPos == Pos{ -1000, -1000 };
}

bool Environment::FeelWind(Pos const pos) const
{
	for (auto panna : m_pannaPoses)
	{
		if (std::abs((int)pos.x - (int)panna.x) + abs((int)pos.y - (int)panna.y) <= 1)
		{
			return true;
		}
	}
	return false;
}

bool Environment::TryMakeAction(Homa& homa)
{
	if (!IsPosFree(m_pannaPoses, homa.m_homaPos)
		|| m_wiyPos == homa.m_homaPos)
	{
		return false;
	}

	homa.AddScore(ACTION_SCORE);

	auto receptors = GetReceptorsState(m_homa);
	auto nextAction = m_homa.GetDesiredAction(receptors);
	
	switch (nextAction)
	{
		case Action::MoveUP:
		{
			return TryMove(m_homa);
		}
		case Action::PickUp:
		{
			return TryPickUp(m_homa);
		}
		case Action::Shoot:
		{
			return TryShoot(m_homa);
		}
		default:
			return Rotate(m_homa, nextAction);
	}

	return true;
}

bool Environment::TryMove(Homa& homa) const
{
	auto homaPos = homa.m_homaPos;
	auto change = GetMovement(homa.m_lookDir);
	homaPos.x += change.x;
	homaPos.y += change.y;

	if (!InBounds(homaPos))
	{
		homa.m_hit = true;
		return true;
	}

	homa.m_homaPos = homaPos;

	if (!IsPosFree(m_pannaPoses, homaPos))
	{
		return false;
	}

	if (homaPos == m_wiyPos)
	{
		return false;
	}
	return true;
}

bool Environment::TryPickUp(Homa& homa)
{
	if (!IsPosFree(m_goldPoses, homa.m_homaPos))
	{
		auto const goldPos = std::find(m_goldPoses.begin(), m_goldPoses.end(), homa.m_homaPos);
		m_goldPoses.erase(goldPos);
		m_homa.AddScore(GOLD_SCORE);
	}
	return true;
}

bool Environment::TryShoot(Homa& homa)
{
	if (!homa.m_isArrowAvaliable)
	{
		return true;
	}

	homa.AddScore(ARROW_LAUNCH_SCORE);
	m_arrow.m_isLaunched = true;
	m_arrow.m_dir = homa.m_lookDir;
	m_arrow.m_pos = homa.m_homaPos;
	homa.m_isArrowAvaliable = false;
	return true;
}

bool Environment::Rotate(Homa& homa, Action const nextAction)
{
	if (nextAction == Action::RotateRight)
	{
		homa.m_lookDir = GetRotationClockwise(homa.m_lookDir);
	}
	else if (nextAction == Action::RotateLeft)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			homa.m_lookDir = GetRotationClockwise(homa.m_lookDir);
		}
	}
	return true;
}

//smell, wind, blink, hit, cry;
Homa::ReceptorsState Environment::GetReceptorsState(Homa const& homa) const
{
	auto const pos = homa.m_homaPos;
	return { HasSmell(pos), FeelWind(pos), HasGold(pos), homa.m_hit, ArrowKilled() };
}