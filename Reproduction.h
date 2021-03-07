/*
* Reproduction.h
* Timothy Kozlov, Eric Pham
* 3/6/2021
*
* This interface provides a method that is useful for mutating a puzzle.
* It has only one pure virtual method, which takes in a reference to a
* puzzle and returns a new puzzle that has been changed. The exact details
* of how this method works depends on the subclass implementing it.
*/

#pragma once
#include "Puzzle.h"

class Reproduction {
public:
   /*
   * This pure virtual method takes a reference to a puzzle and returns
   * a new puzzle that has been changed. The exact details of how this method
   * works depends on the subclass implementing it.
   */
   virtual Puzzle* makeOffspring(const Puzzle& puzzle) const = 0;
};