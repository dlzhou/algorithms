/*
 * [15] 3Sum
 *
 * https://leetcode.com/problems/3sum/description/
 *
 * algorithms
 * Medium (23.98%)
 * Total Accepted:    548.2K
 * Total Submissions: 2.3M
 * Testcase Example:  '[-1,0,1,2,-1,-4]'
 *
 * Given an array nums of n integers, are there elements a, b, c in nums such
 * that a + b + c = 0? Find all unique triplets in the array which gives the
 * sum of zero.
 * 
 * Note:
 * 
 * The solution set must not contain duplicate triplets.
 * 
 * Example:
 * 
 * 
 * Given array nums = [-1, 0, 1, 2, -1, -4],
 * 
 * A solution set is:
 * [
 * ⁠ [-1, 0, 1],
 * ⁠ [-1, -1, 2]
 * ]
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
    vector<vector<int> > threeSum(vector<int>& nums) {
        vector<vector<int> > outputs;
        if(nums.size()<3)
            return outputs;
        sort(nums.begin(), nums.end());
        
        int last = INT32_MIN;
        int iMax = nums.size() - 1;
        int i=0;
        int *mapTotal = new int[nums.size()];
        memset(mapTotal, 0, sizeof(int)*nums.size());
        while(i < nums.size() && nums[i] <= 0){
            if(nums[i] == last) {
                i++;
                continue;
            }
            int iMaxIndex = (mapTotal[i] == 0) ? (nums.size() - 1) : mapTotal[i];
            while((i<iMaxIndex-1)
            && nums[i] + nums[iMaxIndex-1] + nums[iMaxIndex] < 0) {
                i++;
                iMaxIndex = (mapTotal[i] == 0) ? (nums.size() - 1) : mapTotal[i];
            }
            if (i<nums.size()-2
             && nums[i] + nums[i+1] + nums[i+2] > 0) {
                break;
            }
            last = nums[i];
            int j = i+1;
            int k = iMaxIndex;
            int last2 = INT32_MIN;
            int last3 = INT32_MIN;
            while(j<k) {
                if(nums[i] + nums[j] + nums[k] > 0){
                    last3 = nums[k];
                    mapTotal[j] = k;
                    k--;
                } else if(nums[i] + nums[j] + nums[k] < 0){
                    last2 = nums[j];
                    j++;
                } else if(nums[i] + nums[j] + nums[k] == 0
                 && nums[j] != last2 && nums[k] != last3) {
                    vector<int> res; 
                    res.push_back(nums[i]);
                    res.push_back(nums[j]);
                    res.push_back(nums[k]);
                    outputs.push_back(res);
                    last2 = nums[j];
                    last3 = nums[k];
                    j ++;
                    k --;
                } else if(nums[j] == last2) {
                    j ++;
                } else/* if(nums[k] == last3)*/ {
                    k --;
                }
            }
            i++;
         }
        delete[] mapTotal;
        return outputs;
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
  ifstream myfile ("../tests.strings");
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
            }
            else {
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
    vector<vector<int> > out = a.threeSum(tests);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Run time: " << elapsed_secs << "s" << endl;
    cout << "result size is " << out.size() << endl;
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
