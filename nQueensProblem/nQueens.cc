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
  }

  int* permute = new int[n];

  if (all_permutes.size() == 0) {
    cout << "0 possibility found." << endl;
    return solutions;
  }

  string rowtemplate(n, '.');
  for (auto it = all_permutes.begin(); it != all_permutes.end(); ++it) {
    vector<string> sol;
    for (int i = 0; i < n; ++i)
      sol.push_back(string(rowtemplate).replace(*it[i], 1, "Q"));
    solutions.push_back(sol);
  }

  return solutions;
}

bool Solution::findPermutation(int* permute, const int n, int j, int* coltaken, int* sums, int* difs) {
  if (j == 8) {
    int* goodpermute = new int[n];
    all_permutes.push_back(permute);
    return true;
  }

  //   if (coltaken & 1 << k) continue;
  //   if (sums & 1 << j << k) continue;
  //   if (difs & 1 << 7 << j >> k) continue;

  //   int coltaken_new = coltaken | 1 << k;
  //   int sums_new = sums | 1 << j << k;
  //   int difs_new = difs | 1 << 7 << j >> k;
  //   permute[j] = k;
  //   findPermutation(permute, j+1, coltaken_new, sums_new, difs_new);
  // }

  return false;
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

  return 0;
}
