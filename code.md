# Code Code Code

## Combination Sum II 

```cpp


class Solution {
 public:
  std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates,
                                               int target) {
    std::sort(candidates.begin(), candidates.end());
    
    std::vector<int> current;
    searchAll(candidates, 0, target, current, 0);
    
    return std::move(answers_);
  }
  
  // Search the entire solution space for all possible sets.
  void searchAll(const std::vector<int>& sorted, std::size_t start, int target,
                 std::vector<int>& current, int sum_so_far) {
    if (sum_so_far > target) {
      return;
    }
    if (sum_so_far == target) {
      answers_.emplace_back(current);
      return;
    }
    // The '<' case.
    // Iterate through our candidates, choose one, and recurse.
    for (std::size_t i = start; i < sorted.size(); ++i) {
      // DEDUP
      if (i > start && sorted[i] == sorted[i - 1]) { continue; }
      current.emplace_back(sorted[i]);
      searchAll(sorted, i + 1, target, current, sum_so_far + sorted[i]);
      current.pop_back();
    }
  }
  
 private:
  // All found answers so far.
  std::vector<std::vector<int>> answers_;
};
```

## Combination Sum 

Note the dedup part.

```cpp
class Solution {
 public:
  std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates,
                                               int target) {
    std::sort(candidates.begin(), candidates.end());
    
    std::vector<int> current;
    searchAll(candidates, target, current, 0);
    
    return std::move(answers_);
  }
  
  // Search the entire solution space for all possible sets.
  void searchAll(const std::vector<int>& sorted, int target,
                 std::vector<int>& current, int sum_so_far) {
    if (sum_so_far > target) {
      return;
    }
    if (sum_so_far == target) {
      answers_.emplace_back(current);
      return;
    }
    // The '<' case.
    // Iterate through our candidates, choose one, and recurse.
    int prev = -1;  // The number we last considered.
    for (const auto& n : sorted) {
      bool eligible = (current.empty() || n >= current.back()) &&
                      (prev < 0 || n != prev);
      if (eligible) {
        current.emplace_back(n);
        searchAll(sorted, target, current, sum_so_far + n);
        current.pop_back();
        prev = n;
      }
    }
  }
  
 private:
  // All found answers so far.
  std::vector<std::vector<int>> answers_;
};
```

## Count and Say

```cpp
class Solution {
 public:
  static constexpr char* START = "1";
  
  std::string toNext(const std::string& s) {
    std::string result;
    for (std::size_t count = 1, i = 1; i <= s.length(); ++i) {
      if (i == s.length() || s[i] != s[i - 1]) {
        result.append(std::to_string(count));
        result.append(1, s[i - 1]);
        count = 1;
      } else {
        ++count;
      }
    }
    return result;
  }
  
  std::string countAndSay(int n) {
    std::string s(START);
    while (--n) s = toNext(s);
    return s;
  }
};
```

## Sudoku Solver 

```cpp
class Solution {
 public:
  using SudokuBoard = std::vector<std::vector<char>>;
        
  static constexpr int N = 9;
  static constexpr char EMPTY = '.';
  
  Solution() {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        rows_[i][j] = columns_[i][j] = grids_[i][j] = false;
      }
    }
  }
  
  // Which row a cell (i, j) is in.
  int getRow(int i, int j) {
    return i;
  }
  
  // Which column a cell (i, j) is in.
  int getColumn(int i, int j) {
    return j;
  }
  
  // Which grid a cell (i, j) is in.
  int getGrid(int i, int j) {
    return i / 3 * 3 + j / 3;
  }
  
  // Whether we can choose 'd' for position (i, j).
  bool canChoose(int i, int j, char d) {
    int n = d - '0' - 1;
    int r = getRow(i, j), c = getColumn(i, j), g = getGrid(i, j);
    return !rows_[r][n] && !columns_[c][n] && !grids_[g][n];
  }
  
  void choose(SudokuBoard& board, int i, int j, char d) {
    board[i][j] = d;
    int n = d - '0' - 1;
    int r = getRow(i, j), c = getColumn(i, j), g = getGrid(i, j);
    rows_[r][n] = columns_[c][n] = grids_[g][n] = true;
  }
  
  void drop(SudokuBoard& board, int i, int j, char d) {
    board[i][j] = EMPTY;
    int n = d - '0' - 1;
    int r = getRow(i, j), c = getColumn(i, j), g = getGrid(i, j);
    rows_[r][n] = columns_[c][n] = grids_[g][n] = false;
  }
  
  bool solve(SudokuBoard& board, int x, int y) {
    if (x >= N) {
      std::cout << "All open slots have been filled! Yay!!!" << std::endl;
      return true;
    }
    
    int next_x = x + (y + 1) / N, next_y = (y + 1) % N;
    
    if (board[x][y] != EMPTY) {
      return solve(board, next_x, next_y);
    }
    
    // We have 9 options. Try each.
    for (char d = '1'; d <= '9'; ++d) {
      if (canChoose(x, y, d)) {
        choose(board, x, y, d);
        if (solve(board, next_x, next_y)) return true;
        drop(board, x, y, d);
      }
    }
    
    return false;
  }
  
  bool loadFrom(SudokuBoard& board) {
    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        if (board[i][j] == '.') { continue; }
        if (!canChoose(i, j, board[i][j])) { return false; }
        choose(board, i, j, board[i][j]);
      }
    }
    return true;
  } 
  
  void solveSudoku(SudokuBoard& board) {
    assert(loadFrom(board));
    assert(solve(board, 0, 0));
  }
  
 private:
  // rows_[i][k]: whether digit 'k' exists in the ith row. Same for others.
  bool rows_[N][N];
  bool columns_[N][N];
  bool grids_[N][N];
};
```

## Valid Sudoku

Determine if a Sudoku is valid.

```cpp
class Solution {
 public:
  using SudokuBoard = std::vector<std::vector<char>>;
        
  static constexpr int N = 9;
  static constexpr char EMPTY = '.';
  
  Solution() {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        rows_[i][j] = columns_[i][j] = grids_[i][j] = false;
      }
    }
  }
  
  // Which row a cell (i, j) is in.
  int getRow(int i, int j) {
    return i;
  }
  
  // Which column a cell (i, j) is in.
  int getColumn(int i, int j) {
    return j;
  }
  
  // Which grid a cell (i, j) is in.
  int getGrid(int i, int j) {
    return i / 3 * 3 + j / 3;
  }
  
  // Whether we can choose 'd' for position (i, j).
  bool canChoose(int i, int j, char d) {
    int n = d - '0' - 1;
    int r = getRow(i, j), c = getColumn(i, j), g = getGrid(i, j);
    return !rows_[r][n] && !columns_[c][n] && !grids_[g][n];
  }
  
  void choose(SudokuBoard& board, int i, int j, char d) {
    board[i][j] = d;
    int n = d - '0' - 1;
    int r = getRow(i, j), c = getColumn(i, j), g = getGrid(i, j);
    rows_[r][n] = columns_[c][n] = grids_[g][n] = true;
  }
  
  void drop(SudokuBoard& board, int i, int j, char d) {
    board[i][j] = EMPTY;
    int n = d - '0' - 1;
    int r = getRow(i, j), c = getColumn(i, j), g = getGrid(i, j);
    rows_[r][n] = columns_[c][n] = grids_[g][n] = false;
  }
  
  bool solve(SudokuBoard& board, int x, int y) {
    if (x >= N) {
      std::cout << "All open slots have been filled! Yay!!!" << std::endl;
      return true;
    }
    
    int next_x = x + (y + 1) / N, next_y = (y + 1) % N;
    
    if (board[x][y] != EMPTY) {
      return solve(board, next_x, next_y);
    }
    
    // We have 9 options. Try each.
    for (char d = '1'; d <= '9'; ++d) {
      if (canChoose(x, y, d)) {
        choose(board, x, y, d);
        if (solve(board, next_x, next_y)) return true;
        drop(board, x, y, d);
      }
    }
    
    return false;
  }
  
  bool loadFrom(SudokuBoard& board) {
    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        if (board[i][j] == '.') { continue; }
        if (!canChoose(i, j, board[i][j])) { return false; }
        choose(board, i, j, board[i][j]);
      }
    }
    return true;
  } 
  
  void solveSudoku(SudokuBoard& board) {
    assert(loadFrom(board));
    assert(solve(board, 0, 0));
  }
  
 private:
  // rows_[i][k]: whether digit 'k' exists in the ith row. Same for others.
  bool rows_[N][N];
  bool columns_[N][N];
  bool grids_[N][N];
};
```
