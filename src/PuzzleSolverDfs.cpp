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
PuzzleSolverDfs::addChildNodeToStack(PuzzlePosition::Direction direction, const PuzzlePosition &oldNode)
{
  PuzzlePosition tmp = oldNode;
  it nodeInHistory = find(_nodeHistory.begin(),
                          _nodeHistory.end(),
                          oldNode);
  tmp.moveZero(direction);
  tmp.setPreviousPosition(nodeInHistory);

  nodeInHistory = find(_nodeHistory.begin(),
                       _nodeHistory.end(),
                       tmp);
  
  if (nodeInHistory != _nodeHistory.end() && nodeInHistory->getPreviousPosition() == tmp.getPreviousPosition())
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

void
PuzzleSolverDfs::runAlgorithm()
{

  if (_nodeStack.empty())
  {
    throw false;
  }
  
  if (_nodeStack.top().isFinalNode())
  {
    _clkStop = high_resolution_clock::now();
    throw true;
  }
  
  if (_nodeStack.top().getDepth() > _maxNumberOfSteps)
  {
    _nodeStack.pop();
    runAlgorithm();
  }
  
  PuzzlePosition tmp = _nodeStack.top();
  _nodeStack.pop();
  
  int x, y;
  tmp.findZeroPosition(x, y);
  if (!tmp.zeroIsOverUpperEdge(y))
  {
    addChildNodeToStack(PuzzlePosition::Up, tmp);
  }
  if (!tmp.zeroIsOverRightEdge(x))
  {
    addChildNodeToStack(PuzzlePosition::Right, tmp);
  }
  if (!tmp.zeroIsOverLowerEdge(y))
  {
    addChildNodeToStack(PuzzlePosition::Down, tmp);
  }
  if (!tmp.zeroIsOverLeftEdge(x))
  {
    addChildNodeToStack(PuzzlePosition::Left, tmp);
  }
  
  runAlgorithm();
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

