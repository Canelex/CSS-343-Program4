/*
* SudokuPopulation.h/cpp
* Timothy Kozlov, Eric Pham
*
* This class implements the Population interface. It acts as a container
* for Sudoku puzzle objects.
*/

#include "SudokuPopulation.h"
#include "SudokuFitness.h"
#include "SudokuFactory.h"
#include <cmath>

/*
* The constructor will copy size into size_ and instantiates puzzles_
* as a new vector. Then it will use SudokuFactory#fillPuzzle to add
* several randomly-filled solutions based on original into the puzzles_
* vector.
*/
SudokuPopulation::SudokuPopulation(Sudoku original, int size) {
   // Get the SudokuFactory
   SudokuFactory factory = factory.getInstance();

   // Create size random versions of original
   for (int i = 0; i < size; i++) {
      // Copy and fill sudoku with random solution
      Sudoku* copy = (Sudoku*)factory.fillPuzzle(original);
      // Add it to the generation
      puzzles_.push_back(copy);
   }

   // Copy size
   size_ = size;
}

/*
* The destructor will loop through each puzzle in the puzzles_ vector
* and deallocate it. This wasn't originally necessary but since now
* the program uses dynamic allocation, now it is.
*/
SudokuPopulation::~SudokuPopulation() {
   // Deallocate each pointer
   for (int i = 0; i < puzzles_.size(); i++) {
      //cout << "Deallocated a puzzle" << endl;
      delete puzzles_[i];
   }

   // Clear vector
   puzzles_.clear();
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

   // Calculate how many sudokus should be removed
   int numToRemove = int(floor(size_ * percent));
   int numRemaining = puzzles_.size() - numToRemove;

   if (numToRemove >= puzzles_.size()) {
      throw runtime_error("Trying to cull more puzzles than there are.");
   }

   // Bubble sort the vector of Sudoku Puzzles by fitness value
   int tempSize = 0;

   // While the number of Sudoku puzzles to remove has not been met, sort the vector
   while (tempSize < puzzles_.size()) {
      // For the number of Sudoku puzzles, sort the vector
      for (int j = 0; j < puzzles_.size() - 1; j++) {
         if (j < 0) {
            j = 0;
         }
         if (fitness.howFit(*puzzles_[j]) < fitness.howFit(*puzzles_[j + 1])) {
            Sudoku temp = *puzzles_[j + 1];
            *puzzles_[j + 1] = *puzzles_[j];
            *puzzles_[j] = temp;
         }
      }
      tempSize++;
   }

   // Erase the number of puzzles based on highest fitness values up until the specified percentage
   puzzles_.erase(puzzles_.begin(), puzzles_.end() - numRemaining);
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
   SudokuFactory creations = creations.getInstance();
   int temp = 0;
   vector<Sudoku*> newPuzzles;
   for (int i = 0; i < size_; i++) {
      Sudoku* copy = (Sudoku*) creations.createPuzzle(*puzzles_[temp]);
      newPuzzles.push_back(copy);

      temp++;
      if (temp >= puzzles_.size()) {
         temp = 0;
      }
   }

   // Delete old puzzles
   for (int i = 0; i < puzzles_.size(); i++) {
      delete puzzles_[i];
   }

   puzzles_ = newPuzzles;
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
   return puzzles_[bestIndex];
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
      int score = fitness.howFit(*puzzles_[i]);

      // If score is better, update it
      if (bestScore == -1 || score < bestScore) {
         bestScore = score;
         bestIndex = i;
      }
   }

   // Return pair of best index and best score
   return make_pair(bestIndex, bestScore);
}
