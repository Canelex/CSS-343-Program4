/*
* SudokuFactory.h/cpp
* Timothy Kozlov, Eric Pham
* 3/7/2021
* 
* This class implements the PuzzleFactory interface. It has two methods,
* which are used for either filling an unsolved Sudoku puzzle randomly
* or mutating a solved puzzle by 5%
*/

#pragma once
#include "PuzzleFactory.h"

class SudokuFactory : public PuzzleFactory
{
public:
   /*
   * This singleton method returns the current instance of the class.
   * Inside the method, it just declares a static SudokuFactory object
   * and then returns it.
   */
   static SudokuFactory& getInstance();

   /*
   * This method is implemented from the PuzzleFactory interface. It
   * accepts a puzzle, casts it to a Sudoku, clones it, and then randomly
   * solves the clone using Sudoku#setDigitAt on every single cell.
   * Finally, it returns the new puzzle
   */
   Puzzle* fillPuzzle(const Puzzle& unsolved) const;

   /*
   * This pure virtual method accepts a puzzle and then uses the
   * SudokuOffspring#makeOffspring method to return a new, mutated
   * sudoku puzzle.
   */
   Puzzle* createPuzzle(const Puzzle& solved) const;
};

