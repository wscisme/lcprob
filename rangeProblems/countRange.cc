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

inline void mergeRangeSums(long int* ibegin, int nsize, long int firsthalf) {
  int nhalf = nsize/2;
  long int* ihalf = ibegin + nhalf;
  long int* iend = ibegin + nsize;
  long int lsums[nhalf];
  for (auto it = ibegin, itemp = lsums; it != ihalf; ++it, ++itemp)
    *itemp = *it;
  for (auto it = ihalf; it != iend; ++it)
    *it += firsthalf;
  for (auto itl = lsums, ilend = lsums + nhalf, itr = ihalf, itsum = ibegin; itl != ilend; ++itsum) {
    if (*itl <= *itr) {
      *itsum = *itl;
      ++itl;
    } else {
      *itsum = *itr;
      ++itr;
    }
  }
}

int countSubarraySumInRange(vector<int>& nums, int lower, int upper, long int* sums, int j, int k) {
  if (j == k) return 0;
  int arrsize = k - j;
  if (arrsize == 1) {
    sums[j] = nums[j];
    return nums[j] >= lower && nums[j] <= upper;
  }
  int half = (j + k) / 2;
  int sum = countSubarraySumInRange(nums, lower, upper, sums, j, half) + countSubarraySumInRange(nums, lower, upper, sums, half, k);
  if (arrsize == 2) {
    int arrsum = nums[j] + nums[j+1];
    if (nums[j] > arrsum) {
      sums[j] = arrsum;
      sums[j+1] = nums[j];
    } else {
      sums[j] = nums[j];
      sums[j+1] = arrsum;
    }
    return sum + (arrsum >= lower && arrsum <= upper);
  }

  int lsize = half - j;
  int rsize = k - half;
  long int larr[lsize];
  long int* rarr = sums + half;
  long int larrsum = 0;
  for (int i = half - 1, s = 0; i >= j; --i, ++s) {
    larrsum += nums[i];
    larr[s] = -larrsum;
  }

  std::sort(larr, larr + lsize);
  long int loarr[lsize];
  long int uparr[lsize];
  for (int i = 0; i < lsize; ++i) {
    loarr[i] = lower + larr[i];
    uparr[i] = upper + larr[i];
  }

  int count = lsize * rsize;
  for (int r = 0, s = 0; r < rsize && s < lsize;) {
    if (rarr[r] < loarr[s]) {
      count -= lsize - s;
      ++r;
    } else {
      ++s;
    }
  }
  for (int r = 0, s = 0; r < rsize && s < lsize;) {
    if (uparr[s] < rarr[r]) {
      count -= rsize - r;
      ++s;
    } else {
      ++r;
    }
  }

  mergeRangeSums(sums + j, arrsize, larrsum);
  return sum + count;
}

int Solution::countRangeSum(vector<int>& nums, int lower, int upper) {
  long int sums[nums.size()];
  return countSubarraySumInRange(nums, lower, upper, sums, 0, nums.size());
}


int main()
{

  // vector<int> nums = {5, 7, 6, 1, 3};
  vector<int> nums1 = {-2, 5, -1};
  vector<int> nums2 = {-3, 1, 2, -2, 2, -1};
  // vector<int> nums = {5, 7, 4, 6, 3, 3, 4, 2};
  // vector<int> nums3 = {2147483647, -2147483648, -1, 0};
  vector<int> nums3 = {5,-23,-5,-1,-21,13,15,7,18,4,7,26,29,-7,-28,11,-20,-29,19,22,15,25,17,-13,11,-15,19,-8,3,12,-1,2,-1,-21,-10,-7,14,-12,-14,-8,-1,-30,19,-27,16,2,-15,23,6,14,23,2,-4,4,-9,-8,10,20,-29,29};

  Solution sol;
  // vector<int> result = sol.countSmaller(nums);
  // for (auto it = result.begin(); it != result.end(); ++it)
  //   cout << *it << " ";
  // cout << endl;

  cout << "The result for range sum is: " << sol.countRangeSum(nums1, -2, 2) << endl;
  cout << "The result for range sum is: " << sol.countRangeSum(nums2, -3, -1) << endl;
  cout << "The result for range sum is: " << sol.countRangeSum(nums3, -19, 10) << endl;

  return 0;
}
