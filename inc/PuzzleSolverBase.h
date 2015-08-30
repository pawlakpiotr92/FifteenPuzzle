/*
 * PuzzleSolver.h
 *
 *  Created on: 10 sie 2015
 *      Author: piter
 */

#ifndef INC_PUZZLESOLVERBASE_H_
#define INC_PUZZLESOLVERBASE_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <list>
#include <chrono>

#include "PuzzlePosition.h"

using namespace std;
using namespace chrono;

typedef high_resolution_clock::time_point timePoint;

class PuzzleSolverBase
{
  public:
    void parseFileWithPuzzle(const string& filePath);
    void solvePuzzle();

  protected:
    PuzzleSolverBase();
    virtual ~PuzzleSolverBase();
    explicit PuzzleSolverBase(const Puzzle& startPuzzle);

    virtual void runAlgorithm() = 0;
    virtual void addToContainer(const PuzzlePosition& position) = 0;
    virtual void clearContainter() = 0;
    virtual void printOutSolution() = 0;

    list<PuzzlePosition> _nodeHistory;
    timePoint            _clkStart;
    timePoint            _clkStop;
    Puzzle               _startPuzzle;
    int                  _maxNumberOfSteps;

    inline microseconds calculateExecutionTime()
    {
      return duration_cast<microseconds>(_clkStop - _clkStart);
    }
};

#endif /* INC_PUZZLESOLVERBASE_H_ */
