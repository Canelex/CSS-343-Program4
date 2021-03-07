/*
* SudokuFactory.h/cpp
* Timothy Kozlov, Eric Pham
* 3/7/2021
*
* This class implements the PuzzleFactory interface. It has two methods,
* which are used for either filling an unsolved Sudoku puzzle randomly
* or mutating a solved puzzle by 5%
*/

#include "SudokuFactory.h"
#include "SudokuOffspring.h"
#include "Sudoku.h"

/*
* This singleton method returns the current instance of the class.
* Inside the method, it just declares a static SudokuFactory object
* and then returns it.
*/
SudokuFactory& SudokuFactory::getInstance() {
   // Create a static instance
   static SudokuFactory instance;

   // Return it
   return instance;
}

/*
* This method is implemented from the PuzzleFactory interface. It
* accepts a puzzle, casts it to a Sudoku, clones it, and then randomly
* solves the clone using Sudoku#setDigitAt on every single cell.
* Finally, it returns the new puzzle
*/
Puzzle* SudokuFactory::fillPuzzle(const Puzzle& unsolved) const {
   // Cast puzzle to a sudoku
   Sudoku* sudoku = (Sudoku*) &unsolved;

   // Copy the puzzle using copy constructor
   Sudoku* copy = new Sudoku(*sudoku);

   // Fill every number
   // Invariant: 0 < row < sudoku.data.length
   for (int row = 0; row < 9; row++) {
      // Invariant: 0 < col <= sudoku.data[row].length
      for (int col = 0; col < 9; col++) {
         // Check if the number is <= 5 (5 percent chance)
         // Try to change cell to random digit. If it's locked, it wont do anything.
         int randDigit = rand() % 9 + 1;
         copy->setDigitAt(row, col, randDigit);
      }
   }

   // Return the dynamically created sudoku (make sure its deleted)
   return copy;
}

/*
* This pure virtual method accepts a puzzle and then uses the
* SudokuOffspring#makeOffspring method to return a new, mutated
* sudoku puzzle.
*/
Puzzle* SudokuFactory::createPuzzle(const Puzzle& solved) const {
   // Get instance of SudokuOffspring
   SudokuOffspring repro = repro.getInstance();

   // Mutate it using SudokuOffspring
   return repro.makeOffspring(solved);
}