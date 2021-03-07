/*
* PuzzleFactory.h
* Timothy Kozlov, Eric Pham
* 3/7/2021
* 
* This interface provides two methods that are useful for constructing Puzzle objects.
*/
#pragma once
#include "Puzzle.h"

class PuzzleFactory {
public:
   /*
   * This pure virtual method accepts an unsolved puzzle and then randomly solves it.
   */
   virtual Puzzle* fillPuzzle(const Puzzle& unsolved) const = 0;

   /*
   * This pure virtual method accepts a puzzle that has been solved already and then
   * uses the Reproduction#makeOffspring method to return a new, mutated puzzle.
   */
   virtual Puzzle* createPuzzle(const Puzzle& solved) const = 0;
};