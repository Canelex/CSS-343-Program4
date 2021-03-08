#include <iostream>
#include <string>
#include "Sudoku.h"
#include "Fitness.h"
#include "SudokuFitness.h";
#include "SudokuPopulation.h"

using namespace std;


int main(int argc, char* argv[]) {
   
   // Check for argument length
   if (argc < 3) {
      cout << "ERROR: You must provide two numbers in the command line arguments" << endl;
      return -1;
   }

   int popSize, maxGens;

   // Parse two parameters
   try {
      popSize = stoi(argv[1]);
      maxGens = stoi(argv[2]);
   }
   catch (exception) {
      cout << "ERROR: Invalid arguments provided. Are you sure they are numbers?" << endl;
      return -1;
   }

   // Validate two parameters
   if (popSize < 0 || maxGens < 0) {
      cout << "ERROR: Arguments cannot be negative" << endl;
      return -1;
   }


   Sudoku sudoku;

   cout << "Starting genetic algorithm with population of " << popSize
      << " and max generations of " << maxGens << "." << endl;

   cout << "Input a sudoku puzzle:";

   cin >> sudoku;

   cout << "Processing your sudoku:" << endl;
   cout << sudoku << endl;

   SudokuPopulation pop(sudoku, 500);
   for (int i = 1; i <= 100; i++) {
      pop.cull(0.9);
      pop.newGeneration();
      if (i % 1 == 0) {
         cout << "Generation " << i << " Best Fitness: " << pop.bestFitness() << endl;
      }
      
   }

   cout << "Best sudoku: " << endl;
   Puzzle* best = pop.bestIndividual();
   cout << *best << endl;
   delete best; // Delete so valgrind does not yell at me.
}