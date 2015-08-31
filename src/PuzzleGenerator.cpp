/*
 * PuzzleGenerator.cpp
 *
 *  Created on: 23 sie 2015
 *      Author: piter
 */

#include "../inc/PuzzleGenerator.h"

PuzzleGenerator::PuzzleGenerator()
{
  // TODO Auto-generated constructor stub

}

PuzzlePosition
PuzzleGenerator::generatePuzzle(unsigned int amountOfSteps)
{
  PuzzlePosition puzzle;
  list<PuzzlePosition> movesList(1, puzzle);
  unsigned int i = 0;

  while (i < amountOfSteps)
  {
    unsigned int salt = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
    srand(salt);

    int x, y;
    puzzle.findZeroPosition(x, y);
    int randomize = rand() % 4;

    // 0 - up, 1 - down, 2 - left, 3 - right
    if (randomize == 0)
    {
      if (!puzzle.zeroIsOverUpperEdge(y))
      {
        puzzle.moveZero(PuzzlePosition::Up);
        it nodeInHistory = find(movesList.begin(),
                                movesList.end(),
                                puzzle);

        if (nodeInHistory == movesList.end())
        {
          movesList.push_front(puzzle);
          i++;
        }
        else
        {
          puzzle.moveZero(PuzzlePosition::Down);
        }
      }
    }

    else if (randomize == 1)
    {
      if (!puzzle.zeroIsOverLowerEdge(y))
      {
        puzzle.moveZero(PuzzlePosition::Down);
        it nodeInHistory = find(movesList.begin(),
                                movesList.end(),
                                puzzle);

        if (nodeInHistory == movesList.end())
        {
          movesList.push_front(puzzle);
          i++;
        }
        else
        {
          puzzle.moveZero(PuzzlePosition::Up);
        }
      }
    }

    else if (randomize == 2)
    {
      if (!puzzle.zeroIsOverLeftEdge(x))
      {
        puzzle.moveZero(PuzzlePosition::Left);
        it nodeInHistory = find(movesList.begin(),
                                movesList.end(),
                                puzzle);

        if (nodeInHistory == movesList.end())
        {
          movesList.push_front(puzzle);
          i++;
        }
        else
        {
          puzzle.moveZero(PuzzlePosition::Right);
        }
      }
    }

    else
    {
      if (!puzzle.zeroIsOverRightEdge(x))
      {
        puzzle.moveZero(PuzzlePosition::Right);
        it nodeInHistory = find(movesList.begin(),
                                movesList.end(),
                                puzzle);

        if (nodeInHistory == movesList.end())
        {
          movesList.push_front(puzzle);
          i++;
        }
        else
        {
          puzzle.moveZero(PuzzlePosition::Left);
        }
      }
    }
  }

//  for (PuzzlePosition tmp : movesList)
//  {
//    cout << tmp << endl;
//  }

  return puzzle;
}
