/*
 * [18] 4Sum
 *
 * https://leetcode.com/problems/4sum/description/
 *
 * algorithms
 * Medium (30.67%)
 * Total Accepted:    237.8K
 * Total Submissions: 775.4K
 * Testcase Example:  '[1,0,-1,0,-2,2]\n0'
 *
 * Given an array nums of n integers and an integer target, are there elements
 * a, b, c, and d in nums such that a + b + c + d = target? Find all unique
 * quadruplets in the array which gives the sum of target.
 *
 * Note:
 *
 * The solution set must not contain duplicate quadruplets.
 *
 * Example:
 *
 *
 * Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.
 *
 * A solution set is:
 * [
 * ⁠ [-1,  0, 0, 1],
 * ⁠ [-2, -1, 1, 2],
 * ⁠ [-2,  0, 0, 2]
 * ]
 *
 *
 */
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <time.h>
#include <vector>
using namespace std;
class Solution {
public:
  vector<vector<int> > threeSum(vector<int> &nums, int target) {
    vector<vector<int> > outputs;
    if (nums.size() < 3)
      return outputs;

    int i = 0;
    while (i < nums.size() && nums[i] <= target / 3) {
      int iFirst = nums[i];
      int j = i + 1;
      int k = nums.size() - 1;
      while (j < k) {
        if (nums[i] + nums[j] + nums[k] < target) {
          while (j < nums.size() - 1 && nums[j] == nums[j + 1])
            j++;
          j++;
        } else if (nums[i] + nums[j] + nums[k] > target) {
          while (k > 0 && nums[k - 1] == nums[k])
            k--;
          k--;
        } else {
          vector<int> res;
          res.push_back(iFirst);
          res.push_back(nums[j]);
          res.push_back(nums[k]);
          outputs.push_back(res);
          while (j < nums.size() - 1 && nums[j] == nums[j + 1])
            j++;
          j++;
          while (k > 0 && nums[k - 1] == nums[k])
            k--;
          k--;
        }
      }
      i++;
      while (i < nums.size() && nums[i] == iFirst)
        i++;
    }
    return outputs;
  }

  vector<vector<int> > fourSum(vector<int> &nums, int target) {
    vector<vector<int> > outputs;
    if (nums.size() < 4)
      return outputs;
    sort(nums.begin(), nums.end());
    int i = 0;
    while (i < nums.size() && nums[i] <= target / 4) {
      int iFirst = nums[i];
      vector<int> tmp = nums;
      tmp.erase(tmp.begin(), tmp.begin() + i + 1);
      vector<vector<int> > outs = threeSum(tmp, target - iFirst);
      for (int j = 0; j < outs.size(); j++) {
        vector<int> res;
        res.push_back(iFirst);
        res.insert(res.end(), outs[j].begin(), outs[j].end());
        outputs.push_back(res);
      }
      i++;
      while (i < nums.size() && nums[i] == iFirst)
        i++;
    }
    return outputs;
  }
};

#if 0
int main() {
  Solution a;
  vector<int> tests;
  // while(1) {
  //     int test;
  //     cin >> test;
  //     if(test == 999)
  //         break;
  //     tests.push_back(test);
  // }
  string line;
  ifstream myfile("../tests");
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      const char *chInput = line.c_str();
      while (*chInput) {
        if (*chInput == '[') {
          chInput++;
          continue;
        } else if (*chInput == ']') {
          chInput++;
          continue;
        } else if (*chInput == ',') {
          chInput++;
          continue;
        } else if (*chInput == ' ') {
          chInput++;
          continue;
        } else {
          char input[999] = {0};
          int i = 0;
          for (; *chInput == '-' || (*chInput >= '0' && *chInput <= '9');
               chInput++, i++) {
            input[i] = *chInput;
          }
          string str = input;
          int val = 0;
          std::istringstream some_stream(str);
          some_stream >> val;
          tests.push_back(val);
        }
      }
    }
    myfile.close();
  }
  cout << "size is " << tests.size() << endl;
  clock_t begin = clock();
  clock_t end;
  double elapsed_secs;
  vector<vector<int> > out = a.fourSum(tests, -29);
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Run time: " << elapsed_secs << "s" << endl;
  cout << "result size is " << out.size() << endl;
#if 1
  for (int i = 0; i < out.size(); i++) {
    for (int j = 0; j < out[i].size(); j++) {
      if (j != out[i].size() - 1)
        cout << out[i][j] << ",";
      else
        cout << out[i][j] << endl;
    }
  }
#endif

  return 0;
}
#endif
