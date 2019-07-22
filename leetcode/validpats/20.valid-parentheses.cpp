/*
 * [20] Valid Parentheses
 *
 * https://leetcode.com/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (36.63%)
 * Total Accepted:    606.3K
 * Total Submissions: 1.7M
 * Testcase Example:  '"()"'
 *
 * Given a string containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 *
 * An input string is valid if:
 *
 *
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 *
 *
 * Note that an empty string is also considered valid.
 *
 * Example 1:
 *
 *
 * Input: "()"
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: "()[]{}"
 * Output: true
 *
 *
 * Example 3:
 *
 *
 * Input: "(]"
 * Output: false
 *
 *
 * Example 4:
 *
 *
 * Input: "([)]"
 * Output: false
 *
 *
 * Example 5:
 *
 *
 * Input: "{[]}"
 * Output: true
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
  bool isValid(string s) {
    if (s.empty())
      return true;
    if (s.size() == 1)
      return false;
    const char *chIput = s.c_str();
    stack<char> stacks;
    for (int m = 0; m < s.size(); m++) {
      if (chIput[m] == '(' || chIput[m] == '[' || chIput[m] == '{')
        stacks.push(chIput[m]);
      else if (chIput[m] == ')') {
        if (!stacks.empty() && stacks.top() == '(')
          stacks.pop();
        else
          return false;
      } else if (chIput[m] == ']') {
        if (!stacks.empty() && stacks.top() == '[')
          stacks.pop();
        else
          return false;
      } else {
        if (!stacks.empty() && stacks.top() == '{')
          stacks.pop();
        else
          return false;
      }
    }
    if (!stacks.empty())
      return false;
    return true;
  }
};

#if 0
int main() {
  Solution a;
  string tests;
  cin >> tests;

  //   vector<int> tests;
  //   while (1) {
  //     int test;
  //     cin >> test;
  //     if (test == 999)
  //       break;
  //     tests.push_back(test);
  //
  /*
  string line;
  ifstream myfile("../tests");
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      const char *chInput = line.c_str();
      while (*chInput) {
        if (*chInput == '[') {
          chInput++;
          continue;
        } else if (*chInput == ']') {
          chInput++;
          continue;
        } else if (*chInput == ',') {
          chInput++;
          continue;
        } else if (*chInput == ' ') {
          chInput++;
          continue;
        } else {
          char input[999] = {0};
          int i = 0;
          for (; *chInput == '-' || (*chInput >= '0' && *chInput <= '9');
               chInput++, i++) {
            input[i] = *chInput;
          }
          string str = input;
          int val = 0;
          std::istringstream some_stream(str);
          some_stream >> val;
          tests.push_back(val);
        }
      }
    }
    myfile.close();
  }
  cout << "size is " << tests.size() << endl;
  */
  clock_t begin = clock();
  clock_t end;
  double elapsed_secs;
  bool bValue = a.isValid(tests);
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Run time: " << elapsed_secs << "s" << endl;
  if (bValue)
    cout << "true" << endl;
  else
    cout << "false" << endl;
#if 0
  while (out) {
    cout << out->val << endl;
    out = out->next;
  }
#endif

  return 0;
}
#endif