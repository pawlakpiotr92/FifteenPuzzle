/*
 * main.cpp
 *
 *  Created on: 10 sie 2015
 *      Author: piter
 */

#include "../inc/main.h"

int main(int argc, char* argv[])
{
  parseCommandLineArguments(argc, argv);

  return 0;
}

void parseCommandLineArguments(int argc, char* argv[])
{
  if (argc == 2)
  {
    if ((string) argv[1] == "-h" || (string) argv[1] == "--help")
    {
      helpPrintout(argv);
    }
    else
    {
      cout << "Invalid syntax." << endl;
      helpPrintout(argv);
    }
  }
  else if (argc == 3 || argc == 4)
  {
    try
    {
      if ((string) argv[1] == "--dfs")
      {
        PuzzleSolverDfs solver((string) argv[2]);
      }

      else if ((string) argv[1] == "--bfs")
      {
        PuzzleSolverBfs solver((string) argv[2]);
      }

      else if ((string) argv[1] == "--ast")
      {
        PuzzleSolverAStar solver((string) argv[2]);
      }
      
      else if ((string) argv[1] == "--gen" && argc == 4)
      {
        try
        {
          PuzzleGenerator generator;
          unsigned int stepAmount = stoi(string(argv[2]));
          PuzzlePosition puzzle = generator.generatePuzzle(stepAmount);
          
          cout << "Generated puzzle:" << endl << puzzle;
          
          if ((string) argv[3] == "--dfs")
          {
            PuzzleSolverDfs solver(puzzle.getPuzzle());
          }

          else if ((string) argv[3] == "--bfs")
          {
            PuzzleSolverBfs solver(puzzle.getPuzzle());
          }

          else if ((string) argv[3] == "--ast")
          {
            PuzzleSolverAStar solver(puzzle.getPuzzle());
          }
          
          else
          {
            ofstream puzzleFile;
            puzzleFile.exceptions(ofstream::failbit);
            puzzleFile.open((string) argv[3]);
            
            puzzleFile << "4 4" << endl << puzzle;
            puzzleFile.close();
          }
        }
        catch (invalid_argument e)
        {
          cout << "Invalid syntax." << endl;
          helpPrintout(argv);
        }
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
  cout << "Syntax: " << execName.substr(found + 1) << " [-h|--help|--dfs|--bfs|--ast|--gen] [D] [FILE|ALG]" << endl << endl
       << "This application solves fifteen-puzzle game." << endl
       << "Text file with puzzle is given as an argument." << endl
       << "DFS, BFS and A* algorithms can be chosen to solve." << endl
       << endl << "Options:" << endl
       << "  -h, --help:\tShow this help." << endl
       << "  --dfs FILE:\tSolve puzzle from FILE using DFS algorithm." << endl
       << "  --bfs FILE:\tSolve puzzle from FILE using BFS algorithm." << endl
       << "  --ast FILE:\tSolve puzzle from FILE using A*  algorithm." << endl
       << "  --gen D FILE:\tGenerate puzzle of depth D and save to FILE." << endl
       << "  --gen D ALG:\tSolve generated puzzle of depth D using chosen ALGorithm." << endl;
  exit(0);
}

void performSearchAlgorithms()
{
  const string pathToPuzzles = "/home/piter/Programowanie/SISE-PHP/sise/puzzles/";
  
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
        
        cout << "Opening " << fileName.str() << "... ";
        
        PuzzleSolverBfs bfs(filePath);
        cout << "BFS... ";;
        enhanced[fileName.str()][0] = bfs.getTimeOfExecution();
        
        PuzzleSolverDfs dfs(filePath);
        cout << "DFS... ";
        enhanced[fileName.str()][1] = dfs.getTimeOfExecution();
        
        PuzzleSolverAStar astar(filePath);
        cout << "A*..." << endl;
        enhanced[fileName.str()][2] = astar.getTimeOfExecution();
      }
      catch (ios_base::failure & e)
      {
        cout << "File not found." << endl;
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