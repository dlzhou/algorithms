/*
 * [22] Generate Parentheses
 *
 * https://leetcode.com/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (55.28%)
 * Total Accepted:    347.6K
 * Total Submissions: 628.8K
 * Testcase Example:  '3'
 *
 *
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 *
 *
 *
 * For example, given n = 3, a solution set is:
 *
 *
 * [
 * ⁠ "((()))",
 * ⁠ "(()())",
 * ⁠ "(())()",
 * ⁠ "()(())",
 * ⁠ "()()()"
 * ]
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
  vector<string> generateParenthesis(int n) {
    vector<string> outputs;
    if (!n)
      return outputs;
    string strFirst = "()";
    vector<string> lastouts;
    lastouts.push_back(strFirst);
    outputs = lastouts;
    for (int i = 1; i < n; i++) {
      outputs.clear();
      for (int j = 0; j < lastouts.size(); j++) {
        string strInput = lastouts[j];
        int k = 0;
        for (; k < strInput.size() && strInput.c_str()[k] == '('; k++) {
          string part1 = strInput.substr(0, k);
          string part2 = strInput.substr(k, strInput.size() - k);
          string res = part1 + "()" + part2;
          outputs.push_back(res);
        }
        if (k < strInput.size()) {
          string part1 = strInput.substr(0, k);
          string part2 = strInput.substr(k, strInput.size() - k);
          string res = part1 + "()" + part2;
          outputs.push_back(res);
        }
      }
      lastouts = outputs;
    }
    return outputs;
  }
};

#if 0
int main() {
  Solution a;
  // string tests;
  int tests;
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
  vector<string> strValue = a.generateParenthesis(tests);
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Run time: " << elapsed_secs << "s" << endl;
  cout << "size is " << strValue.size() << endl;
#if 0
  for (int i = 0; i < strValue.size(); i++) {
    cout << strValue[i] << endl;
  }
#endif

  return 0;
}
#endif