/*
 * PuzzleSolverBase.cpp
 *
 *  Created on: 10 sie 2015
 *      Author: piter
 */

#include "../inc/PuzzleSolverBase.h"

PuzzleSolverBase::PuzzleSolverBase() :
    _nodeHistory(list<PuzzlePosition>()),
    _clkStart(high_resolution_clock::now()),
    _clkStop(high_resolution_clock::now()),
    _startPuzzle(PuzzlePosition::puzzleBasicPosition),
    _maxNumberOfSteps(1)
{
}

PuzzleSolverBase::PuzzleSolverBase(const Puzzle& start) :
    _nodeHistory(list<PuzzlePosition>()),
    _clkStart(high_resolution_clock::now()),
    _clkStop(high_resolution_clock::now()),
    _startPuzzle(start),
    _maxNumberOfSteps(1)
{
}

PuzzleSolverBase::~PuzzleSolverBase()
{
}

void
PuzzleSolverBase::parseFileWithPuzzle(const string& filePath)
{
  ifstream fileWithPuzzle;
  fileWithPuzzle.exceptions(ifstream::failbit);
  fileWithPuzzle.open(filePath, ifstream::in);

  string tmp;
  stringstream inputString;
  fileWithPuzzle.ignore(4, '\n');
  for (int y = 0; y < 4; y++)
  {
    getline(fileWithPuzzle, tmp);
    inputString << tmp;
    for (int x = 0; x < 4; x++)
    {
      inputString >> _startPuzzle[y][x];
    }
  }
}

void
PuzzleSolverBase::solvePuzzle()
{
  PuzzlePosition startNode = PuzzlePosition(_startPuzzle);
  startNode.setPreviousPosition(_nodeHistory.end());
  _nodeHistory.push_back(startNode);
  addToContainer(startNode);
  bool solutionWasFound = false;

  try
  {
    _clkStart = high_resolution_clock::now();
    runAlgorithm();
  }
  catch (bool e)
  {
    if (e == true)
    {
      solutionWasFound = e;
      cout << "Solution found!\nTime of search: " <<          calculateExecutionTime().count()             << " microseconds, "
                                                  << (double) calculateExecutionTime().count() / 1000.0    << " miliseconds, "
                                                  << (double) calculateExecutionTime().count() / 1000000.0 << " seconds." << endl;
      printOutSolution();
      cout << "Time of search: "                  <<          calculateExecutionTime().count()             << " microseconds, "
                                                  << (double) calculateExecutionTime().count() / 1000.0    << " miliseconds, "
                                                  << (double) calculateExecutionTime().count() / 1000000.0 << " seconds." << endl;
    }
  }
  if (!solutionWasFound)
  {
    cout << "Solution not found! Extending maximum depth to " << ++_maxNumberOfSteps << "..." << endl;
    _nodeHistory.clear();
    clearContainter();
    solvePuzzle();
  }
}
