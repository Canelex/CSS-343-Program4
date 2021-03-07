/*
* SudokuFitness.h/cpp
* Timothy Kozlov, Eric Pham
* 3/6/2021
* 
* This class implements the Fitness interface. It follows the singleton
* pattern and is used to evaluate the “fitness” of Sudoku puzzles.
*/

#pragma once
#include "Fitness.h"
#include "Puzzle.h"

class SudokuFitness : public Fitness
{
public:
   /*
   * This singleton method returns the current instance of the class. 
   * Inside the method, it just declares a static SudokuFitness object
   * and then returns it.
   */
   static SudokuFitness& getInstance();

   /*
   * This method is an implementation from the Fitness interface and
   * return the fitness of the sudoku. First, it casts puzzle to a Sudoku
   * object;  Then, it uses loops to iterate through each row, column,
   * and 3x3 cube to find any mistakes. If any collisions are found,
   * it tallies them up and returns the number as the “weight”.
   */
   int howFit(const Puzzle& puzzle);
};

