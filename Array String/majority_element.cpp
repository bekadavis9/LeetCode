/**
 * @file majority_element.cpp
 * @brief LeetCode #169 - Majority Element
 * @date 11-06-2026
 * @author Beck Davis
 *
 * Given an array `nums` of size `n`, return the majority element.
 *
 * The majority element is the element that appears more than n/2 times.
 * You may assume that the majority element always exists in the array.
 *
 * @note Constraints:
 *   - n == nums.length
 *   - 1 <= n <= 5 * 10^4
 *   - -10^9 <= nums[i] <= 10^9
 *   - The majority element always exists
 *
 * @note Complexity target: O(n) time, O(1) auxiliary space.
 *
 * @example
 *   Input:  nums = [3, 2, 3]
 *   Output: 3
 *
 *   Input:  nums = [2, 2, 1, 1, 1, 2, 2]
 *   Output: 2
 *
 * @details
 * Intuition:
 *    1. try to "cancel out" each element with 2 pointers - one at each end of array
 *        - can have more than 2 different elements so the 2-pointer approach won't naturalize
 *    2. create set with element : # occurrences, return element w/ highest count
 *        - O(n) time but also O(n) space with introduction of set
 *    3. sort array and then return element w/ max occurrences
 *        - sorting costs O(n log n)
 * 
 * Notes:
 *    I was using Claude as a stand-in interviewer, describing my potential approaches and getting some feedback.
 *    Claude told me about the Boyer-Moore Voting Algorithm, which I'd never heard of. 
 *    I wanted to figure out the approach fully on my own, but I looked up the algorithm and used the description to iron out design flaws.
 *    I am allowing myself this grace in the solution because of my #1 intuition above. 
 *    I had the right idea initially but wasn't sure how exactly to implement it. I always overthink / overcomplicate things.
 * 
 * Approach:
 *    Boyer-Moore Voting Algorithm: single forward pass tracking a `candidate` and a `count`. 
 *    When `count` hits 0, the current element becomes the new `candidate`. 
 *    Each matching element increments `count`; each differing element decrements it (canceling out). 
 *    Since the majority element appears more than `n/2` times, it always survives as the final `candidate`.
 *
 * On LeetCode, this solution is accepted with:
 *    0 ms runtime (faster than 100% of submissions) and
 *    42.14 MB memory usage (less than 40.40% of submissions).
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
  int majorityElement(vector<int>& nums) {
    // Boyer-Moore Voting Algorithm approach
    // Track candidate element and count, "eliminating" differing elements

    int count = 0;
    int candidate = 0; // really None, but we don't have this concept in C++

    for (int i = 0; i < nums.size(); i++) {
      // Get current element
      int element = nums[i];
      if (count == 0) {
        // Everything is "cancelled out"; set new candidate element with count == 1
        candidate = element;
        count = 1; // could increment but this guarantees value (truly unnecessary)
      } else if (candidate == element) {
        // Another occurrence of candidate
        count++;
      } else {
        // Differing elements "cancel out"
        count--;
      }
    }

    // Ensure count > floor(n/2) 
      // Unnecessary for this problem because it's guaranteed we'll always have a majority element
    
    return candidate;
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
  {
    vector<int> nums = {3, 2, 3};
    Test::run("Example 1", sol.majorityElement(nums) == 3);
  }

  // Example 2
  {
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
    Test::run("Example 2", sol.majorityElement(nums) == 2);
  }

  // Single element
  {
    vector<int> nums = {42};
    Test::run("Single element", sol.majorityElement(nums) == 42);
  }

  // All same
  {
    vector<int> nums = {5, 5, 5, 5, 5};
    Test::run("All same", sol.majorityElement(nums) == 5);
  }

  // Majority at end
  {
    vector<int> nums = {1, 2, 3, 3, 3};
    Test::run("Majority at end", sol.majorityElement(nums) == 3);
  }

  return 0;
}
