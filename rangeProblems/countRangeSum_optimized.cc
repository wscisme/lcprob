#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
  // https://leetcode.com/problems/count-of-range-sum/
  int countRangeSum(vector<int>& nums, int lower, int upper);
};


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

// The O(nlogn) solution
int countSubarraySumInRange(vector<int>::const_iterator ibegin, vector<int>::const_iterator iend, int lower, int upper, int& arrsum, int* &lsums, int* &rsums) {
  if (ibegin == iend) return 0;
  int arrsize = iend - ibegin;
  if (arrsize == 1) {
    arrsum = *ibegin;
    lsums = new int{*ibegin};
    rsums = new int{*ibegin};
    return (*lsums >= lower && *lsums <= upper);
  }
  else if (arrsize == 2) {
    auto isecond = ibegin + 1;
    arrsum = *ibegin + *isecond;
    if (*ibegin < 0) lsums = new int[2]{arrsum, *isecond};
    else             lsums = new int[2]{*isecond, arrsum};
    if (*isecond < 0) rsums = new int[2]{arrsum, *ibegin};
    else              rsums = new int[2]{*ibegin, arrsum};
    
    return (*ibegin >= lower && *ibegin <= upper) + (*isecond >= lower && *isecond <= upper) + (arrsum >= lower && arrsum <= upper);
  }

  int nhalf1 = arrsize / 2;
  int nhalf2 = arrsize - nhalf1;

  auto ihalf = ibegin + nhalf1;
  int *lsums1(0), *rsums1(0), *lsums2(0), *rsums2(0);
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

  if (!rsums) {
    rsums = mergeRangeSums(rsums1, nhalf1, rsums2, nhalf2, arrsum1);
    lsums = mergeRangeSums(lsums2, nhalf2, lsums1, nhalf1, arrsum2);
  }
  return sum + count;
}

int Solution::countRangeSum(vector<int>& nums, int lower, int upper) {
  int dummy, *dummyptr = &dummy;
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

  cout << "The result for range sum is: " << sol.countRangeSum(nums1, -2, 2) << endl;
  // cout << "The result for range sum is: " << sol.countRangeSum(nums2, -1, 0) << endl;
  cout << "The result for range sum is: " << sol.countRangeSum(nums2, -2, 0) << endl;
  cout << "The result for range sum is: " << sol.countRangeSum(nums3, -19, 10) << endl;

  return 0;
}
