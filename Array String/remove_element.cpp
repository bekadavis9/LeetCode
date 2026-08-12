/**
 * @file remove_element.cpp
 * @brief LeetCode #27 - Remove Element
 * @date 08-11-2026
 * @author Beck Davis
 *
 * Given an integer array `nums` and an integer `val`, remove all occurrences
 * of `val` in `nums` in-place. The order of the elements may be changed.
 * Return the number of elements in `nums` which are not equal to `val`.
 *
 * Consider the number of elements not equal to `val` to be `k`. You must:
 *   - Modify `nums` such that the first `k` elements contain the values not
 *     equal to `val`. The remaining elements and the size of `nums` do not
 *     matter.
 *   - Return `k`.
 *
 * @note Constraints:
 *   - 0 <= nums.length <= 100
 *   - 0 <= nums[i] <= 50
 *   - 0 <= val <= 100
 *
 * @note Complexity target: O(n) time, O(1) auxiliary space.
 * 
 * @example
 *   Input:  nums = [3, 2, 2, 3], val = 3
 *   Output: k = 2, nums = [2, 2, _, _]
 *
 *   Input:  nums = [0, 1, 2, 2, 3, 0, 4, 2], val = 2
 *   Output: k = 5, nums = [0, 1, 3, 0, 4, _, _, _]
 *
 * @details
 * Two-pointer approach: 
 *   `left` and `right` converge inward from opposite ends.
 *   When `nums[left]` equals `val`, check `nums[right]`: 
 *   if it's a valid element, overwrite `nums[left]` with it (one assignment, 
 *   not a full swap — the tail is irrelevant to the judge) and advance `left`. 
 *   Shrink `right` regardless, since that position is either `val` or has just 
 *   been consumed. When the pointers meet, `left` is the count of remaining 
 *   elements. Neither pointer reverses direction, 
 *   so total steps <= n — O(n) time, O(1) auxiliary space.
 * 
 *   On LeetCode, this solution is accepted with:
 *      0 ms runtime (faster than 100% of submissions) and 
 *      11.66 MB memory usage (less than 85.03% of submissions).
 */

#include <cassert>
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
  int removeElement(vector<int>& nums, int val) {
    // Guard required: size() returns size_t (unsigned), so 0 - 1 wraps to
    // SIZE_MAX, making right a huge number and the loop condition always true.
    if (nums.size() == 0) {
      return 0;
    }

    int left = 0;
    int right =nums.size() - 1;

    // Two pointers converge inward. Neither pointer ever reverses direction,
    // so total iterations <= n — O(n) time, O(1) auxiliary space.
    while (left <= right) {
      if (nums[left] == val) {
        if (nums[right] != val) {
          // Overwrite left with right — no need to preserve nums[right]
          // since elements past the final k index are ignored by the judge.
          // One assignment instead of a 3-step swap.
          nums[left] = nums[right];
          left++;
        }
        // Shrink the window regardless — nums[right] is either val (useless)
        // or was just consumed into left's position.
        right--;
      } else {
        left++;
      }
    }

    // left is the count of non-val elements and the first invalid index.
    return left;
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
  
  // Example 1
  vector<int> nums1 = {3, 2, 2, 3};
  int k1 = sol.removeElement(nums1, 3);
  Test::run("Example 1", k1 == 2);

  // Example 2
  vector<int> nums2 = {0, 1, 2, 2, 3, 0, 4, 2};
  int k2 = sol.removeElement(nums2, 2);
  Test::run("Example 2", k2 == 5);

  // Empty vector
  vector<int> nums3 = {};
  int k3 = sol.removeElement(nums3, 1);
  Test::run("Empty vector", k3 == 0);

  // All elements are val
  vector<int> nums4 = {1, 1, 1, 1};
  int k4 = sol.removeElement(nums4, 1);
  Test::run("All elements are val", k4 == 0);

  // Val not in vector
  vector<int> nums5 = {1, 2, 3, 4};
  int k5 = sol.removeElement(nums5, 5);
  Test::run("Val not in vector", k5 == (int)nums5.size());

  return 0;
}