/*
 * [8] String to Integer (atoi)
 *
 * https://leetcode.com/problems/string-to-integer-atoi/description/
 *
 * algorithms
 * Medium (14.59%)
 * Total Accepted:    350.5K
 * Total Submissions: 2.4M
 * Testcase Example:  '"42"'
 *
 * Implement atoi which converts a string to an integer.
 * 
 * The function first discards as many whitespace characters as necessary until
 * the first non-whitespace character is found. Then, starting from this
 * character, takes an optional initial plus or minus sign followed by as many
 * numerical digits as possible, and interprets them as a numerical value.
 * 
 * The string can contain additional characters after those that form the
 * integral number, which are ignored and have no effect on the behavior of
 * this function.
 * 
 * If the first sequence of non-whitespace characters in str is not a valid
 * integral number, or if no such sequence exists because either str is empty
 * or it contains only whitespace characters, no conversion is performed.
 * 
 * If no valid conversion could be performed, a zero value is returned.
 * 
 * Note:
 * 
 * 
 * Only the space character ' ' is considered as whitespace character.
 * Assume we are dealing with an environment which could only store integers
 * within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical
 * value is out of the range of representable values, INT_MAX (231 − 1) or
 * INT_MIN (−231) is returned.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: "42"
 * Output: 42
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "   -42"
 * Output: -42
 * Explanation: The first non-whitespace character is '-', which is the minus
 * sign.
 * Then take as many numerical digits as possible, which gets 42.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: "4193 with words"
 * Output: 4193
 * Explanation: Conversion stops at digit '3' as the next character is not a
 * numerical digit.
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: "words and 987"
 * Output: 0
 * Explanation: The first non-whitespace character is 'w', which is not a
 * numerical 
 * digit or a +/- sign. Therefore no valid conversion could be performed.
 * 
 * Example 5:
 * 
 * 
 * Input: "-91283472332"
 * Output: -2147483648
 * Explanation: The number "-91283472332" is out of the range of a 32-bit
 * signed integer.
 * Thefore INT_MIN (−231) is returned.
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
    int myAtoi(string str) {
        if(str.empty())
            return 0;
        const char *chStr = str.c_str();
        unsigned long long ullOut = 0LL;
        int nPos = 1;
        bool bHead = true;
        for(int i=0; i<str.size(); i++) {
            if(bHead && chStr[i] == ' ')
                continue;
            if( bHead
             && (chStr[i] != '-')
             && (chStr[i] != '+')
             && ((chStr[i] - '0' < 0)
             || (chStr[i] - '9' > 0))
            )
                return 0;

            if(bHead && chStr[i] == '-'){
                nPos = -1;
                bHead = false;
            } else if(bHead && chStr[i] == '+'){ 
                bHead = false;
            } else if( chStr[i] - '0' >=0 
            && chStr[i] - '9' <= 0 ) {
                int val = chStr[i] - '0';
                ullOut *= 10;
                ullOut += val;
                if(ullOut > INT_MAX && nPos > 0)
                    return INT_MAX;
                if(ullOut > 0x80000000LL && nPos < 0)
                    return INT_MIN;
                if(ullOut == 0x80000000LL && nPos < 0)
                    return INT_MIN;
                bHead = false; 
            } else
                break; 
        }
        return (int)ullOut * nPos;
    }
};

int main()
{
    clock_t begin = clock();
    clock_t end;
    double elapsed_secs;
	Solution a;
    string s = "   +8347 2332";
    cout << s.c_str() << endl;
	int out = a.myAtoi(s);
	cout << out << endl;
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Run time: " << elapsed_secs << "s" << endl;
    return 0;
}
