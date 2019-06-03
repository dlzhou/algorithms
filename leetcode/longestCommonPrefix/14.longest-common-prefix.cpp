/*
 * [14] Longest Common Prefix
 *
 * https://leetcode.com/problems/longest-common-prefix/description/
 *
 * algorithms
 * Easy (33.47%)
 * Total Accepted:    463.1K
 * Total Submissions: 1.4M
 * Testcase Example:  '["flower","flow","flight"]'
 *
 * Write a function to find the longest common prefix string amongst an array
 * of strings.
 * 
 * If there is no common prefix, return an empty string "".
 * 
 * Example 1:
 * 
 * 
 * Input: ["flower","flow","flight"]
 * Output: "fl"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 * 
 * 
 * Note:
 * 
 * All given inputs are in lowercase letters a-z.
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
    string longestCommonPrefix(vector<string>& strs) {
        string strCommon = "";
        if(strs.size()<1)
            return strCommon;
        int nSize = strs.size();
        int iLen = 0;
        while(1) {
            int a[26] = {0};
            char chIndex = ' ';
            for(int i=0; i<nSize; i++) {
                if(iLen < strs[i].size()){
                    chIndex = *(strs[i].c_str() + iLen);
                    a[chIndex - 'a'] ++;
                }
            }
            if(chIndex == ' ')
                break;
            if(a[chIndex - 'a'] != nSize)
                break;
            strCommon += chIndex;
            iLen ++;
        }
        return strCommon;
    }
};

// int main()
// {
//     clock_t begin = clock();
//     clock_t end;
//     double elapsed_secs;
// 	Solution a;
//     vector<string> tests;
//     while(1) {
//         string test;
//         cin >> test;
//         if(test == "q" || test == "Q")
//             break;
//         tests.push_back(test);
//     }
//     string out = a.longestCommonPrefix(tests);
// 	cout << out << endl;
//     end = clock();
//     elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//     cout << "Run time: " << elapsed_secs << "s" << endl;
//     return 0;
// }
