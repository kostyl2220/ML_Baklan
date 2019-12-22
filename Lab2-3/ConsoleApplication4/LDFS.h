#pragma once
#include "Puzzle.h"

class LDFS
{
public:
	LDFS();
	~LDFS();

	size_t GetSolution(Puzzle& puzzle, size_t const maxStep);
	size_t GetStepCount() const { return m_countOfSteps; }
private: 
	size_t DoDFS(Puzzle& puzzle, Puzzle::Moves const move);
	size_t DoDFSInner(Puzzle& puzzle, Puzzle::Moves const move);

	size_t m_curStep;
	size_t m_maxStep;
	size_t m_countOfSteps;
};

