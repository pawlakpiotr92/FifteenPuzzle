#include "../inc/PuzzleSolverAStar.h"

PuzzleSolverAStar::PuzzleSolverAStar() :
    PuzzleSolverBase(),
    _nodeSortedList(sortedList()),
    _numberOfSteps(0)
{
}

PuzzleSolverAStar::~PuzzleSolverAStar()
{
}

PuzzleSolverAStar::PuzzleSolverAStar(const Puzzle& startPuzzle) :
    PuzzleSolverBase(startPuzzle),
    _nodeSortedList(sortedList()),
    _numberOfSteps(0)
{
  solvePuzzle();
}

PuzzleSolverAStar::PuzzleSolverAStar(const string& filePath) :
    PuzzleSolverBase(),
    _nodeSortedList(sortedList()),
    _numberOfSteps(0)
{
  parseFileWithPuzzle(filePath);
  solvePuzzle();
}

void
PuzzleSolverAStar::runAlgorithm()
{
  _numberOfSteps++;
  if (_nodeSortedList.empty() || _numberOfSteps == _maxNumberOfSteps)
  {
    _numberOfSteps = 0;
    throw false;
  }

  PuzzlePosition puzzle = _nodeSortedList.begin()->second;

  if (puzzle.isFinalNode())
  {
    _clkStop = high_resolution_clock::now();
    throw true;
  }
  _nodeSortedList.erase(puzzle.getHeuristic());

  list<PuzzlePosition> successors = getSuccessors(puzzle);
  if (!successors.empty())
  {
    for (PuzzlePosition child : successors)
    {
      it historyIterator = find(_nodeHistory.begin(),
                                _nodeHistory.end(),
                                child);
      if (historyIterator != _nodeHistory.end())
      {
        if (historyIterator->getDepth() > child.getDepth())
        {
          historyIterator->setDepth(child.getDepth());
          insertSortedNode(child);
        }
      }
      else
      {
        _nodeHistory.push_back(child);
        insertSortedNode(child);
      }
    }
  }

  runAlgorithm();
}

void
PuzzleSolverAStar::addToContainer(const PuzzlePosition& position)
{
  position.calculateHeuristic();
  _nodeSortedList[position.getHeuristic()] = position;
  _nodeSortedList[position.getHeuristic()].setPreviousPosition(_nodeHistory.end());
}

void
PuzzleSolverAStar::clearContainter()
{
  _nodeSortedList.clear();
}

void
PuzzleSolverAStar::printOutSolution()
{
  indexPair tmp = *_nodeSortedList.begin();
  it temporaryIterator = find(_nodeHistory.begin(),
                              _nodeHistory.end(),
                              tmp.second);

  while (temporaryIterator != _nodeHistory.end())
  {
    cout << *temporaryIterator << endl;
    temporaryIterator = temporaryIterator->getPreviousPosition();
  }
}

void
PuzzleSolverAStar::insertSortedNode(const PuzzlePosition& position)
{
  //_nodeSortedList.insert(indexPair(position.getHeuristic(), position));
  _nodeSortedList[position.getHeuristic()] = position;
}

list <PuzzlePosition>
PuzzleSolverAStar::getSuccessors(PuzzlePosition& position)
{
  it temporaryIterator = find(_nodeHistory.begin(),
                              _nodeHistory.end(),
                              position);

  list<PuzzlePosition> successors;
  if (temporaryIterator != _nodeHistory.end())
  {

    int x, y;
    position.findZeroPosition(x, y);
    if (!position.zeroIsOverUpperEdge(y))
    {
      successors.push_front(position);
      successors.front().moveZero(PuzzlePosition::Up);
      successors.front().setPreviousPosition(temporaryIterator);
      successors.front().calculateHeuristic();
      successors.front().increaseDepth();
    }

    if (!position.zeroIsOverRightEdge(x))
    {
      successors.push_front(position);
      successors.front().moveZero(PuzzlePosition::Right);
      successors.front().setPreviousPosition(temporaryIterator);
      successors.front().calculateHeuristic();
      successors.front().increaseDepth();
    }

    if (!position.zeroIsOverLowerEdge(y))
    {
      successors.push_front(position);
      successors.front().moveZero(PuzzlePosition::Down);
      successors.front().setPreviousPosition(temporaryIterator);
      successors.front().calculateHeuristic();
      successors.front().increaseDepth();
    }

    if (!position.zeroIsOverLeftEdge(x))
    {
      successors.push_front(position);
      successors.front().moveZero(PuzzlePosition::Left);
      successors.front().setPreviousPosition(temporaryIterator);
      successors.front().calculateHeuristic();
      successors.front().increaseDepth();
    }
  }

  return successors;
}
