#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Solution {
 public:
  vector< vector<string> > solveNQueens(int n);
  bool findPermutation(int* permute, const int n, int j, int* coltaken, int* sums, int* difs);
 private:
  vector<int*> all_permutes;
  vector<int*> unique_permutes;
};

vector< vector<string> > Solution::solveNQueens(int n) {
  vector< vector<string> > solutions;
  if (n < 1) {
    cout << "Invalid value. Please input with N > 0." << endl;
    return solutions;
  } else if (n == 1) {
    solutions.push_back(vector<string>{"Q"});
  } else if (n < 4) {
    return solutions;
  }

  int permute[n];
  int sums[n];
  int difs[n];

  int row = 0;
  int col = 0;
  while (true) {
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

  return solutions;
}

int main()
{
  int permute[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  int coltaken{0};
  int sums{0};
  int difs{0};

  Solution s;
  vector< vector<string> > solution;
  solution = s.solveNQueens(8);

  cout << "The total posibilities for n = " << 8 << " is: " << solution.size() << endl;
  for (int i = 0; i < 8; ++i) cout << solution[0][i] << endl;

  return 0;
}
