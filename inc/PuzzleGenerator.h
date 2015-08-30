/*
 * PuzzleGenerator.h
 *
 *  Created on: 23 sie 2015
 *      Author: piter
 */

#ifndef INC_PUZZLEGENERATOR_H_
#define INC_PUZZLEGENERATOR_H_

#include <list>
#include <time.h>
#include <chrono>
#include <algorithm>
#include "PuzzlePosition.h"

using namespace std;
using namespace chrono;

typedef list<PuzzlePosition>::iterator it;

class PuzzleGenerator
{
  public:
    PuzzleGenerator();
    PuzzlePosition generatePuzzle(unsigned int amountOfSteps);
};

#endif /* INC_PUZZLEGENERATOR_H_ */
