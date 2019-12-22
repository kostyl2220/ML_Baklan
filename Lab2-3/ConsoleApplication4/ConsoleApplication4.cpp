// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <time.h>
#include "Puzzle.h"
#include "LDFS.h"
#include "RBFS.h"
#include "SA.h"
#include <chrono>

int main()
{
	srand(time(NULL));
	Puzzle puzzle;
	size_t const shuffleCount = 50;

	LDFS ldfs;
	RBFS rbsf;
	SA sa;

	size_t const countOfTries = 10;
	size_t countOfSteps = 0;
	size_t countOfFails = 0;

	long long totalDuration = 0;
	for (auto i = 0; i < countOfTries; ++i)
	{
		puzzle.ShufflePuzzle(shuffleCount);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		countOfFails += sa.GetSolution(puzzle);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		countOfSteps += sa.GetStepCount();
	}

	std::cout << "Time difference = " << totalDuration / countOfTries << "[ns]" << std::endl;
	printf("Average step count %f\n", (float)countOfSteps / countOfTries);
	printf("Average fail count %f\n", (float)countOfFails / countOfTries);
	puzzle.ShowField();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


