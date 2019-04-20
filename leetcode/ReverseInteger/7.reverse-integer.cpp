/*
 * [7] Reverse Integer
 *
 * https://leetcode.com/problems/reverse-integer/description/
 *
 * algorithms
 * Easy (25.24%)
 * Total Accepted:    661.2K
 * Total Submissions: 2.6M
 * Testcase Example:  '123'
 *
 * Given a 32-bit signed integer, reverse digits of an integer.
 * 
 * Example 1:
 * 
 * 
 * Input: 123
 * Output: 321
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: -123
 * Output: -321
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: 120
 * Output: 21
 * 
 * 
 * Note:
 * Assume we are dealing with an environment which could only store integers
 * within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of
 * this problem, assume that your function returns 0 when the reversed integer
 * overflows.
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
    int reverse(int x) {
        if( !x )
            return 0;
        const unsigned MAXINT = 0x7fffffff;
        unsigned absx = 0;
        if(x == -(MAXINT+1))
            absx = MAXINT+1;
        else
            absx = x > 0 ? x : -x;
        int digits[100] = {0};
        int nsize = 0;
        while(absx>9) {
            int remain = absx - (absx/10) * 10;
            digits[nsize++] = remain;
            absx = absx / 10;
        }
        digits[nsize++] = absx;
        if(nsize > 10
            || (nsize == 10 && digits[0] > 2))
            return 0;
        if(nsize == 10) {
            int intmults[] = {1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1};
            unsigned uReal = 0;
            for(int i=0; i<10; i++)
                uReal += digits[i]*intmults[i];
            if(uReal > MAXINT)
                return 0;
        }
        int output = 0;
        int multis = 1;
        for(int i=0; i<nsize; i++) {
            output += digits[nsize - 1 - i] * multis;
            if(i<9)
                multis *= 10;
        }
        return x > 0 ? output : -output;
    }
};

// int main()
// {
//     clock_t begin = clock();
//     clock_t end;
//     double elapsed_secs;
// 	Solution a;
//     int input = -2147483412;                                ;
//     cout << input << endl;
// 	int out = a.reverse(input);
// 	cout << out << endl;
//     end = clock();
//     elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//     cout << "Run time: " << elapsed_secs << "s" << endl;
//     return 0;
// }