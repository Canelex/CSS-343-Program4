/*
* Fitness.h
* Timothy Kozlov, Eric Pham
* 3/6/2021
*
* This interface provides a method that is useful for evaluating the “fitness”
* of a puzzle. It has only one pure virtual method, which takes in a reference
* to a puzzle and returns an integer representing the “fitness” of it. A fitness
* score of zero indicates a solved puzzle. The exact details of how this method
* works depends on the subclass.
*/
#pragma once
#include "Puzzle.h"

class Fitness {
public:
   /*
   * This method takes a reference to a puzzle and returns an integer representing
   * the "fitness" of it. A fitness score of zero indicates a solved puzzle. The
   * exact details of how this method works depends on the subclass.
   */
   virtual int howFit(const Puzzle& puzzle) = 0;
};