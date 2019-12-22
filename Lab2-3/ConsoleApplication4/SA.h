#pragma once
#include "Puzzle.h"


static float const K2[5] = { 1000.f, 800.f, 500.f, 200.f, 100.f };

class SA
{
public:
	SA();
	~SA();

	static float const K;

	size_t GetSolution(Puzzle& puzzle);
	size_t GetStepCount() const { return m_stepCount; }

private:
	size_t TrySolution(Puzzle& puzzle, size_t coefId);
	size_t m_stepCount = 0;
};

