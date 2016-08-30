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

  int count = 0;
  for (auto it1 = halfarr1.begin(), it2 = halfarr2.begin(), iend1 = halfarr1.end(), iend2 = halfarr2.end(); ;) {
    if (it1 == iend1) {
      if (it2 == iend2) break;
      array.push_back(*it2++);
    } else if (it2 == iend2 || it1->first > it2->first) {
      sol[it1->second] -= count;
      array.push_back(*it1++);
    } else {
      ++count;
      array.push_back(*it2++);
    }
  }
}

/*
void mergeCountSort2(int idxarr[], int lo, int hi, vector<int>& nums, vector<int>& sol) {
  int arrsize = hi - lo;
  if (arrsize < 2) return;

  int half = arrsize/2;
  mergeCountSort2(idxarr, lo, half, nums, sol);
  mergeCountSort2(idxarr, half, hi, nums, sol);

  // for (auto it1 = halfarr1.begin(), it2 = halfarr2.begin(), iend1 = halfarr1.end(), iend2 = halfarr2.end(); ;) {
  for (int i = lo, j = half; ;) {
    if (i == half) {
      if (j == hi) break;
    }
  }
}
*/

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

inline void mergeSortCountRangeSum(int larr[], int rarr[], int arrsize) {

}

int countRangeSum(vector<int>& nums, int lower, int upper, int i, int k) {
  if (i == k) return 0;
  int arrsize = k - i;
  if (arrsize == 1) return nums[i] >= lower && nums[i] <= upper;
  int half = (i+k)/2;
  int sum = countRangeSum(nums, lower, upper, i, half) + countRangeSum(nums, lower, upper, half, j);
  if (arrsize == 2) {
    int tempsum = nums[i] + nums[i+1];
    sum += (tempsum >= lower && tempsum <= upper);
    return sum;
  }

  int larr[half-i];
  int rarr[k-half];
  int tempsum = 0;
  for (int j = half - 1; j >= i; --j) {
    tempsum += nums[j];
    larr[j] = tempsum;
  }
  tempsum = 0;
  for (int j = half; j < k; ++j) {
    tempsum += nums[j];
    larr[j] = tempsum;
  }

  return sum;
}

int Solution::countRangeSum(vector<int>& nums, int lower, int upper) {
  int half = nums.size()/2;
  return countRangeSum(nums, lower, upper, 0, half) + countRangeSum(nums, lower, upper, half, nums.size());
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
