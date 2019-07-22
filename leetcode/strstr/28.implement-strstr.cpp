/*
 * [28] Implement strStr()
 *
 * https://leetcode.com/problems/implement-strstr/description/
 *
 * algorithms
 * Easy (32.29%)
 * Total Accepted:    446.3K
 * Total Submissions: 1.4M
 * Testcase Example:  '"hello"\n"ll"'
 *
 * Implement strStr().
 *
 * Return the index of the first occurrence of needle in haystack, or -1 if
 * needle is not part of haystack.
 *
 * Example 1:
 *
 *
 * Input: haystack = "hello", needle = "ll"
 * Output: 2
 *
 *
 * Example 2:
 *
 *
 * Input: haystack = "aaaaa", needle = "bba"
 * Output: -1
 *
 *
 * Clarification:
 *
 * What should we return when needle is an empty string? This is a great
 * question to ask during an interview.
 *
 * For the purpose of this problem, we will return 0 when needle is an empty
 * string. This is consistent to C's strstr() and Java's indexOf().
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
  int strStr(string haystack, string needle) {
    if (needle.empty())
      return 0;
    if (haystack.empty())
      return -1;
    const char *chNeedle = needle.c_str();
    int *mapStr = new int[needle.size()];
    mapStr[0] = -1;
    if(needle.size()>1)
      mapStr[1] = 0;
    int n = 0;
    int id = 2;
    while (id < needle.size()) {
      if (chNeedle[n] == chNeedle[id-1]) {
        n++;
        mapStr[id] = n;
        id++;
      } else if (n>0){
        n = mapStr[n];
       } else {
          mapStr[id] = 0;
          id++;
        }
      //   mapStr[id] = n;
      //   n = mapStr[n];
      //   while (n >= 0 && chNeedle[id] != chNeedle[n])
      //     n = mapStr[n];
      // }
      // n++;
    }
    const char *chInput = haystack.c_str();
    int index = -1;
    int j = 0;
    int i = 0;
    while (i < haystack.size()) {
      if (j < needle.size() && chInput[i] == chNeedle[j]) {
        j++;
        i++;
      } else if (j == needle.size()) {
        index = i - j;
        break;
      } else {
        if (mapStr[j] != -1)
          j = mapStr[j];
        else {
          j = 0;
          i++;
        }
      }
    }
    if (index == -1 && j == needle.size())
      index = haystack.size() - j;
    delete[] mapStr;
    return index;
  }
};

#if 0
int main() {
  Solution a;
  string strinput;

  strinput = "aabaaabaaac";
  // cin >> strinput;
  string strneedle = "HeHeHello";
  // cin >> strneedle;
  clock_t begin = clock();
  clock_t end;
  double elapsed_secs;
  int ret = a.strStr(strinput, strneedle);
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Run time: " << elapsed_secs << "s" << endl;
  cout << ret << endl;

  return 0;

}
#endif