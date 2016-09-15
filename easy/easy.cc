#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
  // https://leetcode.com/problems/find-the-difference/
  char findTheDifference(string s, string t);
  // https://leetcode.com/problems/counting-bits/
  vector<int> countBits(int num);
  // https://leetcode.com/problems/longest-substring-without-repeating-characters/
  int lengthOfLongestSubstring(string s);
  // https://leetcode.com/problems/single-number/
  int singleNumberi(vector<int>& nums);
  // https://leetcode.com/problems/single-number-ii/
  int singleNumberii(vector<int>& nums);
  // https://leetcode.com/problems/single-number-iii/
  vector<int> singleNumberiii(vector<int>& nums);
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

int Solution::lengthOfLongestSubstring(string s) {
  int len = s.length();
  if (len < 2) return len;
  else if (len == 2) return 1 + (s[0] != s[1]);
  else if (len == 3) return 1 + (s[0] != s[1]) + (s[1] != s[2]) - ((s[0] == s[2]) && (s[0] != s[1]));

  bool taken[128];
  std::fill_n(taken, 128, 0);
  int count(0), maxcount(0);
  for (auto it1 = s.begin(), it2 = it1, iend = s.end(); it2 != iend; ++it2) {
    bool is_taken = false;
    if (taken[*it2]) {
      maxcount = max(maxcount, count);
      while (*it1 != *it2) {
        --count;
        taken[*it1] = false;
        ++it1;
      }
      ++it1;
    } else {
      ++count;
      taken[*it2] = true;
    }
  }
  maxcount = max(maxcount, count);

  return maxcount;
}

int Solution::singleNumberi(vector<int>& nums) {
  int ans{0};
  for (auto it = nums.begin(), iend = nums.end(); it != iend; ++it)
    ans ^= *it;
  return ans;
}

vector<int> Solution::singleNumberiii(vector<int>& nums) {
  int dif(0), one(1), sig(0);
  auto ibegin = nums.begin(), iend = nums.end();
  for (auto it = ibegin; it != iend; ++it) dif ^= *it;
  while (!(dif & one)) one <<= 1;
  for (auto it = ibegin; it != iend; ++it)
    if (*it & one) sig ^= *it;
  return vector<int>{sig, sig^dif};
}

int main()
{
  // string s = "abcd";
  string s = "pwwkew";
  // string t = "bacde";
  // string t = "abcabcbb";
  string t = "bpfbhmipx";
  // string t = "bpf*bhmipx*!@#%";
  Solution sol;

  // cout << sol.findTheDifference(s, t) << endl;
  // cout << (sol.countBits(5)).size() << endl;
  // cout << sol.lengthOfLongestSubstring(s) << endl;
  // cout << sol.lengthOfLongestSubstring(t) << endl;

  vector<int> nums = {1, 2, 1, 3, 2, 5};
  vector<int> rslt = sol.singleNumberiii(nums);
  cout << "The answer is: " << rslt[0] << ", " << rslt[1] << ((rslt.size() == 2)? "" : " bug!!") << endl;

  return 0;
}
