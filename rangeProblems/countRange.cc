#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  // https://leetcode.com/problems/count-of-range-sum/
  int countRangeSum(vector<int>& nums, int lower, int upper);
  // https://leetcode.com/problems/count-of-smaller-numbers-after-self/
  vector<int> countSmaller(vector<int>& nums);
};

void mergeCountSort(vector<pair<int,int>>& array, vector<int>& sol) {
  unsigned int arrsize = array.size();
  if (arrsize < 2) return;

  auto ithalf = array.begin() + arrsize/2;
  vector<pair<int,int>> halfarr1(array.begin(), ithalf);
  vector<pair<int,int>> halfarr2(ithalf, array.end());

  mergeCountSort(halfarr1, sol);
  mergeCountSort(halfarr2, sol);
  array.clear();

  for (auto it1 = halfarr1.begin(), it2 = halfarr2.begin(), iend1 = halfarr1.end(), iend2 = halfarr2.end(); ;) {
    if (it1 == iend1) {
      if (it2 == iend2) break;
      array.push_back(*it2++);
    }
    else if (it2 == iend2 || it1->first > it2->first)
      array.push_back(*it1++);
    else {
      for (auto itemp = it1; itemp != iend1; ++itemp)
        --sol[itemp->second];
      array.push_back(*it2++);
    }
  }
}

vector<int> Solution::countSmaller(vector<int>& nums) {
  const unsigned int nsize = nums.size();
  vector<int> sol(nsize);
  
  vector<pair<int,int>> val_idx_pairs;
  for (unsigned int idx = 0; idx < nsize; ++idx) {
    val_idx_pairs.push_back(make_pair(nums[idx], idx));
    sol[idx] = nsize - 1 - idx;
  }

  int i = 1;
  mergeCountSort(val_idx_pairs, sol);
  
  return sol;
}

int main()
{

  // vector<int> nums = {5, 7, 6, 1, 3};
  // vector<int> nums = {5, 2, 6, 1};
  vector<int> nums = {5, 7, 4, 6, 3, 3, 4, 2};

  Solution sol;
  vector<int> result = sol.countSmaller(nums);

  for (auto it = result.begin(); it != result.end(); ++it)
    cout << *it << " ";
  cout << endl;

  return 0;
}
