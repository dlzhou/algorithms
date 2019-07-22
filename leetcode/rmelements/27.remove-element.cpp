/*
 * [27] Remove Element
 *
 * https://leetcode.com/problems/remove-element/description/
 *
 * algorithms
 * Easy (44.85%)
 * Total Accepted:    426.1K
 * Total Submissions: 950K
 * Testcase Example:  '[3,2,2,3]\n3'
 *
 * Given an array nums and a value val, remove all instances of that value
 * in-place and return the new length.
 *
 * Do not allocate extra space for another array, you must do this by modifying
 * the input array in-place with O(1) extra memory.
 *
 * The order of elements can be changed. It doesn't matter what you leave
 * beyond the new length.
 *
 * Example 1:
 *
 *
 * Given nums = [3,2,2,3], val = 3,
 *
 * Your function should return length = 2, with the first two elements of nums
 * being 2.
 *
 * It doesn't matter what you leave beyond the returned length.
 *
 *
 * Example 2:
 *
 *
 * Given nums = [0,1,2,2,3,0,4,2], val = 2,
 *
 * Your function should return length = 5, with the first five elements of nums
 * containing 0, 1, 3, 0, and 4.
 *
 * Note that the order of those five elements can be arbitrary.
 *
 * It doesn't matter what values are set beyond the returned length.
 *
 * Clarification:
 *
 * Confused why the returned value is an integer but your answer is an array?
 *
 * Note that the input array is passed in by reference, which means
 * modification to the input array will be known to the caller as well.
 *
 * Internally you can think of this:
 *
 *
 * // nums is passed in by reference. (i.e., without making a copy)
 * int len = removeElement(nums, val);
 *
 * // any modification to nums in your function would be known by the caller.
 * // using the length returned by your function, it prints the first len
 * elements.
 * for (int i = 0; i < len; i++) {
 * print(nums[i]);
 * }
 *
 */
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <time.h>
#include <vector>
using namespace std;

class Solution {
public:
  int removeElement(vector<int> &nums, int val) {
    if (nums.size() == 0)
      return 0;
    int outs = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (val == nums[i])
        continue;
      nums[outs++] = nums[i];
    }
    return outs;
  }
};

#if 0
int main() {
  Solution a;
  vector<int> tests;
  while (1) {
    int test;
    cin >> test;
    if (test == 999)
      break;
    tests.push_back(test);
  }
  int val = 2;
  cin >> val;
  clock_t begin = clock();
  clock_t end;
  double elapsed_secs;
  int ret = a.removeElement(tests, val);
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Run time: " << elapsed_secs << "s" << endl;
  int i = 0;
#if 1
  while (i < ret) {
    cout << tests[i] << endl;
    i++;
  }
#endif

  return 0;
}
#endif