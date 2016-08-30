#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
  char findTheDifference(string s, string t);
  vector<int> countBits(int num);
};

char Solution::findTheDifference(string s, string t) {
  int scount[26];
  int tcount[26];
  std::fill_n(scount, 26, 0);
  std::fill_n(tcount, 26, 0);
  for (auto it = s.begin(); it != s.end(); ++it)
    ++scount[*it - 'a'];
  for (auto it = t.begin(); it != t.end(); ++it)
    ++tcount[*it - 'a'];

  for (int i = 0; i < 26; ++i)
    if (scount[i] != tcount[i])
      return 'a' + i;

  return '0';
}

vector<int> Solution::countBits(int num) {
  vector<int> sol;
  sol.push_back(0);
  int count = 1;
  for (int i = 0, j = 0; i < num; ++i, ++j) {
    sol.push_back(sol[j] + 1);
    if (j == count - 1) {
      count <<= 1;
      j = -1;
    }
  }

  return sol;
}


int main()
{
  string s = "abcd";
  string t = "bacde";
  Solution sol;

  cout << sol.findTheDifference(s, t) << endl;
  cout << (sol.countBits(5)).size() << endl;

  return 0;
}
