/*
 * main.cpp
 *
 *  Created on: 10 sie 2015
 *      Author: piter
 */

#include "../inc/main.h"

int main(int argc, char* argv[])
{
//  parseCommandLineArguments(argc, argv);
//  PuzzleSolverDfs solver(defaultPuzzle);

//  PuzzleGenerator gen;
//  PuzzlePosition abc = gen.generatePuzzle(8);
//  //cout << endl << endl << endl;
//  //PuzzleSolverAStar solver(abc.getPuzzle());
//  {
//    PuzzleSolverBfs solver(abc.getPuzzle());
//  }
//  {
//    PuzzleSolverDfs solver(abc.getPuzzle());
//  }
//  {
//    PuzzleSolverAStar solver(abc.getPuzzle());
//  }
  
  performSearchAlgorithms();

  return 0;
}

void parseCommandLineArguments(int argc, char* argv[])
{
  if (argc == 2)
  {
    if ((string) argv[1] == "-h")
    {
      helpPrintout(argv);
    }
    else
    {
      cout << "Invalid syntax." << endl;
      helpPrintout(argv);
    }
  }
  else if (argc == 3)
  {
    try
    {
      if ((string) argv[1] == "-dfs")
      {
        PuzzleSolverDfs solver((string) argv[2]);
      }

      else if ((string) argv[1] == "-bfs")
      {
        PuzzleSolverBfs solver((string) argv[2]);
      }

      else if ((string) argv[1] == "-a*")
      {
        PuzzleSolverAStar solver((string) argv[2]);
      }

      else
      {
        cout << "Invalid syntax." << endl;
        helpPrintout(argv);
      }
    }
    catch (ios_base::failure & e)
    {
      cout << "File error " << endl
           << "Check if file path is correct and "
           << "file with puzzle has correct format";
      helpPrintout(argv);
    }
  }

  else
  {
    cout << "Invalid syntax." << endl;
    helpPrintout(argv);
  }
}

void helpPrintout(char* argv[])
{
  string execName = argv[0];
  size_t found = execName.find_last_of('/');
  cout << "Syntax: " << execName.substr(found + 1) << " [-h] | [-dfs|-bfs|-a*] FILE" << endl << endl
       << "This application solves fifteen-puzzle game." << endl
       << "Text file with puzzle is given as an argument." << endl
       << "DFS, BFS and A* algorithms can be chosen to solve." << endl
       << endl << "Options:" << endl
       << "  -h:       \tShow this help." << endl
       << "  -dfs FILE:\tSolve puzzle from FILE using DFS algorithm." << endl
       << "  -bfs FILE:\tSolve puzzle from FILE using BFS algorithm." << endl
       << "  -a*  FILE:\tSolve puzzle from FILE using A*  algorithm." << endl;
  exit(0);
}

void performSearchAlgorithms()
{
  const string pathToPuzzles = "/home/piter/Programowanie/SISE-PHP/sise/puzzles/";
//  PuzzleAndTimeMap bfsSolutions;
//  PuzzleAndTimeMap dfsSolutions;
//  PuzzleAndTimeMap aStarSolutions;
  
  PuzzleAndTimeMapEnh enhanced;
  
  for (int depth = 0; depth < 8; depth++)
  {
    for (int id = 1; ; id++)
    {
      try
      {
        stringstream fileName;
        fileName << "Deep0" << depth << "_" << setfill('0') << setw(3) << id << ".txt";
        string filePath = pathToPuzzles + fileName.str();
        
        cout << "Opening " << fileName.str() << "..." << endl;
        
        PuzzleSolverBfs bfs(filePath);
        //bfsSolutions.insert(PuzzleAndTime(fileName, solver->getTimeOfExecution()));
        enhanced[fileName.str()][0] = bfs.getTimeOfExecution();
        
        PuzzleSolverDfs dfs(filePath);
        //dfsSolutions.insert(PuzzleAndTime(fileName, solver->getTimeOfExecution()));
        enhanced[fileName.str()][1] = dfs.getTimeOfExecution();
        
        PuzzleSolverAStar astar(filePath);
        //aStarSolutions.insert(PuzzleAndTime(fileName, solver->getTimeOfExecution()));
        enhanced[fileName.str()][2] = astar.getTimeOfExecution();
      }
      catch (ios_base::failure & e)
      {
        break;
      }
    }
  }
  
  ofstream outputFile("outputFile.txt");
  outputFile << "Puzzle name\tBFS time\tDFS time\tA* time" << endl;
  for (PuzzleAndTimeEnh pair : enhanced)
  {
    outputFile << pair.first << '\t';
    for (int i = 0; i < 3; i++)
      outputFile << pair.second[i] << '\t';
    outputFile << endl;
  }
  outputFile.close();
}