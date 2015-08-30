/*
 * PuzzleSolverDfs.cpp
 *
 *  Created on: 16 sie 2015
 *      Author: piter
 */

#include "../inc/PuzzleSolverDfs.h"

PuzzleSolverDfs::PuzzleSolverDfs() :
    PuzzleSolverBase(),
    _nodeStack(stack<PuzzlePosition>())
{
}

PuzzleSolverDfs::PuzzleSolverDfs(const Puzzle& startPuzzle) :
    PuzzleSolverBase(startPuzzle),
    _nodeStack(stack<PuzzlePosition>())
{
  solvePuzzle();
}

PuzzleSolverDfs::PuzzleSolverDfs(const string& filePath) :
    PuzzleSolverBase(),
    _nodeStack(stack<PuzzlePosition>())
{
  parseFileWithPuzzle(filePath);
  solvePuzzle();
}

PuzzleSolverDfs::~PuzzleSolverDfs()
{
}

bool
PuzzleSolverDfs::addChildNodeToStack(PuzzlePosition::Direction direction)
{
  PuzzlePosition tmp = _nodeStack.top();
  it nodeInHistory = find(_nodeHistory.begin(),
                          _nodeHistory.end(),
                          tmp);
  tmp.moveZero(direction);
  tmp.setPreviousPosition(nodeInHistory);

  if (tmp != *_nodeStack.top().getPreviousPosition())
  {
    nodeInHistory = find(_nodeHistory.begin(),
                         _nodeHistory.end(),
                         tmp);
    if (*nodeInHistory == tmp && nodeInHistory->getPreviousPosition() == tmp.getPreviousPosition())
    {
      return false;
    }
    else
    {
      _nodeStack.push(tmp);
      _nodeHistory.push_back(tmp);
      return true;
    }
  }
  return false;
}

void
PuzzleSolverDfs::runAlgorithm()
{
  if (_nodeStack.size() > _maxNumberOfSteps)
  {
    return;
  }

  if (_nodeStack.top().isFinalNode())
  {
    _clkStop = high_resolution_clock::now();
    throw true;
  }

  if (_nodeStack.empty())
  {
    throw false;
  }

  int x, y;
  _nodeStack.top().findZeroPosition(x, y);
  if (!_nodeStack.top().zeroIsOverUpperEdge(y))
  {
    if (addChildNodeToStack(PuzzlePosition::Up))
    {
      runAlgorithm();
      _nodeStack.pop();
    }
  }
  if (!_nodeStack.top().zeroIsOverRightEdge(x))
  {
    if (addChildNodeToStack(PuzzlePosition::Right))
    {
      runAlgorithm();
      _nodeStack.pop();
    }
  }
  if (!_nodeStack.top().zeroIsOverLowerEdge(y))
  {
    if (addChildNodeToStack(PuzzlePosition::Down))
    {
      runAlgorithm();
      _nodeStack.pop();
    }
  }
  if (!_nodeStack.top().zeroIsOverLeftEdge(x))
  {
    if (addChildNodeToStack(PuzzlePosition::Left))
    {
      runAlgorithm();
      _nodeStack.pop();
    }
  }
}

void
PuzzleSolverDfs::addToContainer(const PuzzlePosition& position)
{
  _nodeStack.push(position);
  _nodeStack.top().setPreviousPosition(_nodeHistory.end());
}

void
PuzzleSolverDfs::clearContainter()
{
  while (!_nodeStack.empty())
  {
    _nodeStack.pop();
  }
}

void
PuzzleSolverDfs::printOutSolution()
{
  it temporaryIterator = find(_nodeHistory.begin(),
                              _nodeHistory.end(),
                              _nodeStack.top());

  while (temporaryIterator != _nodeHistory.end())
  {
    cout << *temporaryIterator << endl;
    temporaryIterator = temporaryIterator->getPreviousPosition();
  }
}

