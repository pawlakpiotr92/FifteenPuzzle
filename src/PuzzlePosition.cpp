/*
 * PuzzlePosition.cpp
 *
 *  Created on: 9 sie 2015
 *      Author: piter
 */

#include "../inc/PuzzlePosition.h"

Puzzle PuzzlePosition::puzzleBasicPosition =
{
    { 1,  2,  3,  4  },
    { 5,  6,  7,  8  },
    { 9,  10, 11, 12 },
    { 13, 14, 15, 0  }
};

PuzzlePosition::PuzzlePosition() :
    _previous(),
    _puzzle(puzzleBasicPosition),
    _heuristic(0),
    _depth(0)
{
}

PuzzlePosition::PuzzlePosition(const Puzzle& newPuzzle) :
    _previous(),
    _puzzle(newPuzzle),
    _heuristic(0),
    _depth(0)
{
}

PuzzlePosition::PuzzlePosition(const PuzzlePosition& previousPuzzle) :
    _previous(previousPuzzle._previous),
    _puzzle(previousPuzzle._puzzle),
    _heuristic(previousPuzzle._heuristic),
    _depth(previousPuzzle._depth)
{
  increaseDepth();
}

PuzzlePosition&
PuzzlePosition::operator=(const PuzzlePosition& rightHandValue)
{
  _previous = rightHandValue._previous;
  _puzzle = rightHandValue._puzzle;
  _heuristic = rightHandValue._heuristic;
  _depth = rightHandValue._depth;

  return *this;
}

void
PuzzlePosition::findZeroPosition(int& x, int& y)
{
  for (y = 0; y < 4; y++)
  {
    for (x = 0; x < 4; x++)
    {
      if (_puzzle[y][x] == 0)
      {
        return;
      }
    }
  }
}

void
PuzzlePosition::moveZero(Direction direction)
{
  switch(direction)
  {
    case Up:
      moveZeroUp();
      break;

    case Down:
      moveZeroDown();
      break;

    case Left:
      moveZeroLeft();
      break;

    case Right:
      moveZeroRight();
      break;
  }
}

void
PuzzlePosition::moveZeroUp()
{
  int x, y;
  findZeroPosition(x, y);
  if (!zeroIsOverUpperEdge(y))
  {
    _puzzle[y][x] = _puzzle[y - 1][x];
    _puzzle[y - 1][x] = 0;
  }
}

void
PuzzlePosition::moveZeroDown()
{
  int x, y;
  findZeroPosition(x, y);
  if (!zeroIsOverLowerEdge(y))
  {
    findZeroPosition(x, y);
    _puzzle[y][x] = _puzzle[y + 1][x];
    _puzzle[y + 1][x] = 0;
  }
}

void
PuzzlePosition::moveZeroLeft()
{
  int x, y;
  findZeroPosition(x, y);
  if (!zeroIsOverLeftEdge(x))
  {
    findZeroPosition(x, y);
    _puzzle[y][x] = _puzzle[y][x - 1];
    _puzzle[y][x - 1] = 0;
  }
}

void
PuzzlePosition::moveZeroRight()
{
  int x, y;
  findZeroPosition(x, y);
  if (!zeroIsOverRightEdge(x))
  {
    _puzzle[y][x] = _puzzle[y][x + 1];
    _puzzle[y][x + 1] = 0;
  }
}

void
PuzzlePosition::calculateHeuristic() const
{
  _heuristic = 0;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (_puzzle[i][j] != 0)
      {
        _heuristic += abs(((int(_puzzle[i][j]) - 1) / 4) - i)
                   +  abs(((int(_puzzle[i][j]) - 1) % 4) - j);
      }
    }
  }
}

ostream&
operator<<(ostream& output, const PuzzlePosition& puzzleToPrint)
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      output << puzzleToPrint._puzzle[i][j] << '\t';
    }
    output << endl;
  }

  return output;
}
