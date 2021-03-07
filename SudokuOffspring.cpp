/*
* SudokuOffspring.h/cpp
* Timothy Kozlov, Eric Pham
* 3/7/2021
*
* This class implements the Reproduction interface. It follows the singleton
* pattern and is used to mutate any Sudoku puzzles passed in.
*/

#include "SudokuOffspring.h"
#include "Sudoku.h"

const int MUTATION_PERCENT = 100;

/*
* This singleton method returns the current instance of the class. Inside
* the method, it just declares a static SudokuOffspring object and then
* returns it.
*/
SudokuOffspring& SudokuOffspring::getInstance() {
   // Create a static instance
   static SudokuOffspring instance;

   // Return it
   return instance;
}

/*
* This method accepts a Puzzle object, casts it to a Sudoku, clones it using
* a copy constructor, and then randomly changes 5% of the cells to a different
* number 1-9. Then, it returns the cloned object.
*/
Puzzle* SudokuOffspring::makeOffspring(const Puzzle& puzzle) const {
   // Case puzzle to a sudoku
   Sudoku* sudoku = (Sudoku*)&puzzle;

   // Clone it using a copy constructor
   Sudoku* copy = new Sudoku(*sudoku);

   // 5% chance to change the cells to a different number 1-9
   // Invariant: 0 < row < sudoku.data.length
   for (int row = 0; row < 9; row++) {
      // Invariant: 0 < col <= sudoku.data[row].length
      for (int col = 0; col < 9; col++) {
         // Random number from 0-99
         int chance = rand() % 100;
         // Check if the number is <= 5 (5 percent chance)
         if (chance <= MUTATION_PERCENT) {
            // Try to change cell to random digit. If it's locked, it wont work.
            int randDigit = rand() % 9 + 1;
            copy->setDigitAt(row, col, randDigit);
         }
      }
   }

   // Return copy
   return copy;
}