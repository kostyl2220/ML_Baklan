#include "pch.h"
#include<fstream>
#include<sstream>
#include<iomanip>
#include<iostream>
#include<windows.h>
using namespace std;
#include"GUI.h"
using namespace GUI;
#include<stdlib.h>
#include"random_num_gen.h"
#include"environment.h"
#include"agent.h"
#include"evaluator.h"

namespace GUI
{
	const int DISPLAY_ID = 1, START_ID = 0, DO_ONE_RUN_ID = 2, DO_ALL_RUN_ID = 3, DO_ONE_STEP_ID = 4, NEXT_RUN_ID = 5;
}

char file_name[1000]="map/agent.map";
long long life_time=1000,current_time,total_runs=20,current_run,dirty_degree,consumed_energy;
long long total_dirty_degree,total_consumed_energy;

Environment *env=NULL;
Agent *agent=NULL;
RandomNumberGenerator *rng=NULL;
Evaluator *evaluator=NULL;
Agent::ActionType action=Agent::actIDLE;
ifstream fin;

void GUI::Display(){
	system("cls");
	env->Show();
	showScore();
	system("pause");
}

void GUI::SetupSimulation()
{
	current_run = 1;
	total_dirty_degree = 0;
	total_consumed_energy = 0;
	newGame();
}

void GUI::control_cb(int id){
	switch(id){
		case DISPLAY_ID:
			Display();
			break;
		case START_ID:
			SetupSimulation();
			break;
		case DO_ONE_STEP_ID:
			doOneStep();
			Display();
			break;
		case DO_ONE_RUN_ID:
			doOneRun();
			Display();
			break;
		case NEXT_RUN_ID:
			nextRun();
			Display();
			break;
		case DO_ALL_RUN_ID:
			doAllRun();
			Display();
			break;
		default:
			break;
	}
}
int GUI::startDraw(int argc,char **argv){
	
	return 0;
}

void GUI::showScore(){
	cout << "Run " << current_run << "  ,Time step " << current_time << endl;

	cout <<"Action "<<ActionStr(action)<<(env->isJustBump()?" Bump!":"") << endl;
	
	cout <<"DirtyDegree = "<<dirty_degree << endl;
	
	cout <<"ConsumedEnergy =  "<<consumed_energy << endl;
	
	/*展示總分*/
	long long complete_runs=current_run-(current_time!=life_time);
	//The Round has been completed 
	cout <<"Completed Runs "<<complete_runs << endl;
	
	cout <<"Total dirty degree =  "<<total_dirty_degree<<"   ,toal consumed energy = "<<total_consumed_energy << endl;
	
	if(complete_runs>0){
		cout <<setprecision(3)<<fixed<<"Average dirty degree = "<<(double)total_dirty_degree/(double)complete_runs<<"  ,Average consumed energy = "<<(double)total_consumed_energy/(double)complete_runs << endl;
	}
	else{
		cout <<"Average dirty degree = 0  ,Average consumed energy = 0" << endl;
	}	
}

void GUI::doOneStep(){
	if(current_time<life_time){
		env->Change(*rng);
		
		agent->Perceive(*env);
		
		action = agent->Think();
		env->AcceptAction(action);
		evaluator->Eval(action,*env);
		
		dirty_degree=evaluator->DirtyDegree();
		consumed_energy=evaluator->ConsumedEnergy();
		
		++current_time;
		if(current_time==life_time){//一輪結束 

			total_dirty_degree+=dirty_degree;
			total_consumed_energy+=consumed_energy;
		}
	}
}
void GUI::doOneRun(){

	while(current_time<life_time){
		doOneStep();
	}
}
void GUI::doAllRun(){
	doOneRun();
	while(current_run<total_runs){
		nextRun();
		doOneRun();
	}
}
void GUI::nextRun(){
	if(current_run<total_runs){
		++current_run;
		newGame();
	}
}

void GUI::newGame(){
	fin.close();
	fin.clear();
	delete env;
	delete agent;
	delete rng;
	delete evaluator;

	fin.open(file_name);
	if(fin){
		current_time=0;
		dirty_degree=0;
		consumed_energy=0;
		env=new Environment(fin);
		rng=new RandomNumberGenerator(env->RandomSeed()+current_run);
		evaluator=new Evaluator();
		agent=new Agent();
	}
	else{
		fin.clear();
		fin.open(file_name);
		if(fin){
			current_time=0;
			dirty_degree=0;
			consumed_energy=0;
			env=new Environment(fin);
			rng=new RandomNumberGenerator(env->RandomSeed()+current_run);
			evaluator=new Evaluator();
			agent=new Agent();
		}
		else{
		}
	}
}
