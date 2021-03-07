/*
* Sudoku.h/cpp
* Timothy Kozlov, Eric Pham
* 3/6/2021
*
* This class implements the Puzzle interface. It represents either a solved
* or unsolved Puzzle solution. In the backend, it uses a 2d array of 81 ints
* and bools to hold the data of the sudoku board.
*/

#include "Sudoku.h"
#include <exception>
#include <string>

/*
* This is the default constructor. It represents a completely empty puzzle
* with data_ all set to 0 and fixed_ all set to false (default values)
*/
Sudoku::Sudoku() : data_{ 0 }, fixed_{ false } { }

/*
* This copy constructor copies the data_ and fixed_ arrays from another sudoku
* object. This is used by SudokuOffspring to clone and mutate.
*/
Sudoku::Sudoku(Sudoku& other) {
   // Loop invariant: 0 <= row < data_.length_
   for (int row = 0; row < 9; row++) {
      // Loop invariant: 0 <= col < data_[row].length_
      for (int col = 0; col < 9; col++) {
         // Copy values from other object.
         data_[row][col] = other.data_[row][col];
         fixed_[row][col] = other.fixed_[row][col];
      }
   }
}

/*
* This method is an implementation from the Puzzle interface. It accepts an
* input stream and fills data_ and fixed_ with data values. It reads a stream
* of 81 digits. Any digit but zero is considered “fixed” and cannot be changed
* in the future (set fixed_[i] to true).
*/
istream& Sudoku::readPuzzle(istream& is) {
   // Read input string into string
   string input;
   is >> input;

   // i => current index in string
   // row => current row in puzzle
   // col => current column in puzzle
   int i = 0, row = 0, col = 0;

   // Repeat until entire puzzle is filled
   while (row < 9 && col < 9) {
      // Check that we got enough digits
      if (i >= input.size()) {
         throw runtime_error("Invalid sudoku input passed via istream");
      }

      // Get current character from string
      char c = input[i];
      // Verify that c is a digit
      if (isdigit(c)) {
         // Parse digit from character (use ascii code of character - ascii of 0 to get actual value)
         int digit = (int)c - (int)'0';

         // Verify that digit is in correct domain
         if (digit < 0 || digit > 9) {
            throw runtime_error("Invalid domain for sudoku digit in readPuzzle");
         }

         // Write digit into puzzle
         data_[row][col] = digit;
         fixed_[row][col] = digit != 0; // Anything but zero will be fixed

         // Move column and/or row
         col++;
         if (col >= 9) {
            col = 0;
            row++;
         }
      }

      i++; // increment i by one.
   }

   return is;
}

/*
* This method is an implementation from the Puzzle interface. It prints to
* cout the current puzzle + solution using the format described in the
* specifications.
*/
ostream& Sudoku::writePuzzle(ostream& os) const {
   // Style line
   static string line = "+-------+-------+-------+";

   // Loop invariant: 0 <= row < data_.length
   for (int row = 0; row < 9; row++) {
      // Every third row, print a horizontal line
      if (row % 3 == 0) {
         os << line << endl;
      }

      // Loop invariant: 0 <= col < data_[row].length
      for (int col = 0; col < 9; col++) {
         // Every third column, print a vertical line
         if (col % 3 == 0) {
            os << "| ";
         }

         os << data_[row][col] << " ";
      }

      // Print vertical line to close right side
      os << "|" << endl;
   }
   
   // Print horizontal line to close bottom
   os << line;
   return os;
}

/*
* This method returns the digit stored at row and col in the data_.
*/
int Sudoku::getDigitAt(int row, int col) const {
   // Check bounds
   if (row < 0 || row >= 9 || col < 0 || col >= 9) {
      throw runtime_error("Invalid bounds for getDigitAt");
   }

   // Return digit at cell
   return data_[row][col];
}

/*
* This method sets the digit in the puzzle at row and col to digit as long
* as it is not fixed (check fixed_). If it is, it does nothing and returns
* false. If the change succeeds, return true.
*/
bool Sudoku::setDigitAt(int row, int col, int digit) {
   // Check bounds
   if (row < 0 || row >= 9 || col < 0 || col >= 9) {
      throw runtime_error("Invalid bounds for setDigitAt");
   }

   // Check that digit is legal
   if (digit <= 0 || digit > 9) {
      throw runtime_error("Invalid domain for sudoku digit in setDigitAt");
   }

   // Check if cell is fixed
   if (fixed_[row][col]) {
      return false; // Cannot be changed, return false
   }

   data_[row][col] = digit;
   return true;
}