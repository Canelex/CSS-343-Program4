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

#include "Puzzle.h"

/*
* This method will be implemented by Puzzle.cpp and will just call the
* virtual method writePuzzle.
*/
ostream& operator<<(ostream& os, const Puzzle& puzzle) {
   puzzle.writePuzzle(os);
   return os;
}

/*
* This method will be implemented by Puzzle.cpp and will just call the
* virtual method readPuzzle.
*/
istream& operator>>(istream& is, Puzzle& puzzle) {
   puzzle.readPuzzle(is);
   return is;
}