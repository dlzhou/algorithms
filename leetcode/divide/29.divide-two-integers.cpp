/*
 * [29] Divide Two Integers
 *
 * https://leetcode.com/problems/divide-two-integers/description/
 *
 * algorithms
 * Medium (16.16%)
 * Total Accepted:    203.7K
 * Total Submissions: 1.3M
 * Testcase Example:  '10\n3'
 *
 * Given two integers dividend and divisor, divide two integers without using
 * multiplication, division and mod operator.
 *
 * Return the quotient after dividing dividend by divisor.
 *
 * The integer division should truncate toward zero.
 *
 * Example 1:
 *
 *
 * Input: dividend = 10, divisor = 3
 * Output: 3
 *
 * Example 2:
 *
 *
 * Input: dividend = 7, divisor = -3
 * Output: -2
 *
 * Note:
 *
 *
 * Both dividend and divisor will be 32-bit signed integers.
 * The divisor will never be 0.
 * Assume we are dealing with an environment which could only store integers
 * within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of
 * this problem, assume that your function returns 231 − 1 when the division
 * result overflows.
 *
 *
 */
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <time.h>
#include <vector>
using namespace std;
class Solution {
public:
  int divide(int dividend, int divisor) {
    int n = 0;
    long long nDivisor = divisor;
    if (nDivisor < 0)
      nDivisor = -nDivisor;
    if (dividend == INT32_MIN && divisor == -1)
      return INT32_MAX;
    if (dividend == INT32_MIN && divisor == 1)
      return INT32_MIN;
    long long nDiv = dividend;
    if (nDiv < 0)
      nDiv = -nDiv;
    unsigned long long nMul = 1LL;
    while (nDiv >= nDivisor) {
      unsigned long long tDivisor = nDivisor;
      nMul = 1LL;
      while (tDivisor < nDiv) {
        tDivisor <<= 1;
        nMul <<= 1;
      }
      if (tDivisor > nDiv) {
        nMul >>= 1;
        tDivisor >>= 1;
      }
      n += nMul;
      nDiv -= tDivisor;
    }
    if (dividend >= 0 && divisor > 0)
      return n;
    else if (dividend < 0 && divisor < 0)
      return n;
    else
      return -n;
  }
};

#if 1
int main() {
  int nDiv = 2147483646;
  int nDivsor = 1;
  cin >> nDiv;
  cin >> nDivsor;
  Solution a;
  clock_t begin = clock();
  clock_t end;
  double elapsed_secs;
  int ret = a.divide(nDiv, nDivsor);
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Run time: " << elapsed_secs << "s" << endl;
  cout << ret << endl;

  return 0;
}
#endif