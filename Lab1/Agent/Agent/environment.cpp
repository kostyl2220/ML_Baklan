#include "pch.h"
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
#include <string>
using std::string;
#include "stdlib.h"

#include "environment.h"
#include "random_num_gen.h"

Environment::Environment(ifstream &infile)
{
	string comment;
	getline(infile, comment);
	infile >> agentPosX_ >> agentPosY_ >> dirtyProb_ >> randomSeed_;;
	
	for (int row=0; row<MAZE_SIZE; row+=1)
	{
		for (int col=0; col<MAZE_SIZE; col+=1)
		{
			char c;
			infile >> c;
			if (c == MAP_ROAD) {
   				maze_[row][col] = 0;
			}
			else if (c == MAP_OBSTACLE) {
   				maze_[row][col] = OBSTACLE;
			}
			else {
				cout << c << " is an unknown symbol in agent.map!"; exit(1);
			}
		}// for - col
	}// for - row
	
	bump_ = false;
	preAction_=Agent::actIDLE;
}
// -----------------------------------------------------------
int Environment::DirtAmount(int x, int y) const
{
	if (maze_[x][y] == OBSTACLE) return 0;
	else return maze_[x][y];
}
// -----------------------------------------------------------	
void Environment::Show() const
{
	for (int row=0; row<MAZE_SIZE; row+=1)
	{
		for (int col=0; col<MAZE_SIZE; col+=1)
		{
			if (maze_[row][col] == OBSTACLE){
				cout << "###";
			}
			else 
			{
   				if (row == agentPosX_ && col == agentPosY_){
					char const actions[6] = { 'u', 'd', 'l', 'r', 's', 'i' };
					printf("%2c ", actions[preAction_]);
				}
				else
				{
					printf("%2d ", DirtAmount(row, col));
				}
			}
		}
		cout << endl;
	}
}
// -----------------------------------------------------------
void Environment::Change(const RandomNumberGenerator &rng)
{
	for (int row=0; row<MAZE_SIZE; row+=1)
	{
		for (int col=0; col<MAZE_SIZE; col+=1)
		{
			if (maze_[row][col] != OBSTACLE && 
			    static_cast<double>(rng.RandomValue())/RAND_MAX < dirtyProb_) // probability: 0.01
			{
				maze_[row][col] += 1;
			}
		}// for - col
	}// for - row
}
// -----------------------------------------------------------
void Environment::AcceptAction(Agent::ActionType action)
{
	bump_ = false;
	switch (action)
	{
		case Agent::actSUCK:
			if(maze_[agentPosX_][agentPosY_] > 0){
				maze_[agentPosX_][agentPosY_] -= 1;
			}
			break;
		case Agent::actUP:
			if (maze_[agentPosX_-1][agentPosY_] != OBSTACLE) agentPosX_-=1;
			else bump_ = true;
			break;
		case Agent::actDOWN:
			if (maze_[agentPosX_+1][agentPosY_] != OBSTACLE) agentPosX_+=1;
			else bump_ = true;			
			break;
		case Agent::actLEFT:
			if (maze_[agentPosX_][agentPosY_-1] != OBSTACLE) agentPosY_-=1;
			else bump_ = true;			
			break;
		case Agent::actRIGHT:
			if (maze_[agentPosX_][agentPosY_+1] != OBSTACLE) agentPosY_+=1;
			else bump_ = true;			
			break;    		
	}
	preAction_=action;
}
// -----------------------------------------------------------
