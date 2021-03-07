/*
* Puzzle.h/cpp
* Timothy Kozlov, Eric Pham
* 3/6/2021
* 
* This interface provides a set of methods that are implemented by subclasses
* and can be used by Fitness objects to evaluate the puzzle and Reproduction
* objects to mutate the puzzle. Puzzles will be instantiated using a
* PuzzleFactory singleton and stored inside a Population object.
*/

#pragma once
#include <iostream>
using namespace std;

class Puzzle
{
public:
   /*
   * This method is pure virtual and should be implemented by its subclasses.
   * It accepts an istream and reads values into the puzzle. Returns same
   * istream object.
   */
   virtual istream& readPuzzle(const istream& is) = 0;

   /*
   * This method is pure virtual and should be8 implemented by the subclass.
   * It accepts an ostream and prints the puzzle to cout with a format.
   * Returns same ostream object.
   */
   virtual ostream& writePuzzle(const ostream& os) const = 0;

   /*
   * This method will be implemented by Puzzle.cpp and will just call the
   * virtual method writePuzzle.
   */
   friend ostream& operator<<(ostream& os, const Puzzle& puzzle);

   /*
   * This method will be implemented by Puzzle.cpp and will just call the
   * virtual method readPuzzle.
   */
   friend istream& operator>>(istream& is, Puzzle& puzzle);
};

