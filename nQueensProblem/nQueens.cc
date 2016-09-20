#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Solution {
 public:
  // https://leetcode.com/problems/n-queens/
  vector<vector<string>> solveNQueens(int n);
  // https://leetcode.com/problems/n-queens-ii/
  int totalNQueens(int n);
};

vector<vector<string>> Solution::solveNQueens(int n) {
  vector<vector<string>> solutions;
  if (n < 4) {
    if (n < 1) cout << "Invalid value. Please input with N > 0." << endl;
    else if (n == 1) solutions.push_back(vector<string>{"Q"});
    return solutions;
  }

  int half = (n+1)/2;
  vector<int*> all_permutes;
  int permute[n];
  int sums[n];
  int difs[n];

  int row = 0;
  int col = 0;
  while (row > 0 || col < half) {
    if (col == n) {
      --row;
      if (row < 0) break;
      col = permute[row] + 1;
      continue;
    }
    int sum = row + col;
    int dif = row - col;
    bool trynext = false;
    for (int j = 0; j < row; ++j) {
      trynext = (permute[j] == col || (sums[j] == sum) || (difs[j] == dif));
      if (trynext) break;
    }
    if (trynext) { ++col; continue; }

    permute[row] = col;
    sums[row] = sum;
    difs[row] = dif;
    ++row;
    col = 0;

    if (row == n) {
      int* goodpermute = new int[n];
      for (int k = 0; k < n; ++k) goodpermute[k] = permute[k];
      all_permutes.push_back(goodpermute);
      row -= 2;
      col = permute[row] + 1;
    }
  }

  string rowtemplate(n, '.');
  for (auto it = all_permutes.begin(); it != all_permutes.end(); ++it) {
    vector<string> sol;
    for (int i = 0; i < n; ++i)
      sol.push_back(string(rowtemplate).replace((*it)[i], 1, "Q"));
    solutions.push_back(sol);
  }

  for (auto it = all_permutes.rbegin(); it != all_permutes.rend(); ++it) {
    vector<string> sol;
    if (n%2 && (*it)[0] == half - 1) continue;
    for (int i = 0; i < n; ++i)
      sol.push_back(string(rowtemplate).replace((n - 1 - (*it)[i]), 1, "Q"));
    solutions.push_back(sol);
  }

  return solutions;
}

int Solution::totalNQueens(int n) {
  if (n < 4) {
    if (n < 1) cout << "Invalid value. Please input with N > 0." << endl;
    else if (n == 1) return 1;
    return 0;
  }

  bool isOdd = n%2;
  int half = (n+1)/2;
  int solution{0};
  int duplicate{0};
  int permute[n];
  int sums[n];
  int difs[n];

  int row = 0;
  int col = 0;
  while (row > 0 || col < half) {
    if (col == n) {
      --row;
      if (row < 0) break;
      col = permute[row] + 1;
      continue;
    }
    int sum = row + col;
    int dif = row - col;
    bool trynext = false;
    for (int j = 0; j < row; ++j) {
      trynext = (permute[j] == col || (sums[j] == sum) || (difs[j] == dif));
      if (trynext) break;
    }
    if (trynext) { ++col; continue; }

    permute[row] = col;
    sums[row] = sum;
    difs[row] = dif;
    ++row;
    col = 0;

    if (row == n) {
      solution++;
      if (isOdd && permute[0] == half - 1)
        duplicate++;
      row -= 2;
      col = permute[row] + 1;
    }
  }

  solution = solution + solution - duplicate;

  return solution;
}

int main()
{
  int permute[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  int coltaken{0};
  int sums{0};
  int difs{0};

  Solution s;
  vector<vector<string>> solution;
  for (int n = 0; n < 7; ++n) {
    solution = s.solveNQueens(n);
    cout << "The total posibilities for n = " << n << " is: " << solution.size() << endl;
    cout << "and the number only program says: " << s.totalNQueens(n) << endl;
    // for (auto it = solution.begin(); it != solution.end(); ++it) {
    //   for (int i = 0; i < n; ++i) cout << (*it)[i] << endl;
    //   cout << "------------------\n";
    // }
  }

  return 0;
}
