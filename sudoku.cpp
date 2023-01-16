#include "sudoku.h"

bool sudoku::solve()
{
  std::vector<std::set<sudoku_type>> need_rows(DIMENSIONS);
  std::vector<std::set<sudoku_type>> need_columns(DIMENSIONS);
  std::vector<std::vector<std::set<sudoku_type>>> need_squares(DIMENSIONS / 3,
                                                               std::vector<std::set<sudoku_type>> (DIMENSIONS / 3));

  // init all sets
  for (auto& row: need_rows)
    for (sudoku_type i = 1; i <= DIMENSIONS; ++i)
      row.insert(i);
  for (auto& column: need_columns)
    for (sudoku_type i = 1; i <= DIMENSIONS; ++i)
      column.insert(i);
  for (auto& square_row: need_squares)
    for (auto& square : square_row)
      for (sudoku_type i = 1; i <= DIMENSIONS; ++i)
        square.insert(i);


  std::set<std::pair<size_t, size_t>> empty;

  for (size_t row_id = 0; row_id < DIMENSIONS; ++row_id) // preprocess - find which numbers are needed
  {
    auto row = data[row_id];
    for (size_t column_id = 0; column_id < DIMENSIONS; ++column_id)
    {
      auto item = row[column_id];
      if (item != EMPTY)
      {
        auto& need_row = need_rows[row_id];
        auto& need_column = need_columns[column_id];
        auto& need_square = need_squares[row_id / 3][column_id / 3];

        auto need_row_iter = need_rows[row_id].begin();
        auto need_column_iter = need_columns[column_id].begin();
        auto need_square_iter = need_squares[row_id / 3][column_id / 3].begin();

        if ((need_row_iter = need_row.find(item)) == need_row.end()
          || (need_column_iter = need_column.find(item)) == need_column.end()
          || (need_square_iter = need_square.find(item)) == need_square.end()) // sudoku is incorrect
          return false;

        need_row.erase(need_row_iter);
        need_column.erase(need_column_iter);
        need_square.erase(need_square_iter);
      }
      else
      {
//          if we can insert number already, we should do it. It will give small perf boost // WILL IT? //
        empty.insert(std::make_pair(row_id, column_id));
      }
    }
  }

  try_solve(empty, need_rows, need_columns, need_squares);

  return empty.empty();
}

bool sudoku::solve_easy(std::set<std::pair<size_t, size_t>>& empty, std::vector<std::set<sudoku_type>>& need_rows,
                        std::vector<std::set<sudoku_type>>& need_columns,
                        std::vector<std::vector<std::set<sudoku_type>>>& need_squares)
{
  size_t empty_size;
  do
  {
    empty_size = empty.size();

    for (auto iter = empty.begin(); iter != empty.end(); )
    {
      auto row_id = iter->first;
      auto column_id = iter->second;

      auto& need_row = need_rows[row_id];
      auto& need_column = need_columns[column_id];
      auto& need_square = need_squares[row_id / 3][column_id / 3];

      std::set<sudoku_type> need;

      for (auto item: need_row)
        if (need_column.contains(item) && need_square.contains(item))
          need.insert(item);

      if (need.size() == 1)
      {
        auto number = *need.begin();

        data[row_id][column_id] = number;

        need_row.erase(number);
        need_column.erase(number);
        need_square.erase(number);

        empty.erase(iter);
        iter = empty.begin();
      }
      else if (need.empty())
        return false;
      else
        ++iter;
    }

  } while (empty_size != empty.size());
  return true;
}

bool sudoku::try_solve(std::set<std::pair<size_t, size_t>>& empty,
                       std::vector<std::set<sudoku_type>>& need_rows,
                       std::vector<std::set<sudoku_type>>& need_columns,
                       std::vector<std::vector<std::set<sudoku_type>>>& need_squares)
                       // we can use recursion, because it's depth is limited to squared DIMENSIONS
{
  if (!solve_easy(empty, need_rows, need_columns, need_squares))
    return false;

  if (empty.empty())
    return true;

  auto row_id = empty.begin()->first;
  auto column_id = empty.begin()->second;

  auto& need_row = need_rows[row_id];
  auto& need_column = need_columns[column_id];
  auto& need_square = need_squares[row_id / 3][column_id / 3];

  std::set<sudoku_type> need;

  for (auto item: need_row)
    if (need_column.contains(item) && need_square.contains(item))
      need.insert(item);

  if (need.empty())
    return false;
  else
  {

    for (auto number: need)
    {
      auto backup_need_rows = need_rows;
      auto backup_need_columns = need_columns;
      auto backup_need_squares = need_squares;
      auto backup_empty = empty;


      data[row_id][column_id] = number;

      auto backup_sudoku = *this;


      need_row.erase(number);
      need_column.erase(number);
      need_square.erase(number);
      empty.erase(empty.begin());


      if (try_solve(empty, need_rows, need_columns, need_squares))
      {
        return true;
      }

      *this = backup_sudoku;
      need_rows = backup_need_rows;
      need_columns = backup_need_columns;
      need_squares = backup_need_squares;
      empty = backup_empty;
    }
  }
  return false;
}

std::ostream& operator<<(std::ostream& out, const sudoku& s)
{
  for (auto& row : s.data)
  {
    for (auto& item : row)
     out << (int)item << "\t";
    out << "\n";
  }
  return out;
}
std::istream& operator>>(std::istream& in, sudoku& s)
{
  int tmp;
  for (auto& row : s.data)
    for (auto& item : row)
    {
      in >> tmp;
      item = (sudoku_type)tmp;
    }
  return in;
}
