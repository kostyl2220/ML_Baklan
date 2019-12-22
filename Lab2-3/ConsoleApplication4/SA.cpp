#include "pch.h"
#include "SA.h"
#include <algorithm>
#include <tgmath.h>

SA::SA()
{
}

const float SA::K = 0.05f;

SA::~SA()
{
}

float GetTemperature(size_t time)
{
	return 1000 - time * SA::K;
}

size_t SA::GetSolution(Puzzle& puzzle)
{
	m_stepCount = 0;
	for (int t = 0; t < 100; ++t)
	{
		for (int i = 0; i < 5; ++i)
		{
			Puzzle copy = puzzle;
			TrySolution(copy, i);
			if (copy.IsSolved())
			{
				m_stepCount / (i + 1);
				puzzle = copy;
				return t;
			}
		}
	}
	return 100;
}

size_t SA::TrySolution(Puzzle& puzzle, size_t coefId)
{
	Puzzle::Moves prevMove = Puzzle::Moves::Move_Error;
	for (int time = 0; time < SIZE_MAX; ++time)
	{
		float const temp = GetTemperature(time);
		
		size_t const oldMismatches = puzzle.CountOfMismatch();
		if (oldMismatches == 0)
		{
			return puzzle.CountOfMismatch();
		}

		++m_stepCount;
		if (temp <= 0)
		{
			return puzzle.CountOfMismatch();
		}

		auto nextMoves = puzzle.AvaliableMoves(prevMove);
		auto nextMove = nextMoves[rand() % nextMoves.size()];


		puzzle.PerformMove(nextMove);
		int const diff = oldMismatches - puzzle.CountOfMismatch();

		if (diff <= 0)
		{
			auto prob = exp(diff * K2[coefId] / temp);
			if ((double)rand() / (RAND_MAX) >= prob)
			{
				puzzle.PerformMove(Puzzle::GetOppositeMove(nextMove));
			}
		}
	}

	return puzzle.CountOfMismatch();
}

