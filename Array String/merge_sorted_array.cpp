/**
 * @file merge_sorted_array.cpp
 * @brief LeetCode #88 - Merge Sorted Array
 * @date 11-05-2026
 * @author Beck Davis
 * 
 * You are given two integer arrays `nums1` and `nums2`, sorted in non-decreasing order, 
 * and two integers `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively.
 * 
 * Merge `nums1` and `nums2` into a single array sorted in non-decreasing order.
 * 
 * The final sorted array should not be returned by the function, but instead be stored inside the array `nums1`. 
 * To accommodate this, `nums1` has a length of `m + n`, where the first `m` elements denote the elements that should be merged, 
 * and the last `n` elements are set to 0 and should be ignored. 
 * `nums2` has a length of `n`.
 *
 * @note Constraints:
 *   -  nums1.length == m + n
 *   -  nums2.length == n
 *   -  0 <= m, n <= 200
 *   -  1 <= m + n <= 200
 *   -  -10^9 <= nums1[i], nums2[j] <= 10^9
 *   -  `nums1` and `nums2` sorted in non-decreasing order
 *
 * @note Complexity target: O(m + n) time, O(1) auxiliary space.
 *
 * @example
 *   Input:  
 *      nums1 = [1,2,3,0,0,0], m = 3
 *      nums2 = [2,5,6], n = 3
 *   Output: [**1**,**2**,2,**3**,5,6], bold numbers come from `nums1`
 *
 *   Input:  
 *      nums1 = [1], m = 1
 *      nums2 = [], n = 0
 *   Output: [1]
 * 
 *   Input:  
 *      nums1 = [0], m = 0
 *      nums2 = [1], n = 1
 *   Output: [1]
 *      Note that because m = 0, there are no elements in nums1. 
 *        The 0 is only there to ensure the merge result can fit in nums1.
 *      -> Edge case!
 * 
 * @details
 * Three-pointer approach working backward through `nums1`:
 *   `m` and `n` start at the last valid indices of `nums1` and `nums2`.
 *   `writer` starts at the last position of `nums1` (m+n-1).
 *   Each iteration writes the larger of `nums1[m]` / `nums2[n]` to `writer`,
 *   decrementing that pointer and `writer`.
 *   Loop runs while `n >= 0`; if `m` is exhausted first, remaining `nums2`
 *   elements are written directly. If `nums2` is exhausted first, remaining
 *   `nums1` elements are already in place — no work needed.
 *
 *   O(m+n) time, O(1) auxiliary space.
 *
 *   On LeetCode, this solution is accepted with:
 *      0 ms runtime (faster than 100% of submissions) and
 *      12.14 MB memory usage (less than 99.38% of submissions).
 */

#include <iostream>
#include <vector>

using namespace std;

//   +======================================================+
//   |                                                      |
//   |                      SOLUTION                        |
//   |                                                      |
//   +======================================================+

class Solution {
 public:
  void mergeSorted(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    // Note: LeetCode will ensure valid input.

    int writer = m+n-1;
    m--;
    n--;
    // Loop until nums2 is empty
    while (n >= 0) {
      // Write nums2 if larger or nums1 is exhausted
      if (m < 0 || nums2[n] > nums1[m]) {
        // write and then decrement
        nums1[writer] = nums2[n--];
      } else {
        nums1[writer] = nums1[m--]; 
      }
      // Move to next position in nums1;
      writer--;
    }
  }
};

//   +======================================================+
//   |                                                      |
//   |                        TESTS                         |
//   |                                                      |
//   +======================================================+

struct Test {
  static void run(std::string name, bool passed) {
    std::cout << name << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
  }
};

int main() {
  Solution sol;

  // Example 1: interleaved merge
  {
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};
    sol.mergeSorted(nums1, 3, nums2, 3);
    Test::run("Example 1", nums1 == vector<int>{1, 2, 2, 3, 5, 6});
  }

  // Example 2: nums2 is empty (n = 0)
  {
    vector<int> nums1 = {1};
    vector<int> nums2 = {};
    sol.mergeSorted(nums1, 1, nums2, 0);
    Test::run("Example 2 (n=0)", nums1 == vector<int>{1});
  }

  // Example 3: nums1 is empty (m = 0)
  {
    vector<int> nums1 = {0};
    vector<int> nums2 = {1};
    sol.mergeSorted(nums1, 0, nums2, 1);
    Test::run("Example 3 (m=0)", nums1 == vector<int>{1});
  }

  // Edge: all of nums2 is smaller than nums1
  {
    vector<int> nums1 = {4, 5, 6, 0, 0, 0};
    vector<int> nums2 = {1, 2, 3};
    sol.mergeSorted(nums1, 3, nums2, 3);
    Test::run("nums2 all smaller", nums1 == vector<int>{1, 2, 3, 4, 5, 6});
  }

  // Edge: all of nums2 is larger than nums1
  {
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {4, 5, 6};
    sol.mergeSorted(nums1, 3, nums2, 3);
    Test::run("nums2 all larger", nums1 == vector<int>{1, 2, 3, 4, 5, 6});
  }

  return 0;
}
