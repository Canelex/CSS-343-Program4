/*
* Sudoku.h/cpp
* Timothy Kozlov, Eric Pham
* 3/6/2021
* 
* This class implements the Puzzle interface. It represents either a solved
* or unsolved Puzzle solution. In the backend, it uses a 2d array of 81 ints
* and bools to hold the data of the sudoku board.
*/

#pragma once
#include "Puzzle.h"

class Sudoku : public Puzzle
{
public:
   /*
   * This is the default constructor. It represents a completely empty puzzle
   * with data_ all set to 0 and fixed_ all set to false (default values)
   */
   Sudoku();

   /*
   * This copy constructor copies the data_ and fixed_ arrays from another sudoku
   * object. This is used by SudokuOffspring to clone and mutate.
   */
   Sudoku(Sudoku& other);

   /*
   * This method is an implementation from the Puzzle interface. It accepts an
   * input stream and fills data_ and fixed_ with data values. It reads a stream
   * of 81 digits. Any digit but zero is considered “fixed” and cannot be changed
   * in the future (set fixed_[i] to true).
   */
   istream& readPuzzle(istream& is);

   /*
   * This method is an implementation from the Puzzle interface. It prints to 
   * cout the current puzzle + solution using the format described in the 
   * specifications.
   */
   ostream& writePuzzle(ostream& os) const;

   /*
   * This method returns the digit stored at row and col in the data_.
   */
   int getDigitAt(int row, int col) const;

   /*
   * This method sets the digit in the puzzle at row and col to digit as long
   * as it is not fixed (check fixed_). If it is, it does nothing and returns
   * false. If the change succeeds, return true.
   */
   bool setDigitAt(int row, int col, int digit);

private:
   /*
   * This variable uses a 2d matrix to keep track of the digits being stored
   * in each cell of the sudoku puzzle.
   */
   int data_[9][9];

   /*
   * This variable uses a 2d matrix to keep track of which digits are
   * interchangable. A true value represents a cell that cannot be changed; A
   * false value represents a cell that can be mutated.
   */
   bool fixed_[9][9];
};

