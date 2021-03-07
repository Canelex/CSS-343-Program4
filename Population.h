/*
* Population.h
* Timothy Kozlov, Eric Pham
* 3/6/2021
* 
* This interface provides a set of methods that should be implemented by all
* Population classes.
*/

#pragma once
#include "Puzzle.h"

class Population {
public:
   /*
   * This pure virtual method should calculate the fitness score of each puzzle
   * and then remove 100*percent% elements with the worst (largest) fitness
   * score.
   */
   virtual void cull(double percent) = 0;

   /*
   * This pure virtual method will use a PuzzleFactory to generate and save a new
   * set of puzzles based on the previous generation.
   */
   virtual void newGeneration() = 0;

   /*
   * This method uses a Fitness strategy to calculate and return the best (lowest)
   * fitness score encountered. Pure virtual method -- implemented by child class.
   */
   virtual int bestFitnes() = 0;

   /*
   * This method uses a Fitness strategy to calculate and return the puzzle with
   * the best (lowest) fitness score. Pure virtual method -- implemented by child
   * class.
   */
   virtual Puzzle bestIndividual() = 0;
};