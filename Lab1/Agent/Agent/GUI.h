#ifndef GUI_H
#define GUI_H

#include<fstream>

namespace GUI{
	const extern int DISPLAY_ID, START_ID, DO_ONE_RUN_ID, DO_ALL_RUN_ID, DO_ONE_STEP_ID, NEXT_RUN_ID;


	void Display();//ø�� 
	void control_cb(int);//�ϧΤ����Ҧ����s���� 
	int startDraw(int,char *[]);
	void showScore();
	void SetupSimulation();
	
	void doOneStep();
	void doOneRun();
	void doAllRun();
	void nextRun();
	void newGame();
};
#endif
