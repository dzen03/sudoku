#include <iostream>
#include "sudoku.h"

int main()
{
  sudoku sudoku;

  std::cin >> sudoku;

  sudoku.solve();

  std::cout << sudoku;

  return 0;
}

/*
Test sample:
-1	-1	-1	8	-1	7	9	1	-1
9	-1	-1	3	4	-1	2	-1	-1
-1	-1	5	-1	-1	-1	-1	7	-1
5	9	3	7	-1	2	-1	6	4
-1	-1	1	-1	-1	-1	-1	3	8
8	7	-1	6	3	1	-1	9	2
7	4	-1	-1	-1	-1	-1	2	-1
-1	-1	-1	-1	-1	4	3	-1	-1
-1	5	2	1	7	-1	-1	-1	-1
*/
