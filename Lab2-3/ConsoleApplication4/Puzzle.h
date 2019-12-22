#pragma once
#include <vector>

class Puzzle
{
public:
	Puzzle();
	~Puzzle();
	 
	struct Pos
	{
		Pos() {}
		Pos(int _y, int _x) : x(_x), y(_y) {}

		int y, x;

		Pos AddedPos(int y, int x) const;
	};

	enum class Moves
	{
		Move_UP,
		Move_DOWN,
		Move_RIGHT,
		Move_LEFT,
		Move_Count,
		Move_Error
	};

	size_t CountOfMismatch() const;
	bool IsSolved() const;
	void ShowField() const;
	void ShufflePuzzle(size_t countOfShuffles);
	std::vector<Moves> AvaliableMoves(Moves prevMove) const;
	
	bool PerformMove(Moves move);
	bool IsMoveAvaliable(Moves move) const;

	static Moves GetOppositeMove(Moves move);
private:
	int m_field[3][3];

	//helper
	Pos m_emptyPos;
};

