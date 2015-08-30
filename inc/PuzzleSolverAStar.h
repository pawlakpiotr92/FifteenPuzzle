/*
 * PuzzleSolverAStar.h
 *
 *  Created on: 23 sie 2015
 *      Author: piter
 */

#ifndef INC_PUZZLESOLVERASTAR_H_
#define INC_PUZZLESOLVERASTAR_H_

#include <cmath>
#include "PuzzleSolverBase.h"

typedef map<int, PuzzlePosition> sortedList;
typedef pair<int, PuzzlePosition> indexPair;

class PuzzleSolverAStar : public PuzzleSolverBase
{
  public:
    virtual ~PuzzleSolverAStar();
    explicit PuzzleSolverAStar(const Puzzle& startPuzzle);
    explicit PuzzleSolverAStar(const string& filePath);

  private:
    PuzzleSolverAStar();
    sortedList _nodeSortedList;
    int        _numberOfSteps;

    virtual void runAlgorithm();
    virtual void addToContainer(const PuzzlePosition& position);
    virtual void clearContainter();
    virtual void printOutSolution();

    void insertSortedNode(const PuzzlePosition& position);
    list<PuzzlePosition> getSuccessors(PuzzlePosition& position);
};

#endif /* INC_PUZZLESOLVERASTAR_H_ */
