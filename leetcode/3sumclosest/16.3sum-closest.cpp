/*
 * [16] 3Sum Closest
 *
 * https://leetcode.com/problems/3sum-closest/description/
 *
 * algorithms
 * Medium (45.77%)
 * Total Accepted:    350.1K
 * Total Submissions: 765K
 * Testcase Example:  '[-1,2,1,-4]\n1'
 *
 * Given an array nums of n integers and an integer target, find three integers
 * in nums such that the sum is closest to target. Return the sum of the three
 * integers. You may assume that each input would have exactly one solution.
 * 
 * Example:
 * 
 * 
 * Given array nums = [-1, 2, 1, -4], and target = 1.
 * 
 * The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 * 
 * 
 */
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <time.h>
#include <map>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int closest = INT16_MIN;
        if(nums.size()<3)
            return target;
        sort(nums.begin(), nums.end());
        
        if(nums[0] + nums[1] + nums[2] > target)
            return (nums[0] + nums[1] + nums[2]);
        
        if(nums[nums.size()-3] + nums[nums.size()-2] + nums[nums.size()-1] < target)
            return (nums[nums.size()-3] + nums[nums.size()-2] + nums[nums.size()-1]);

        int i=0;
        while(i<nums.size()-2) {
            int j = i + 1;
            int k = nums.size() - 1;
            int iLess = INT16_MIN;
            int iGreat = INT16_MAX;
            int iClosest = INT16_MIN;
            while(j<k) {
                if(nums[i] + nums[j] +  nums[k] < target){
                    int nLess = nums[i] + nums[j] +  nums[k];
                    if(target-iLess > target-nLess)
                        iLess = nLess;
                    while(j<nums.size()-1 && nums[j] == nums[j+1]) j++;
                    j++;
                } else if (nums[i] + nums[j] +  nums[k] > target) {
                    int nGreat = nums[i] + nums[j] +  nums[k];
                    if(iGreat-target > nGreat-target)
                        iGreat = nGreat;
                    while(k>0 && nums[k-1] == nums[k]) k--;
                    k--;
                } else
                    return target;
            }
            if(target-iLess > iGreat - target) 
                iClosest = iGreat;
            else
                iClosest = iLess;
            if(abs(iClosest - target) < abs(closest - target)) {
                closest = iClosest;
            }
          while(i<nums.size()-3 && nums[i] == nums[i+1]) i++;
          i++;
        }
        return closest;
    }
};


#if 0
int main()
{
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
  ifstream myfile ("../tests");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
        const char* chInput = line.c_str();
        while(*chInput) {
            if(*chInput == '['){
                chInput ++;
                continue;
            } else if(*chInput == ']'){
                chInput ++;
                continue;
            } else if(*chInput == ',') {
                chInput ++;
                continue;
            } else if(*chInput == ' ') {
                chInput ++;
                continue;
            } else {
                char input[999] = {0};
                int i=0;
                for(; *chInput=='-'|| (*chInput>='0' && *chInput<='9');chInput++, i++){
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
    int out = a.threeSumClosest(tests, 3);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Run time: " << elapsed_secs << "s" << endl;
    cout << "result is " << out << endl;
#if 0
    for(int i=0; i<out.size(); i++) {
        for(int j=0; j<out[i].size(); j++){
            if(j!=out[i].size()-1)
	            cout << out[i][j] << "," ;
            else
                cout << out[i][j] << endl;
        }
    }
#endif

    return 0;
}
#endif
   
