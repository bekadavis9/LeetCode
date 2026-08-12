/**
 * @file remove_duplicates.cpp
 * @brief LeetCode #26 - Remove Duplicates from Sorted Array
 * @date 08-11-2026
 * @author Beck Davis
 *
 * Given an integer array `nums` sorted in non-decreasing order, remove the
 * duplicates in-place such that each unique element appears only once. The
 * relative order of the elements should be kept the same. Return the number
 * of unique elements in `nums`.
 *
 * Consider the number of unique elements to be `k`. You must:
 *   - Modify `nums` such that the first `k` elements contain the unique
 *     elements in their original order.
 *   - The remaining elements and size of `nums` do not matter.
 *   - Return `k`.
 *
 * @note Constraints:
 *   - 1 <= nums.length <= 3 * 10^4
 *   - -100 <= nums[i] <= 100
 *   - nums is sorted in non-decreasing order
 *
 * @note Complexity target: O(n) time, O(1) auxiliary space.
 *
 * @example
 *   Input:  nums = [1, 1, 2]
 *   Output: k = 2, nums = [1, 2, _]
 *
 *   Input:  nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
 *   Output: k = 5, nums = [0, 1, 2, 3, 4, _, _, _, _, _]
 * 
 * @details 
 * Two-pointer approach: 
 *   `left` is the write pointer, starting at 1 since the first element is 
 *   always unique. `right` scans forward, and whenever it finds a value different 
 *   from `nums[left - 1]` (the last confirmed unique element), 
 *   writes it to `nums[left]` and advances `left`.
 *   
 *   Single pass: O(n) time, O(1) auxiliary space.
 * 
 *   On LeetCode, this solution is accepted with:
 *      0 ms runtime (faster than 100% of submissions) and 
 *      22.68 MB memory usage (less than 53.56% of submissions).
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
  int removeDuplicates(vector<int>& nums) {
    int nums_size = static_cast<int>(nums.size());
    if (nums_size == 1) {
      return nums_size;
    }
    

    // Use 2 pointers to traverse the array. Both start at index 1. 
    // The array is sorted and non-empty, so the first element is always unique.
    // The left pointer (writer) tracks the index of the last unique element found,
    // while the right pointer (reader) scans for the next unique element.
    int left = 1;
    for (int right = 1; right < nums_size; right++) {
      // If the current element is different from the last unique element,
      // it is a new unique element. Move it to the position after the last unique element
      if (nums[right] != nums[left - 1]) {
        nums[left] = nums[right];
        left++;
      }

    }
    // left is the count of unique elements and the first invalid index.
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
  vector<int> nums1 = {1, 1, 2};
  Test::run("Example 1", sol.removeDuplicates(nums1) == 2);

  // Example 2
  vector<int> nums2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
  Test::run("Example 2", sol.removeDuplicates(nums2) == 5);

  // Fail: Empty array not allowed by constraints
  vector<int> nums3 = {};
  Test::run("Empty array not allowed", sol.removeDuplicates(nums3) != 0);

  // Single-element array
  vector<int> nums4 = {42};
  Test::run("Single-element array", sol.removeDuplicates(nums4) == 1);

  // All duplicates
  vector<int> nums5 = {7, 7, 7, 7, 7};
  Test::run("All duplicates", sol.removeDuplicates(nums5) == 1);

  // No duplicates
  vector<int> nums6 = {1, 2, 3, 4, 5};
  Test::run("No duplicates", sol.removeDuplicates(nums6) == 5);

  return 0;
}
