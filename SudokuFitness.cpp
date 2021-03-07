#include "SudokuFitness.h"
#include "Sudoku.h"

/*
* Sample sudokus and expected fitness counts
* 
* 528974613916238475743165982391827546274653198685491327867519234459382761132746859 => 0
* 328974613916238475743165982391827546274653198685491327867519234459382761132746859 => 3
* 328974613916238475743165982391827546274653198685491327867519234459382761132746858 => 6
* 111111111111111111111111111111111111111111111111111111111111111111111111111111111 => 216 
* (8 per row, 8 per col, 8 per cube)
*/

/*
* This singleton method returns the current instance of the class.
* Inside the method, it just declares a static SudokuFitness object
* and then returns it.
*/
SudokuFitness& SudokuFitness::getInstance() {
   // Create a static instance
   static SudokuFitness instance;

   // Return it
   return instance;
}

/*
* This method is an implementation from the Fitness interface and
* return the fitness of the sudoku. First, it casts puzzle to a Sudoku
* object;  Then, it uses loops to iterate through each row, column,
* and 3x3 cube to find any mistakes. If any collisions are found,
* it tallies them up and returns the number as the “weight”.
*/
int SudokuFitness::howFit(const Puzzle& puzzle) {
   // Case puzzle to a sudoku
   Sudoku* sudoku = (Sudoku*) &puzzle;
   
   // Integer to keep track of issues in sudoku
   int issues = 0;

   // Check for repeats in each row
   // Invariant: 0 <= row < # puzzle rows
   for (int row = 0; row < 9; row++) {
      // Array to keep track of frequency of each digit
      int freq[10] = { 0 };

      // Invariant: 0 <= col < # puzzle columns
      for (int col = 0; col < 9; col++) {
         // Get the digit of the sudoku using row and col
         int digit = sudoku->getDigitAt(row, col);
         freq[digit]++; // Use digit as index
      }

      // Loop through each digit 1-10
      for (int i = 0; i < 10; i++) {
         // If there are more than one of that digit, count as errors
         if (freq[i] > 1) {
            issues += freq[i] - 1; // 2=>1 issue, 3=>2 issues, etc.
         }
      }
      //cout << issues << " issues in row " << row << endl;
      //issues = 0;
   }

   // Check for repeats in each col
   // Invariant: 0 <= col < # puzzle cols
   for (int col = 0; col < 9; col++) {
      // Array to keep track of frequency of each digit
      int freq[10] = { 0 };

      // Invariant: 0 <= row < # puzzle rows
      for (int row = 0; row < 9; row++) {
         // Get the digit of the sudoku using row and col
         int digit = sudoku->getDigitAt(row, col);
         freq[digit]++; // Use digit as index
      }

      // Loop through each digit 1-10
      for (int i = 0; i < 10; i++) {
         // If there are more than one of that digit, count as errors
         if (freq[i] > 1) {
            issues += freq[i] - 1; // 2=>1 issue, 3=>2 issues, etc.
         }
      }
      //cout << issues << " issues in col " << col << endl;
      //issues = 0;
   }

   // Check for issues in each 3x3 cube
   // Invariant: 0 < i < 9.
   // i represents the current 3x3 cube. 0=>topleft, 1=>topmiddle, 8=>bottomright
   for (int i = 0; i < 9; i++) {
      // Array to keep track of frequency of each digit
      int freq[10] = { 0 };

      // Invariant: 0 <= row < # puzzle rows
      for (int row = 0; row < 3; row++) {
         // Invariant: 0 <= col < # puzzle cols
         for (int col = 0; col < 3; col++) {
            // Adjust row and col using i (current 3x3 cube)
            int arow = row + (i / 3) * 3;
            int acol = col + (i % 3) * 3;
            // Get the digit of the sudoku using arow and acol
            int digit = sudoku->getDigitAt(arow, acol);
            freq[digit]++; // Use digit as index
         }
      }

      // Loop through each digit 1-10
      for (int i = 0; i < 10; i++) {
         // If there are more than one of that digit, count as errors
         if (freq[i] > 1) {
            issues += freq[i] - 1; // 2=>1 issue, 3=>2 issues, etc.
         }
      }

      //cout << issues << " issues in box " << i << endl;
      //issues = 0;
   }

   return issues;
}