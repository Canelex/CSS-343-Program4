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

   // Allocate size for array
   size_ = size;
   maxSize_ = size;
   puzzles_ = new Sudoku*[size];

   // Create size random versions of original
   for (int i = 0; i < size; i++) {
      // Copy and fill sudoku with random solution
      Sudoku* copy = (Sudoku*)factory.fillPuzzle(original);
      // Add it to the generation
      puzzles_[i] = copy;
   }
}

/*
* The destructor will loop through each puzzle in the puzzles_ vector
* and deallocate it. This wasn't originally necessary but since now
* the program uses dynamic allocation, now it is.
*/
SudokuPopulation::~SudokuPopulation() {
   // Deallocate each pointer
   for (int i = 0; i < size_; i++) {
      //cout << "Deallocated a puzzle" << endl;
      delete puzzles_[i];
   }

   delete[] puzzles_;
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

   if (percent > 1) {
      throw runtime_error("Trying to cull more puzzles than there are.");
   }

   // Create a dynamic array of fitness scores
   int* scores = new int[size_];
   for (int i = 0; i < size_; i++) {
      scores[i] = fitness.howFit(*puzzles_[i]);
   }

   // Calculate size after culling
   int newSize = int(ceil(size_ * (1 - percent)));

   // Delete scores with highest fitness
   for (int i = 0; i < newSize; i++) {
      
      // Find the index with the lowest fitness score
      int bestIndex = i;
      for (int j = i + 1; j < size_; j++) {
         if (scores[j] < scores[bestIndex]) {
            bestIndex = j;
         }
      }

      // Swap index i with best index in rest of array
      Sudoku* tempPz = puzzles_[i];
      puzzles_[i] = puzzles_[bestIndex];
      puzzles_[bestIndex] = tempPz;

      // Update parallel array scores
      int tempScore = scores[i];
      scores[i] = scores[bestIndex];
      scores[bestIndex] = tempScore;
   }

   // Clear rest of array
   for (int i = newSize; i < size_; i++) {
      delete puzzles_[i];
      puzzles_[i] = nullptr;
   }

   // Update size_ to newsize
   size_ = newSize;

   // deallocate dynamic array
   delete[] scores;

   /*cout << "after cull:" << endl;
   for (int i = 0; i < maxSize_; i++) {
      cout << (puzzles_[i] != nullptr ? fitness.howFit(*puzzles_[i]) : -1) << " ";
   }
   cout << endl;*/
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

   // This variable keeps track of puzzle we are cloning
   int j = 0;

   for (int i = size_; i < maxSize_; i++) {
      // Create a new puzzle using one at j
      Sudoku* copy = (Sudoku*) creations.createPuzzle(*puzzles_[j]);
      puzzles_[i] = copy;

      // If j moves out of bounds (previous generation portion at start
      // of array), set it back to zero.
      j++;
      if (j >= size_) {
         j = 0;
      }
   }

   // Set size back to max size
   size_ = maxSize_;

   /*SudokuFitness fitness = fitness.getInstance();
   cout << "after newgen:" << endl;
   for (int i = 0; i < maxSize_; i++) {
      cout << (puzzles_[i] != nullptr ? fitness.howFit(*puzzles_[i]) : -1) << " ";
   }
   cout << endl;*/
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
   if (size_ <= 0) {
      throw runtime_error("Tried to get best puzzle in empty population");
   }

   // Get SudokuFitness singleton
   SudokuFitness fitness = fitness.getInstance();

   // Int to keep track of best score.
   int bestScore = -1;
   int bestIndex = -1;

   // Use a for loop to calculate best score
   for (int i = 0; i < size_; i++) {
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
