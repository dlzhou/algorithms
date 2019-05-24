/*
 * [9] Palindrome Number
 *
 * https://leetcode.com/problems/palindrome-number/description/
 *
 * algorithms
 * Easy (42.80%)
 * Total Accepted:    554.4K
 * Total Submissions: 1.3M
 * Testcase Example:  '121'
 *
 * Determine whether an integer is a palindrome. An integer is a palindrome
 * when it reads the same backward as forward.
 * 
 * Example 1:
 * 
 * 
 * Input: 121
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it
 * becomes 121-. Therefore it is not a palindrome.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a
 * palindrome.
 * 
 * 
 * Follow up:
 * 
 * Coud you solve it without converting the integer to a string?
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
    bool isPalindrome(int x) {
         if(x < 0)
            return false;
         if(!x)
            return true;
         int nDigits[100] = {0};
         int i = 0;
         while(x>9){
            int nRemainder = x - (x/10) * 10;
            nDigits[i++] = nRemainder;
            x /= 10;
         }
         nDigits[i++] = x;
         for(int m = 0, n = i - 1; m<n; m++, n--){
             if(nDigits[m] != nDigits[n])
                return false;
         }
         return true;
    }
};

// int main()
// {
//     clock_t begin = clock();
//     clock_t end;
//     double elapsed_secs;
// 	Solution a;
//     int input = -123321;                                ;
//     cout << input << endl;
// 	bool out = a.isPalindrome(input);
// 	cout << (out ? "true" : "false") << endl;
//     end = clock();
//     elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//     cout << "Run time: " << elapsed_secs << "s" << endl;
//     return 0;
// }
