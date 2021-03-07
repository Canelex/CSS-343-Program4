/*
* SudokuPopulation.h/cpp
* Timothy Kozlov, Eric Pham
* 
* This class implements the Population interface. It acts as a container
* for Sudoku puzzle objects.
*/

#pragma once
#include <vector>
#include "Population.h"
#include "Sudoku.h"

class SudokuPopulation : public Population
{
public:
   /*
   * The constructor will copy size into size_ and instantiates puzzles_
   * as a new vector. Then it will use SudokuFactory#fillPuzzle to add
   * several randomly-filled solutions based on original into the puzzles_
   * vector.
   */
   SudokuPopulation(Sudoku original, int size);

   /*
   * This method is an implementation from the Population interface and
   * will calculate the fitness score of each element in the puzzles_ vector
   * using the SudokuFitness singleton and then remove the (size_ * percent)
   * elements with the worst (largest) fitness score. To do this, it will
   * use a for loop and vector#erase.
   */
   void cull(double percent);

   /*
   * This method is an implementation from the Population interface and
   * will use the SudokuFactory singleton to generate a new set of puzzles.
   * Using a for loop to repeat size_ times, SudokuFactory#createPuzzle
   * will be called for each puzzle in puzzles_. When we run out of puzzles
   * in our vector (since size_ is greater than the vector size after culling),
   * it will pick up from puzzles_[0] again. Then, it will replace the
   * puzzles_ vector with the new set we generated.
   */
   void newGeneration();

   /*
   * This method is an implementation from the Population interface and uses
   * a loop and the SudokuFitness singleton to calculate and return the best
   * (lowest) fitness score encountered.
   */
   int bestFitness() const;

   /*
   * This method uses a Fitness strategy to calculate and return the puzzle with
   * the best (lowest) fitness score. Pure virtual method -- implemented by child
   * class.
   *
   * This class dynamically allocates the Puzzle copy
   */
   Puzzle* bestIndividual() const;

private:
   /*
   * This field stores all the puzzles that are part of the current generation.
   */
   vector<Sudoku> puzzles_;

   /*
   * This field stores all the puzzles that are part of the current generation.
   */
   int size_;
};

