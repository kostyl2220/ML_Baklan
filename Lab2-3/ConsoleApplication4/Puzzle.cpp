#include "pch.h"
#include "Puzzle.h"


Puzzle::Pos Puzzle::Pos::AddedPos(int y, int x) const
{
	Pos newPos = *this;
	newPos.y += y;
	newPos.x += x;
	return newPos;
}

Puzzle::Puzzle()
{
	for (size_t y = 0; y < 3; ++y)
	{
		for (size_t x = 0; x < 3; ++x)
		{
			m_field[y][x] = y * 3 + x;
		}
	}

	m_emptyPos = Pos(0, 0);
}


Puzzle::~Puzzle()
{
}

size_t Puzzle::CountOfMismatch() const
{
	size_t count = 0;
	for (size_t y = 0; y < 3; ++y)
	{
		for (size_t x = 0; x < 3; ++x)
		{
			if (m_field[y][x] != y * 3 + x)
			{
				++count;
			}
		}
	}

	if (count == 1)
	{
		count = 0;
	}

	return count;
}

bool Puzzle::IsSolved() const
{
	return (CountOfMismatch() == 0);
}

void Puzzle::ShowField() const
{
	printf("Current field: \n");
	for (size_t y = 0; y < 3; ++y)
	{
		for (size_t x = 0; x < 3; ++x)
		{
			char const output = (m_field[y][x] > 0) ? m_field[y][x] + 48 : ' ';
			printf("%2c", output);	
		}
		printf("\n");
	}
}

void Puzzle::ShufflePuzzle(size_t countOfShuffles)
{
	Moves prevMove = Moves::Move_Error;
	for (auto i = 0; i < countOfShuffles; ++i)
	{
		auto avaliableMoves = AvaliableMoves(prevMove);
		prevMove = avaliableMoves[rand() % avaliableMoves.size()];
		PerformMove(prevMove);
	}
}

std::vector<Puzzle::Moves> Puzzle::AvaliableMoves(Puzzle::Moves prevMove) const
{
	std::vector<Puzzle::Moves> avaliableMoves;
	avaliableMoves.reserve((size_t)Moves::Move_Count);
	for (size_t i = 0; i < (size_t)Moves::Move_Count; ++i)
	{
		Moves currentMove = (Moves)i;
		if (currentMove != GetOppositeMove(prevMove) && IsMoveAvaliable(currentMove))
		{
			avaliableMoves.push_back(currentMove);
		}
	}

	return avaliableMoves;
}

bool Puzzle::IsMoveAvaliable(Moves move) const
{
	switch (move)
	{
	case Puzzle::Moves::Move_UP:
		return m_emptyPos.y < 2;
	case Puzzle::Moves::Move_DOWN:
		return m_emptyPos.y > 0;
	case Puzzle::Moves::Move_RIGHT:
		return m_emptyPos.x > 0;
	case Puzzle::Moves::Move_LEFT:
		return m_emptyPos.x < 2;
	default:
		return false;
	}
}

Puzzle::Moves Puzzle::GetOppositeMove(Moves move)
{
	switch (move)
	{
	case Puzzle::Moves::Move_UP:
		return Moves::Move_DOWN;
	case Puzzle::Moves::Move_DOWN:
		return Moves::Move_UP;
	case Puzzle::Moves::Move_RIGHT:
		return Moves::Move_LEFT;
	case Puzzle::Moves::Move_LEFT:
		return Moves::Move_RIGHT;
	default:
		return Moves::Move_Error;
	}
}

bool Puzzle::PerformMove(Moves move)
{
	if (!IsMoveAvaliable(move))
	{
		return false;
	}

	Pos posToMoveFrom;
	switch (move)
	{
	case Puzzle::Moves::Move_UP:
		posToMoveFrom = m_emptyPos.AddedPos(1, 0);
		break;
	case Puzzle::Moves::Move_DOWN:
		posToMoveFrom = m_emptyPos.AddedPos(-1, 0);
		break;
	case Puzzle::Moves::Move_RIGHT:
		posToMoveFrom = m_emptyPos.AddedPos(0, -1);
		break;
	case Puzzle::Moves::Move_LEFT:
		posToMoveFrom = m_emptyPos.AddedPos(0, 1);
		break;
	default:
		return false;
	}

	m_field[m_emptyPos.y][m_emptyPos.x] = m_field[posToMoveFrom.y][posToMoveFrom.x];
	m_field[posToMoveFrom.y][posToMoveFrom.x] = 0;
	m_emptyPos = posToMoveFrom;
	return true;
}