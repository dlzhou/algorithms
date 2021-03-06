#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <time.h>
#include <map>
using namespace std;



class Solution {
public:
    bool isPalindrome(string s) {
        const char* sin = s.c_str();
        bool bRet = false;
        for(int i=0, j=s.length()-1; i<s.length(); i++,j--) {
            if(sin[i] != sin[j])
                break;
            if(i>=j) {
                bRet = true;
                break;
            }
        }
        return bRet;
    }

    string longestPalindrome(string s)
    {
        map< char, vector<int> > hashMap;
        const char *strInput = s.c_str();

        int maxlen = 1;
        string maxPal = s.substr(0, 1);
        for (int i = 0; i < s.length(); i++)
        {
            for (int j = 0; j < hashMap[strInput[i]].size(); j++)
            {
                int k = hashMap[strInput[i]][j];
                if(i-k+1 > maxlen
                 && isPalindrome(s.substr(k, i-k+1))) {
                    maxlen = i-k+1;
                    maxPal = s.substr(k, i-k+1);
                }
            }
            hashMap[strInput[i]].push_back(i);
        }
        return maxPal;
    }

#if 0
    string longestPalindrome(string s) {
        int maxlen = 1;
        string maxPal = s.substr(0,1);
        for(int i=0; i<s.length(); i++){
            for(int j=i+maxlen; j<s.length(); j++) {
                if(j-i+1 > maxlen
                 && isPalindrome(s.substr(i, j-i+1))) {
                    maxlen = j-i+1;
                    maxPal = s.substr(i, j-i+1);
                }
            }
        }
        return maxPal;
    }
#endif
};


string& getInput()
{
	char strinput[100];
	scanf("%s", strinput);
	string* input = new string(strinput);
	return *input;
}

int main()
{
	string s = getInput();

    clock_t begin = clock();
    clock_t end;
    double elapsed_secs;
	Solution a;
	string len = a.longestPalindrome(s);
	cout << len << endl;
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Run time: " << elapsed_secs << "s" << endl;
    return 0;
}

