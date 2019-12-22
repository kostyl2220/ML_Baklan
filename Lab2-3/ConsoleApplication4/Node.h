#pragma once
#include "Puzzle.h"
#include <memory>

class Node
{
public:
	Node();
	~Node();

	Node(Puzzle state)
		: m_state(state)
		, m_cost(0) {};

	Node(Puzzle state, std::shared_ptr<Node> parent, Puzzle::Moves move)
		: m_state(state)
		, m_parent(parent)
		, m_move(move)
		, m_cost(parent->GetPathCost() + 1) {};

	Puzzle::Moves GetMove() const { return m_move; }
	std::shared_ptr<Node> GetParent() const { return m_parent; }
	Puzzle GetState() const { return m_state; }
	size_t GetPathCost() const { return m_cost; }
	size_t GetLimit() const { return m_limit; }
	void SetLimit(size_t limit) { m_limit = limit; }
	bool isRootNode() { return m_parent == nullptr; }


private:
	size_t m_cost;
	Puzzle m_state;
	std::shared_ptr<Node> m_parent;
	Puzzle::Moves m_move;
	size_t m_limit;
};

