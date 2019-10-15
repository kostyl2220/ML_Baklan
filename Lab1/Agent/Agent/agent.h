
#ifndef AGENT__
#define AGENT__

#include <string>
using std::string;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent();
	
	enum ActionType { actUP, actDOWN, actLEFT, actRIGHT, actSUCK, actIDLE };

	void Perceive(const Environment &env);
	ActionType Think();
private:
	ActionType RandomThink();
	ActionType SimpleThink();
	ActionType ModelThink();

	struct position
	{
		int x, y;
	};

	position GetPosFromAction(ActionType dir) const;
	int& GetCellFromAction(ActionType dir);

	static const int WALL_ID = -1;
	static const int MAZE_SIZE = 10;
	static const int PLAYER_MAZE_SIZE = MAZE_SIZE * 2 - 1;
	int stored_maze_[PLAYER_MAZE_SIZE][PLAYER_MAZE_SIZE];
	position pos;
	int currentStepId_;
	bool bump_,
		 dirty_;
	ActionType prevAction_;
};

string ActionStr(Agent::ActionType);

#endif
