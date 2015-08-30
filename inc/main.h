/*
 * main.h
 *
 *  Created on: 10 sie 2015
 *      Author: piter
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include <iostream>

#include "PuzzleGenerator.h"
#include "PuzzleSolverAStar.h"
#include "PuzzleSolverBfs.h"
#include "PuzzleSolverDfs.h"

using namespace std;

void parseCommandLineArguments(int argc, char* argv[]);
void helpPrintout(char* argv[]);

Puzzle defaultPuzzle =
{
    { 1,  0,  2,  4  },
    { 5,  7,  3,  8  },
    { 9,  6,  10, 11 },
    { 13, 14, 15, 12 }
};

#endif /* INC_MAIN_H_ */
