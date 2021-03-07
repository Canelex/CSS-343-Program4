/*
* SudokuPopulation.h/cpp
* Timothy Kozlov, Eric Pham
*
* This class implements the Population interface. It acts as a container
* for Sudoku puzzle objects.
*/

#include "SudokuPopulation.h"
#include "SudokuFitness.h"
#include "SudokuOffspring.h"

/*
* The constructor will copy size into size_ and instantiates puzzles_
* as a new vector. Then it will use SudokuFactory#fillPuzzle to add
* several randomly-filled solutions based on original into the puzzles_
* vector.
*/
SudokuPopulation::SudokuPopulation(Sudoku original, int size) {
   // Create size random versions of original
   for (int i = 0; i < size; i++) {
      // TODO: use fillPuzzle
      SudokuOffspring repro = repro.getInstance();

      Sudoku* copy = (Sudoku*) repro.makeOffspring(original);

      // Get SudokuFitness singleton
      SudokuFitness fitness = fitness.getInstance();

      //cout << fitness.howFit(copy) << " " << endl;
      puzzles_.push_back(*copy);
   }

   // Copy size
   size_ = size;
}

/*
* This method is an implementation from the Population interface and
* will calculate the fitness score of each element in the puzzles_ vector
* using the SudokuFitness singleton and then remove the (size_ * percent)
* elements with the worst (largest) fitness score. To do this, it will
* use a for loop and vector#erase.
*/
void SudokuPopulation::cull(double percent) {
   // Get SudokuFitness singleton
   SudokuFitness fitness = fitness.getInstance();

   // TODO: remove puzzles
}

/*
* This method is an implementation from the Population interface and
* will use the SudokuFactory singleton to generate a new set of puzzles.
* Using a for loop to repeat size_ times, SudokuFactory#createPuzzle
* will be called for each puzzle in puzzles_. When we run out of puzzles
* in our vector (since size_ is greater than the vector size after culling),
* it will pick up from puzzles_[0] again. Then, it will replace the
* puzzles_ vector with the new set we generated.
*/
void SudokuPopulation::newGeneration() {
   // TODO
}

/*
* This method is an implementation from the Population interface and uses
* a loop and the SudokuFitness singleton to calculate and return the best
* (lowest) fitness score encountered.
*/
int SudokuPopulation::bestFitness() const {
   // Get the best score
   int bestScore = bestPuzzle().second;

   // Return the best fitness.
   return bestScore;
}

/*
* This method is an implementation from the Population interface and uses
* a loop and the SudokuFitness singleton to calculate and return the
* puzzle with the best (lowest) fitness score.
*/
Puzzle* SudokuPopulation::bestIndividual() const {
   // Get the best index
   int bestIndex = bestPuzzle().first;

   // Return dynamic copy of puzzle with best index (needs delete later)
   return new Sudoku(puzzles_[bestIndex]);
}

/*
* This is a helper method to reduce the amount of redundant code. It is used
* by both bestFitness and bestIndividual to calculate the puzzle with the least
* weight.
*
* Returns a pair <index in puzzles_, fitness> of the best puzzle
*/
pair<int, int> SudokuPopulation::bestPuzzle() const {
   // Check that there is at least one puzzle
   if (puzzles_.size() <= 0) {
      throw runtime_error("Tried to get best puzzle in empty population");
   }

   // Get SudokuFitness singleton
   SudokuFitness fitness = fitness.getInstance();

   // Int to keep track of best score.
   int bestScore = -1;
   int bestIndex = -1;

   // Use a for loop to calculate best score
   for (int i = 0; i < puzzles_.size(); i++) {
      // Calculate score of current puzzle
      int score = fitness.howFit(puzzles_[i]);

      // If score is better, update it
      if (bestScore == -1 || score < bestScore) {
         bestScore = score;
         bestIndex = i;
      }
   }

   // Return pair of best index and best score
   return make_pair(bestIndex, bestScore);
}