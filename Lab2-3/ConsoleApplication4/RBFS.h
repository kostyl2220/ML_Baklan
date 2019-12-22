#pragma once
#include "Puzzle.h"
#include "Node.h"
#include <memory>
#include <vector>

class RBFS
{
public:
	RBFS();
	~RBFS();

	std::shared_ptr<Node> GetSolution(Puzzle const& puzzle);

	size_t GetStepCount() const { return m_countOfSteps; }

private:
	std::vector<std::shared_ptr<Node>> ExpandNode(std::shared_ptr<Node> node);
	std::shared_ptr<Node> DoDFS(std::shared_ptr<Node>&, size_t, size_t limitF, size_t recDepth);

	size_t m_countOfSteps;
};

