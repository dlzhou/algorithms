/*
 * [6] ZigZag Conversion
 *
 * https://leetcode.com/problems/zigzag-conversion/description/
 *
 * algorithms
 * Medium (31.28%)
 * Total Accepted:    303.8K
 * Total Submissions: 971.3K
 * Testcase Example:  '"PAYPALISHIRING"\n3'
 *
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
 * of rows like this: (you may want to display this pattern in a fixed font for
 * better legibility)
 * 
 * 
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 
 * 
 * And then read line by line: "PAHNAPLSIIGYIR"
 * 
 * Write the code that will take a string and make this conversion given a
 * number of rows:
 * 
 * 
 * string convert(string s, int numRows);
 * 
 * Example 1:
 * 
 * 
 * Input: s = "PAYPALISHIRING", numRows = 3
 * Output: "PAHNAPLSIIGYIR"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "PAYPALISHIRING", numRows = 4
 * Output: "PINALSIGYAHRPI"
 * Explanation:
 * 
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 * 
 */
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <time.h>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
         if(numRows == 1)
             return s;
        if (s.empty())
            return s;
        if (s == "")
            return s;
        vector<vector<char> > arrays;
        arrays.reserve(numRows);
        const char* strCh = s.c_str();
        int iRows = 0;
        bool bInc = true;
        for(int i=0; i<s.size(); i++) {
            if(arrays.size() < iRows+1) {
                vector<char> elements;
                elements.push_back(strCh[i]);
                arrays.push_back(elements);
            } else
                arrays[iRows].push_back(strCh[i]);
            if(bInc) {
                iRows ++;
                if(iRows >= numRows - 1) {
                    bInc = false;
                    iRows = numRows - 1;
                }
            } else {
                iRows --;
                if(!iRows)
                    bInc = true;
            }
        }
        string output = "";
        for(int j=0; j<numRows; j++){
            for(int k=0; k<arrays[j].size(); k++)
                output += arrays[j][k];
        }
        return output;
    }
};

// int main()
// {
//     clock_t begin = clock();
//     clock_t end;
//     double elapsed_secs;
// 	Solution a;
//     string s = "";
//     cout << s.c_str() << endl;
// 	string out = a.convert(s, 1);
// 	cout << out.c_str() << endl;
//     end = clock();
//     elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//     cout << "Run time: " << elapsed_secs << "s" << endl;
//     return 0;
// }
