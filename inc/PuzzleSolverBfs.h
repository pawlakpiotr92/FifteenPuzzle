/*
 * PuzzleSolverBfs.h
 *
 *  Created on: 16 sie 2015
 *      Author: piter
 */

#ifndef INC_PUZZLESOLVERBFS_H_
#define INC_PUZZLESOLVERBFS_H_

#include <queue>
#include "PuzzleSolverBase.h"

class PuzzleSolverBfs: public PuzzleSolverBase
{
  public:
    virtual ~PuzzleSolverBfs();
    explicit PuzzleSolverBfs(const Puzzle& startPuzzle);
    explicit PuzzleSolverBfs(const string& filePath);

  private:
    PuzzleSolverBfs();
    queue<PuzzlePosition> _nodeQueue;
    unsigned int          _numberOfSteps;

    bool addChildNodeToQueue(PuzzlePosition::Direction direction);

    virtual void runAlgorithm();
    virtual void addToContainer(const PuzzlePosition& position);
    virtual void clearContainter();
    virtual void printOutSolution();
};

#endif /* INC_PUZZLESOLVERBFS_H_ */
