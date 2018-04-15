// ShortestPalindrome.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.length();
		if(n<=1)
			return s;
		bool bIsPalindrome = false;
		int k = 0;
		for(k = n - 1; k>=0 && !bIsPalindrome; k--) {
			int i=0;
			int j=k;
			for(; i<j && s[i] == s[j]; i++,j--);
			if(i>=j)
				bIsPalindrome = true;		
		}
		if(k==n-2)
			return s;
		k += 2;
		char *input = (char *)s.c_str();
        char* output = new char[n-k+1];
        int id=0;
        for(id=k;id<n;id++){
            output[n-id-1] = input[id];
        }
        output[n-k] = '\0';
        s = output + s;
		delete output;
		return s;
	}
};

int main(int argc, char* argv[])
{
	string out;
	Solution sol;
	if(argc > 1) {
		string input = argv[1];
		out = sol.shortestPalindrome(input);
	} else {
		out = sol.shortestPalindrome("abcd");//gabqtbypdwjjelvgohmvzpyfqayobkyyhoizaqhtqkzodcosufbpgurxsbjtrkombfbl
	}
	cout << out << endl;
	cout << out.length() << endl;
	return 0;
}

