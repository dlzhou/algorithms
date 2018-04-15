// SlidingWinMax.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> maxOut;
		if (nums.size() == 0)
			return maxOut;
		for (int i = 0; i <= nums.size() - k; i++) {
			if (!i) {
				int max = nums[0];
				for (int j = 1; j < k; j++) {
					if (nums[j] > max)
						max = nums[j];
				}
				maxOut.push_back(max);
			}
			else {
				if (maxOut[i - 1] <= nums[i + k-1])
					maxOut.push_back(nums[i + k-1]);
				else if (maxOut[i - 1] != nums[i - 1])
					maxOut.push_back(maxOut[i - 1]);
				else {
					int max = nums[i];
					for (int j = i; j < i+k; j++) {
						if (nums[j] > max)
							max = nums[j];
					}
					maxOut.push_back(max);
				}
			}
			
		}
		return maxOut;
	}
};

int main()
{
	int input[] = { 1,3,-1,-3,5,3,6,7 };
	vector<int> nums;
	for (int i = 0; i<sizeof(input) / sizeof(input[0]); i++) {
		nums.push_back(input[i]);
	}
	int id = nums.size();
	clock_t begin = clock();
	Solution sol;
	vector<int> ret = sol.maxSlidingWindow(nums, 3);//16021);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	for (int i = 0; i<ret.size(); i++) {
		cout << ret[i] << endl;
	}
	cout << "Run time: " << elapsed_secs << "s" << endl;
    return 0;
}

