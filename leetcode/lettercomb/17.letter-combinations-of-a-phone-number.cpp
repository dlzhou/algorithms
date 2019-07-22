/*
 * [17] Letter Combinations of a Phone Number
 *
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * algorithms
 * Medium (41.74%)
 * Total Accepted:    395.9K
 * Total Submissions: 948.4K
 * Testcase Example:  '"23"'
 *
 * Given a string containing digits from 2-9 inclusive, return all possible
 * letter combinations that the number could represent.
 * 
 * A mapping of digit to letters (just like on the telephone buttons) is given
 * below. Note that 1 does not map to any letters.
 * 
 * 
 * 
 * Example:
 * 
 * 
 * Input: "23"
 * Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 * 
 * 
 * Note:
 * 
 * Although the above answer is in lexicographical order, your answer could be
 * in any order you want.
 * 
 */
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <time.h>
#include <map>
#include <stack>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> outputs;
        stack<string> digitstack;
        const char* digitsalpha[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        for(int i=0; i<digits.size(); i++)
            digitstack.push(digitsalpha[digits.c_str()[i]-'2']);
        while(!digitstack.empty()) {
            string alphabet = digitstack.top();
            if(!outputs.size())
                for(int i=0; i<alphabet.size(); i++) {
                    outputs.push_back(string(1, alphabet.c_str()[i]));
                }
            else  {
                vector<string> tmp = outputs;
                outputs.clear();
                for(int i=0; i<alphabet.size(); i++) {
                    for(int j=0; j<tmp.size(); j++) {
                        string newstr = alphabet.c_str()[i] + tmp[j];
                        outputs.push_back(newstr);
                    }
                }
            }
            digitstack.pop();
        }
        return outputs;
    }
};


#if 1
int main()
{
	Solution a;
    vector<int> tests;
    while(1) {
        int test;
        cin >> test;
        if(test == 999)
            break;
        tests.push_back(test);
    }
 string input = "";
 for(int i=0; i<tests.size(); i++) {
     char chInput = tests[i] + '0';
     input = input + chInput;
 }
 cout << "input is " << input << endl;
#if 0
  string line;
  ifstream myfile ("../tests");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
        const char* chInput = line.c_str();
        while(*chInput) {
            if(*chInput == '['){
                chInput ++;
                continue;
            } else if(*chInput == ']'){
                chInput ++;
                continue;
            } else if(*chInput == ',') {
                chInput ++;
                continue;
            } else if(*chInput == ' ') {
                chInput ++;
                continue;
            } else {
                char input[999] = {0};
                int i=0;
                for(; *chInput=='-'|| (*chInput>='0' && *chInput<='9');chInput++, i++){
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
#endif
    clock_t begin = clock();
    clock_t end;
    double elapsed_secs;
    vector<string> out = a.letterCombinations(input);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Run time: " << elapsed_secs << "s" << endl;
    cout << "result size is " << out.size() << endl;
#if 1
    for(int i=0; i<out.size(); i++) {
        if(i!=out.size()-1)
	            cout << out[i] << "," ;
            else
                cout << out[i] << endl;
    }
#endif

    return 0;
}
#endif
   