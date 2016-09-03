#include <iostream>
#include <vector>
#include <algorithm>

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

// This is a O(nlog^2(n)) simple solution
int countSubarraySumInRange(vector<int>& nums, int lower, int upper, int j, int k) {
  if (j == k) return 0;
  int arrsize = k - j;
  if (arrsize == 1) return nums[j] >= lower && nums[j] <= upper;
  int half = (j + k) / 2;
  int sum = countSubarraySumInRange(nums, lower, upper, j, half) + countSubarraySumInRange(nums, lower, upper, half, k);
  if (arrsize == 2) {
    int tempsum = nums[j] + nums[j+1];
    sum += (tempsum >= lower && tempsum <= upper);
    return sum;
  }

  int lsize = half - j;
  int rsize = k - half;
  long int larr[rsize];
  long int rarr[rsize];
  long int tempsum = 0;
  for (int i = half - 1, s = 0; i >= j; --i, ++s) {
    tempsum += nums[i];
    larr[s] = -tempsum;
  }
  tempsum = 0;
  for (int i = half, r = 0; i < k; ++i, ++r) {
    tempsum += nums[i];
    rarr[r] = tempsum;
  }

  std::sort(larr, larr + lsize);
  std::sort(rarr, rarr + rsize);
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

  return sum + count;
}

inline int* mergeRangeSums(int* arr1, int size1, int* arr2, int size2, int arrsum1) {
  int* array = new int[size1+size2];
  for (auto it = arr2, iend = arr2 + size2; it != iend; ++it)
    *it += arrsum1;

  auto it1 = arr1, iend1 = arr1 + size1;
  auto it2 = arr2, iend2 = arr2 + size2;
  auto ita = array;
  for (; it1 != iend1 && it2 != iend2; ++ita) {
    if (*it1 <= *it2) {
      *ita = *it1;
      ++it1;
    } else {
      *ita = *it2;
      ++it2;
    }
  }
  for (; it1 != iend1; ++it1, ++ita) *ita = *it1;
  for (; it2 != iend2; ++it2, ++ita) *ita = *it2;
  delete [] arr1;
  delete [] arr2;
  return array;
}

int countSubarraySumInRange(vector<int>::const_iterator ibegin, vector<int>::const_iterator iend, int lower, int upper, int& arrsum, int* &lsums, int* &rsums) {
  if (ibegin == iend) return 0;
  int arrsize = iend - ibegin;
  if (arrsize == 1) {
    arrsum = *ibegin;
    lsums = new int{*ibegin};
    rsums = new int{*ibegin};
    return (*lsums >= lower && *lsums <= upper);
  }
  int nhalf1 = arrsize / 2;
  int nhalf2 = arrsize - nhalf1;

  auto ihalf = ibegin + nhalf1;
  int *lsums1, *rsums1, *lsums2, *rsums2;
  int arrsum1, arrsum2;
  int sum = countSubarraySumInRange(ibegin, ihalf, lower, upper, arrsum1, lsums1, rsums1)
            + countSubarraySumInRange(ihalf, iend, lower, upper, arrsum2, lsums2, rsums2);

  arrsum = arrsum1 + arrsum2;

  int count = nhalf1 * nhalf2;

  for (int ir = 0, il = nhalf1 - 1; ir < nhalf2 && il >= 0;) {
    if ((long) rsums2[ir] + lsums1[il] < lower) {
      count -= il + 1;
      ++ir;
    } else {
      --il;
    }
  }
  for (int ir = 0, il = nhalf1 - 1; ir < nhalf2 && il >= 0;) {
    if ((long) rsums2[ir] + lsums1[il] > upper) {
      count -= nhalf2 - ir;
      --il;
    } else {
      ++ir;
    }
  }

  rsums = mergeRangeSums(rsums1, nhalf1, rsums2, nhalf2, arrsum1);
  lsums = mergeRangeSums(lsums2, nhalf2, lsums1, nhalf1, arrsum2);
  return sum + count;
}

int Solution::countRangeSum(vector<int>& nums, int lower, int upper) {
  int dummy, *dummyptr;
  return countSubarraySumInRange(nums.cbegin(), nums.cend(), lower, upper, dummy, dummyptr, dummyptr);
}


int main()
{

  // vector<int> nums = {5, 7, 6, 1, 3};
  vector<int> nums1 = {-2, 5, -1};
  // vector<int> nums2 = {-3, 1, 2, -2, 2, -1};
  // vector<int> nums = {5, 7, 4, 6, 3, 3, 4, 2};
  vector<int> nums2 = {2147483647, -2147483648, -1, 0};
  vector<int> nums3 = {5,-23,-5,-1,-21,13,15,7,18,4,7,26,29,-7,-28,11,-20,-29,19,22,15,25,17,-13,11,-15,19,-8,3,12,-1,2,-1,-21,-10,-7,14,-12,-14,-8,-1,-30,19,-27,16,2,-15,23,6,14,23,2,-4,4,-9,-8,10,20,-29,29};

  Solution sol;
  // vector<int> result = sol.countSmaller(nums);
  // for (auto it = result.begin(); it != result.end(); ++it)
  //   cout << *it << " ";
  // cout << endl;

  cout << "The result for range sum is: " << sol.countRangeSum(nums1, -2, 2) << endl;
  // cout << "The result for range sum is: " << sol.countRangeSum(nums2, -1, 0) << endl;
  cout << "The result for range sum is: " << sol.countRangeSum(nums2, -2, 0) << endl;
  cout << "The result for range sum is: " << sol.countRangeSum(nums3, -19, 10) << endl;

  return 0;
}
