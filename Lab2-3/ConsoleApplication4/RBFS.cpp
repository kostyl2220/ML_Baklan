#include "pch.h"
#include "RBFS.h"
#include <algorithm>

RBFS::RBFS()
	: m_countOfSteps(0)
{
}


RBFS::~RBFS()
{
}

std::shared_ptr<Node> RBFS::GetSolution(Puzzle const& puzzle)
{
	m_countOfSteps = 0;
	auto node = std::make_shared<Node>(Node(puzzle));
	return DoDFS(node, node->GetState().CountOfMismatch(), SIZE_MAX, 0);
}

std::vector<std::shared_ptr<Node>> RBFS::ExpandNode(std::shared_ptr<Node> node)
{
	std::vector<std::shared_ptr<Node>> res;

	for (auto move : node->GetState().AvaliableMoves(node->GetMove()))
	{
		Puzzle stateCopy = node->GetState();
		stateCopy.PerformMove(move);
		auto childNode = std::make_shared<Node>(Node(stateCopy, node, move));
		res.push_back(childNode);
	}

	return res;
}

size_t AltBestFIndex(std::vector<size_t> const& costs, size_t best)
{
	if (costs.size() == 1)
	{
		return best;
	}
	size_t minValue = best == 0 ? 1 : 0;
	for (size_t i = 0; i < costs.size(); ++i)
	{
		if (costs[i] < costs[minValue] && i != best)
		{
			minValue = i;
		}
	}

	return minValue;
}

size_t GetBestFIndex(std::vector<size_t> const& costs)
{
	size_t minValue = 0;
	for (size_t i = 0; i < costs.size(); ++i)
	{
		if (costs[i] < costs[minValue])
		{
			minValue = i;
		}
	}

	return minValue;
}

std::shared_ptr<Node> RBFS::DoDFS(std::shared_ptr<Node>& node, size_t nodeF, size_t limitF, size_t recDepth)
{
	if (node->GetState().IsSolved())
	{
		node->SetLimit(SIZE_MAX);
		return node;
	}

	++m_countOfSteps;
	auto successors = ExpandNode(node);
	if (successors.empty())
	{
		node->SetLimit(SIZE_MAX);
		return node;
	}

	std::vector<size_t> costs;
	costs.reserve(successors.size());

	std::shared_ptr<Node> minFNode = nullptr;
	for (auto child : successors)
	{
		costs.push_back(std::max(child->GetState().CountOfMismatch() + child->GetPathCost(), nodeF));
	}

	while (true)
	{
		size_t bestFIndex = GetBestFIndex(costs);

		if (costs[bestFIndex] > limitF)
		{
			node->SetLimit(costs[bestFIndex]);
			return node;
		}

		size_t altBestFIndex = AltBestFIndex(costs, bestFIndex);
		auto res = DoDFS(successors[bestFIndex], costs[bestFIndex], std::min(limitF, costs[altBestFIndex]), recDepth + 1);
		costs[bestFIndex] = res->GetLimit();

		if (res->GetState().IsSolved()
			|| !res->GetState().IsSolved() && res->GetLimit() == SIZE_MAX)
		{
			return res;
		}
	}

}