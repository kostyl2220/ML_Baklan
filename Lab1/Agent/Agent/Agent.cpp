#include "pch.h"
#include "agent.h"
#include "environment.h"
#include <cstring>
#include <cstdlib>
#include "GUI.h"
#include <time.h>

int main()
{
	srand(time(NULL));

	GUI::control_cb(GUI::START_ID);
	GUI::control_cb(GUI::DO_ALL_RUN_ID);
}

Agent::Agent() 
	: bump_(false)
	, dirty_(false)
	, prevAction_(actIDLE)
	, pos({ MAZE_SIZE , MAZE_SIZE })
	, currentStepId_(0)
{
	memset(stored_maze_, 0, PLAYER_MAZE_SIZE * PLAYER_MAZE_SIZE * sizeof(int));
	stored_maze_[pos.y][pos.x] = ++currentStepId_;
}

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
//    return static_cast<ActionType> (rand()%4);
	
	return RandomThink();
}
// -----------------------------------------------------------

Agent::ActionType Agent::RandomThink()
{
	return static_cast<ActionType> (rand() % 6);
}

Agent::ActionType Agent::SimpleThink()
{
	if (dirty_) 
	{
		return actSUCK;
	}
	return static_cast<ActionType> (rand()%4);
}

Agent::ActionType Agent::ModelThink()
{
	if (bump_)
	{
		//store wall
		GetCellFromAction(prevAction_) = WALL_ID;
	}
	else
	{
		//moved a bit
		pos = GetPosFromAction(prevAction_);
		GetCellFromAction(actIDLE) = ++currentStepId_;
	}

	if (dirty_)
	{
		prevAction_ = actSUCK;
		return prevAction_;
	}

	//unvisited data
	ActionType avaliableMoves[4];
	int curUnvisitedMoveId = 0;

	//already visited
	ActionType latestVisitedDir = actUP;
	int dirId = currentStepId_;

	for (int i = 0; i < 4; ++i)
	{
		ActionType nextMove = static_cast<ActionType>(i);
		int& cellState = GetCellFromAction(nextMove);
		if (cellState == WALL_ID)
		{
			continue;
		}
		if (cellState > 0) 
		{
			if (cellState < dirId)
			{
				//was visited
				dirId = cellState;
				latestVisitedDir = nextMove;
			}
		}
		else
		{
			avaliableMoves[curUnvisitedMoveId++] = nextMove;
		}
	}
	
	prevAction_ = curUnvisitedMoveId > 0 ? avaliableMoves[rand() % curUnvisitedMoveId] : latestVisitedDir;
	return prevAction_;
}

Agent::position Agent::GetPosFromAction(ActionType dir) const
{
	switch (dir)
	{
	case Agent::actUP:
		return { pos.x, pos.y - 1 };
	case Agent::actDOWN:
		return { pos.x, pos.y + 1 };
	case Agent::actLEFT:
		return { pos.x - 1, pos.y };
	case Agent::actRIGHT:
		return { pos.x + 1, pos.y };
	case Agent::actSUCK:
		return { pos.x, pos.y };
	case Agent::actIDLE:
		return { pos.x, pos.y };
	default:
		return { pos.x, pos.y };
	}
}

int& Agent::GetCellFromAction(ActionType dir)
{
	position pos = GetPosFromAction(dir);
	return stored_maze_[pos.y][pos.x];
}

// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	bump_ = env.isJustBump();
	dirty_ = env.isCurrentPosDirty();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType action)
{
	switch (action)
	{
	case Agent::actUP: return "UP";
	case Agent::actDOWN: return "DOWN";
	case Agent::actLEFT: return "LEFT";
	case Agent::actRIGHT: return "RIGHT";
	case Agent::actSUCK: return "SUCK";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
