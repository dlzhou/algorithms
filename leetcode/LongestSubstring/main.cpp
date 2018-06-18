#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <time.h>
using namespace std;



class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() < 1)
            return 0;
        const char* strInput = s.c_str();
        int nMax = 1;
        int nHead = 0;
        int nTail = 1;
        int nMaxLen = 1;
        int chInputs[1000] = {-1};
        memset(chInputs,-1, 1000*sizeof(int));
        chInputs[strInput[nHead]] = nHead;
        for(;nTail<strlen(strInput); nTail++) {
            if(chInputs[strInput[nTail]] == -1
               || chInputs[strInput[nTail]] < nHead ) {
                chInputs[strInput[nTail]] = nTail;
                nMaxLen ++;
            } else {
                   int m = chInputs[strInput[nTail]];
                    chInputs[strInput[nTail]] = nTail;
                    if(nMaxLen > nMax)
                        nMax = nMaxLen;
                    nMaxLen = nTail - m;
                    nHead = m + 1;
            }
        }
        if(nMaxLen > nMax)
            nMax = nMaxLen;
        return nMax;
        
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

    clock_t begin = clock();
    clock_t end;
    double elapsed_secs;
	Solution a;
	int len = a.lengthOfLongestSubstring(s);
	cout << len << endl;
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Run time: " << elapsed_secs << "s" << endl;
    return 0;
}

