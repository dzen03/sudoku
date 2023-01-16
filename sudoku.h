#ifndef SUDOKU__SUDOKU_H_
#define SUDOKU__SUDOKU_H_

#include <iostream>
#include <vector>
#include <set>


#define DIMENSIONS 9
#define EMPTY (-1)

typedef int8_t sudoku_type;
class sudoku {
 private:
  bool solve_easy(std::set<std::pair<size_t, size_t>>& empty,
                  std::vector<std::set<sudoku_type>>& need_rows,
                  std::vector<std::set<sudoku_type>>& need_columns,
                  std::vector<std::vector<std::set<sudoku_type>>>& need_squares);

  bool try_solve(std::set<std::pair<size_t, size_t>>& empty,
                 std::vector<std::set<sudoku_type>>& need_rows,
                 std::vector<std::set<sudoku_type>>& need_columns,
                 std::vector<std::vector<std::set<sudoku_type>>>& need_squares);
 public:
  sudoku_type data[DIMENSIONS][DIMENSIONS]{};

  bool solve();

};

std::ostream& operator<<(std::ostream&, const sudoku&);

std::istream& operator>>(std::istream&, sudoku&);

#endif //SUDOKU__SUDOKU_H_
