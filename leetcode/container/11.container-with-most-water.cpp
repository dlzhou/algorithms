/*
 * [11] Container With Most Water
 *
 * https://leetcode.com/problems/container-with-most-water/description/
 *
 * algorithms
 * Medium (43.78%)
 * Total Accepted:    349.9K
 * Total Submissions: 799.3K
 * Testcase Example:  '[1,8,6,2,5,4,8,3,7]'
 *
 * Given n non-negative integers a1, a2, ..., an , where each represents a
 * point at coordinate (i, ai). n vertical lines are drawn such that the two
 * endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together
 * with x-axis forms a container, such that the container contains the most
 * water.
 * 
 * Note: You may not slant the container and n is at least 2.
 * 
 * 
 * 
 * 
 * 
 * The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In
 * this case, the max area of water (blue section) the container can contain is
 * 49. 
 * 
 * 
 * 
 * Example:
 * 
 * 
 * Input: [1,8,6,2,5,4,8,3,7]
 * Output: 49
 * 
 */
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <time.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        if(height.size()<2)
            return 0;
        int nLeft = 0;
        int nRight = height.size()-1;
        int nWidth = nRight - nLeft;
        int nHeight = height[nRight] > height[nLeft] ? height[nLeft] : height[nRight];
        int nMaxArea = nWidth * nHeight;
        do {
            if(height[nRight] > height[nLeft]) {
                nLeft ++;
                if(height[nLeft] > nHeight) {
                    nHeight = height[nRight] > height[nLeft] ? height[nLeft] : height[nRight];
                    nWidth = nRight - nLeft;
                    if(nWidth * nHeight > nMaxArea)
                        nMaxArea = nWidth * nHeight;
                } 
            } else {
              nRight --;
                 if(height[nRight] > nHeight) {
                    nHeight = height[nRight] > height[nLeft] ? height[nLeft] : height[nRight];
                    nWidth = nRight - nLeft;
                    if(nWidth * nHeight > nMaxArea)
                        nMaxArea = nWidth * nHeight;
                }             
            } 
        } while(nLeft < nRight);
      
        return nMaxArea;
    }
};

// int main()
// {
//     clock_t begin = clock();
//     clock_t end;
//     double elapsed_secs;
// 	Solution a;
//     vector<int> at;
//     int atest[] = {1,8,6,2,5,4,8,3,7};
//     for(int i=0; i<sizeof(atest)/sizeof(atest[0]); i++)
//         at.push_back(atest[i]);
//     int out = a.maxArea(at);
// 	cout << out << endl;
//     end = clock();
//     elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//     cout << "Run time: " << elapsed_secs << "s" << endl;
//     return 0;
// }