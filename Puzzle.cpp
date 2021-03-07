#include "Puzzle.h"
using namespace std;

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