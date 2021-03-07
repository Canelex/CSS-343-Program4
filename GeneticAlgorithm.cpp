#include <iostream>
#include "Sudoku.h"

using namespace std;


int main() {
   Sudoku sudoku;

   cout << "Starting program" << endl;

   cout << "Input a sudoku puzzle:";

   cin >> sudoku;

   cout << "Here is your sudoku:" << endl;
   cout << sudoku;
}