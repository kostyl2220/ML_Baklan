#include "pch.h"
#include "LDFS.h"
#include <algorithm>

LDFS::LDFS()
	: m_countOfSteps(0)
{
}


LDFS::~LDFS()
{
}

size_t LDFS::GetSolution(Puzzle& puzzle, size_t maxStep)
{
	m_countOfSteps = 0;
	m_maxStep = maxStep;
	m_curStep = 0;
	auto res = DoDFS(puzzle, Puzzle::Moves::Move_Error);
	while (res > 0)
	{
		res = DoDFS(puzzle, Puzzle::Moves::Move_Error);
	}
	
	return res;
}

size_t LDFS::DoDFS(Puzzle& puzzle, Puzzle::Moves const move)
{
	++m_curStep;
	//printf("%d\n", m_curStep);
	auto res = DoDFSInner(puzzle, move);
	--m_curStep;
	return res;
}

size_t LDFS::DoDFSInner(Puzzle& puzzle, Puzzle::Moves const prevMove)
{
	if (m_curStep >= m_maxStep 
		|| puzzle.IsSolved())
	{
		return puzzle.CountOfMismatch();
	}

	size_t res = 10;
	++m_countOfSteps;
	auto avaliableMoves = puzzle.AvaliableMoves(prevMove);
	for (auto move : avaliableMoves)
	{
		puzzle.PerformMove(move);
		size_t const res = DoDFS(puzzle, move);
		if (res == 0)
		{
			return 0;
		}
		puzzle.PerformMove(Puzzle::GetOppositeMove(move));
	}
	return puzzle.CountOfMismatch();
}

