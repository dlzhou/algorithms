/*
 * [13] Roman to Integer
 *
 * https://leetcode.com/problems/roman-to-integer/description/
 *
 * algorithms
 * Easy (52.32%)
 * Total Accepted:    413.4K
 * Total Submissions: 790.2K
 * Testcase Example:  '"III"'
 *
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D
 * and M.
 * 
 * 
 * Symbol       Value
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 * 
 * For example, two is written as II in Roman numeral, just two one's added
 * together. Twelve is written as, XII, which is simply X + II. The number
 * twenty seven is written as XXVII, which is XX + V + II.
 * 
 * Roman numerals are usually written largest to smallest from left to right.
 * However, the numeral for four is not IIII. Instead, the number four is
 * written as IV. Because the one is before the five we subtract it making
 * four. The same principle applies to the number nine, which is written as IX.
 * There are six instances where subtraction is used:
 * 
 * 
 * I can be placed before V (5) and X (10) to make 4 and 9. 
 * X can be placed before L (50) and C (100) to make 40 and 90. 
 * C can be placed before D (500) and M (1000) to make 400 and 900.
 * 
 * 
 * Given a roman numeral, convert it to an integer. Input is guaranteed to be
 * within the range from 1 to 3999.
 * 
 * Example 1:
 * 
 * 
 * Input: "III"
 * Output: 3
 * 
 * Example 2:
 * 
 * 
 * Input: "IV"
 * Output: 4
 * 
 * Example 3:
 * 
 * 
 * Input: "IX"
 * Output: 9
 * 
 * Example 4:
 * 
 * 
 * Input: "LVIII"
 * Output: 58
 * Explanation: L = 50, V= 5, III = 3.
 * 
 * 
 * Example 5:
 * 
 * 
 * Input: "MCMXCIV"
 * Output: 1994
 * Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
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
    int romanToInt(string s) {
        const char* chInput = s.c_str();
        int iVal = 0;
        while(*chInput) {
            if(*chInput == 'M')
                iVal += 1000;
            else if(*chInput == 'D')
                iVal += 500;
                else if (*chInput == 'C') {
                    if(*(chInput+1) == 'M') { 
                        chInput ++;
                        iVal += 900;
                    } else if (*(chInput+1) == 'D') {
                        chInput ++;
                        iVal += 400;
                    } else
                        iVal += 100;
                } else if (*chInput == 'L')
                    iVal += 50;
                 else if (*chInput == 'X') {
                      if(*(chInput+1) == 'L') {
                        chInput ++;
                        iVal += 40;
                    } else if (*(chInput+1) == 'C') {
                        chInput ++;
                        iVal += 90;
                    } else
                        iVal += 10;                   
                 } else if (*chInput == 'V')
                    iVal += 5;
                    else if (*chInput == 'I') {
                      if(*(chInput+1) == 'V') {
                        chInput ++;
                        iVal += 4;
                    } else if (*(chInput+1) == 'X') {
                        chInput ++;
                        iVal += 9;
                    } else
                        iVal += 1;                          
                    }
                    chInput ++;
                
        }
        return iVal;
    }
};

// int main()
// {
//     clock_t begin = clock();
//     clock_t end;
//     double elapsed_secs;
// 	Solution a;
//     string test;
//     cin >> test;
//     int out = a.romanToInt(test);
// 	cout << out << endl;
//     end = clock();
//     elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//     cout << "Run time: " << elapsed_secs << "s" << endl;
//     return 0;
// }
