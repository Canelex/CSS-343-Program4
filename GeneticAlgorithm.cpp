#include <iostream>
#include <string>
#include "Sudoku.h"
#include "Fitness.h"
#include "SudokuFitness.h"
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
   
   try {
      cin >> sudoku;
   } catch (runtime_error err) {
      cout << "ERROR: Invalid sudoku input" << endl;
      return -1;
   }

   cout << "Processing your sudoku:" << endl;
   cout << sudoku << endl;

   // Use random seed
   srand(time(0));
   SudokuPopulation pop(sudoku, popSize);
   for (int i = 1; i <= maxGens && pop.bestFitness() != 0; i++) {
      pop.cull(0.9);
      pop.newGeneration();

      /*
      * For bigger populations, this helps the user understand how much time
      * is remaining before an output is printed.
      */
      //if (i % (maxGens / 10) == 0) {
      //   cout << "Percent done: " << (100 * i / maxGens) << "%" << endl;
      //}
   }

   cout << "Best sudoku: " << endl;
   Puzzle* best = pop.bestIndividual();
   cout << *best << endl;
   cout << "Best fitness: " << pop.bestFitness() << endl;
   //delete best; // Delete so valgrind does not yell at me.
}