#include "../inc/PuzzleSolverBfs.h"

PuzzleSolverBfs::PuzzleSolverBfs() :
    PuzzleSolverBase(),
    _nodeQueue(queue<PuzzlePosition>()),
    _numberOfSteps(0)
{
}

PuzzleSolverBfs::~PuzzleSolverBfs()
{
}

PuzzleSolverBfs::PuzzleSolverBfs(const Puzzle& startPuzzle) :
    PuzzleSolverBase(startPuzzle),
    _nodeQueue(queue<PuzzlePosition>()),
    _numberOfSteps(0)
{
  solvePuzzle();
}

PuzzleSolverBfs::PuzzleSolverBfs(const string& filePath) :
    PuzzleSolverBase(),
    _nodeQueue(queue<PuzzlePosition>()),
    _numberOfSteps(0)
{
  parseFileWithPuzzle(filePath);
  solvePuzzle();
}

void
PuzzleSolverBfs::runAlgorithm()
{
  _numberOfSteps++;
  if (_nodeQueue.front().isFinalNode())
  {
    _clkStop = high_resolution_clock::now();
    throw true;
  }

  if (_nodeQueue.empty() || _numberOfSteps == _maxNumberOfSteps)
  {
    _numberOfSteps = 0;
    throw false;
  }

  int x, y;
  _nodeQueue.front().findZeroPosition(x, y);

  if (!_nodeQueue.front().zeroIsOverUpperEdge(y))
  {
    addChildNodeToQueue(PuzzlePosition::Up);
  }
  if (!_nodeQueue.front().zeroIsOverRightEdge(x))
  {
    addChildNodeToQueue(PuzzlePosition::Right);
  }
  if (!_nodeQueue.front().zeroIsOverLowerEdge(y))
  {
    addChildNodeToQueue(PuzzlePosition::Down);
  }
  if (!_nodeQueue.front().zeroIsOverLeftEdge(x))
  {
    addChildNodeToQueue(PuzzlePosition::Left);
  }

  _nodeQueue.pop();
  runAlgorithm();
}

bool
PuzzleSolverBfs::addChildNodeToQueue(PuzzlePosition::Direction direction)
{
  PuzzlePosition tmp = _nodeQueue.front();
  it nodeInHistory = find(_nodeHistory.begin(),
                          _nodeHistory.end(),
                          tmp);
  tmp.moveZero(direction);
  tmp.setPreviousPosition(nodeInHistory);

  if (tmp != *_nodeQueue.front().getPreviousPosition())
  {
    nodeInHistory = find(_nodeHistory.begin(),
                         _nodeHistory.end(),
                         tmp);

    if (nodeInHistory != _nodeHistory.end())
    {
      return false;
    }
    else
    {
      _nodeQueue.push(tmp);
      _nodeHistory.push_back(tmp);
      return true;
    }
  }
  return false;
}

void
PuzzleSolverBfs::addToContainer(const PuzzlePosition& position)
{
  _nodeQueue.push(position);
  _nodeQueue.back().setPreviousPosition(_nodeHistory.end());
}

void
PuzzleSolverBfs::clearContainter()
{
  while (!_nodeQueue.empty())
  {
    _nodeQueue.pop();
  }
}

void
PuzzleSolverBfs::printOutSolution()
{
  it temporaryIterator = find(_nodeHistory.begin(),
                              _nodeHistory.end(),
                              _nodeQueue.front());

  while (temporaryIterator != _nodeHistory.end())
  {
    cout << *temporaryIterator << endl;
    temporaryIterator = temporaryIterator->getPreviousPosition();
  }
}
