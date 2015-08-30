/*
 * PuzzlePosition.h
 *
 *  Created on: 9 sie 2015
 *      Author: piter
 */

#ifndef PUZZLEPOSITION_H_
#define PUZZLEPOSITION_H_

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class PuzzlePosition;

typedef vector<vector<short int>> Puzzle;
typedef list<PuzzlePosition>::iterator it;

class PuzzlePosition
{
  public:
    static Puzzle puzzleBasicPosition;

    enum Direction
    {
      Up,
      Down,
      Left,
      Right
    };

    PuzzlePosition();
    explicit PuzzlePosition(const Puzzle& firstPuzzle);
    PuzzlePosition(const PuzzlePosition& previousPuzzle);

    void findZeroPosition(int& x, int& y);
    void moveZero(Direction direction);
    void calculateHeuristic() const;

    PuzzlePosition&
    operator=(const PuzzlePosition& rightHandValue);

    inline bool
    operator==(const PuzzlePosition& rightHandValue)
    {
      return _puzzle == rightHandValue._puzzle;
    }

    inline bool
    operator!=(const PuzzlePosition& rightHandValue)
    {
      return _puzzle != rightHandValue._puzzle;
    }

    inline bool
    operator==(const Puzzle& rightHandValue)
    {
      return _puzzle == rightHandValue;
    }

    inline bool
    zeroIsOverUpperEdge(const int& y)
    {
      return y == 0;
    }

    inline bool
    zeroIsOverLowerEdge(const int& y)
    {
      return y == 3;
    }

    inline bool
    zeroIsOverLeftEdge(const int& x)
    {
      return x == 0;
    }

    inline bool
    zeroIsOverRightEdge(const int& x)
    {
      return x == 3;
    }

    inline bool
    isFinalNode()
    {
      return _puzzle == puzzleBasicPosition;
    }

    inline const Puzzle&
    getPuzzle() const
    {
      return _puzzle;
    }

    inline const it&
    getPreviousPosition() const
    {
      return _previous;
    }

    inline void
    setPreviousPosition(const it& previous)
    {
      _previous = previous;
    }

    inline int
    getHeuristic() const
    {
      return _heuristic;
    }

    inline void
    setHeuristic(const int& heuristic)
    {
      _heuristic = heuristic;
    }

    inline int
    getDepth() const
    {
      return _depth;
    }

    inline void
    setDepth(const int& depth)
    {
      _depth = depth;
    }

    inline void
    increaseDepth()
    {
      _depth++;
    }

    friend
    ostream& operator<<(ostream& output, const PuzzlePosition& puzzleToPrint);

  private:
    it _previous;
    Puzzle _puzzle;

    mutable int _heuristic;
    int _depth;

    void moveZeroUp();
    void moveZeroDown();
    void moveZeroLeft();
    void moveZeroRight();
};

#endif /* PUZZLEPOSITION_H_ */
