/*
* SudokuOffspring.h/cpp
* Timothy Kozlov, Eric Pham
* 3/7/2021
* 
* This class implements the Reproduction interface. It follows the singleton
* pattern and is used to mutate any Sudoku puzzles passed in.
*/

#pragma once
#include "Reproduction.h"

class SudokuOffspring : public Reproduction
{
public:
   /*
   * This singleton method returns the current instance of the class. Inside
   * the method, it just declares a static SudokuOffspring object and then
   * returns it.
   */
   static SudokuOffspring& getInstance();

   /*
   * This method accepts a Puzzle object, casts it to a Sudoku, clones it using
   * a copy constructor, and then randomly changes 5% of the cells to a different
   * number 1-9. Then, it returns the cloned object.
   */
   Puzzle* makeOffspring(const Puzzle& puzzle) const;
};

