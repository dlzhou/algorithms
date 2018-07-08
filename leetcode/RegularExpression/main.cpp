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

    bool isMatch(string s, string p) {
        const char* chPattern = p.c_str();
        const char* chInput = s.c_str();
        char previousP = ' ';
        int iStart = 0;
        int iStartP = 0;
        while(iStart<s.length() && iStartP<p.length()) {
            if((chInput[iStart] == chPattern[iStartP]
                || chPattern[iStartP] == '.' ) 
                && ( iStartP + 1 == p.length() 
                  || iStartP+1 < p.length() && chPattern[iStartP+1] != '*')){
                iStart++;
                iStartP++;
                continue;
            }
            if(iStartP+1 < p.length()
             && chPattern[iStartP + 1] == '*') {
                 previousP = chPattern[iStartP];
                for(; iStart < s.length(); iStart++){
                    if(chInput[iStart] != previousP 
                     && previousP != '.')
                        break;
                    if( iStartP + 2 < p.length()
                        && isMatch(s.substr(iStart, s.length() - iStart), p.substr(iStartP+2, p.length() - iStartP - 2)))
                        return true;
                }
                iStartP += 2;
                continue;
            }
            break;
        }
        if(iStart == s.length() && iStartP == p.length())
            return true;
        if(iStart == s.length()) {
            while(iStartP+1 < p.length() && chPattern[iStartP+1] == '*') {
                iStartP += 2;
            }
            if(iStartP == p.length())
                return true;
        }            
        return false;        
    }
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
    string p = getInput();

    clock_t begin = clock();
    clock_t end;
    double elapsed_secs;
	Solution a;
	bool bMatch = a.isMatch(s, p);
    string output = bMatch ? "true" : "false";
	cout << output << endl;
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Run time: " << elapsed_secs << "s" << endl;
    return 0;
}

