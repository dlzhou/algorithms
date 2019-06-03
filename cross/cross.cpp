#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <time.h>
#include <map>
using namespace std;

vector<vector<int> > genMoves(vector<int> arrs)
{
    vector<vector<int> > outputs;
    int i=0;
    int index = -1;
    for(int i=0; i<arrs.size(); i++)
    {
        if(arrs[i] == 0){
            index = i;
            break;
        }
    }
    if(index - 2 >=0 && arrs[index - 2] == 1) {
        vector<int> res = arrs;
        res[index-2] = 0;
        res[index] = 1;
        outputs.push_back(res);
    }
    if(index - 1 >=0 && arrs[index - 1] == 1) {
        vector<int> res = arrs;
        res[index-1] = 0;
        res[index] = 1;
        outputs.push_back(res);
    }
    if(index + 1 < arrs.size() && arrs[index + 1] == 2) {
        vector<int> res = arrs;
        res[index+1] = 0;
        res[index] = 2;
        outputs.push_back(res);
    }
    if(index + 2 < arrs.size() && arrs[index + 2] == 2) {
        vector<int> res = arrs;
        res[index+2] = 0;
        res[index] = 2;
        outputs.push_back(res);
    } 
    return outputs;   
}

bool hasDone(vector<int> arrs)
{
    int nMid = arrs.size()/2;
    for(int i=0; i<arrs.size(); i++) {
        if(i < nMid && arrs[i] != 2)
            return false; 
        if(i == nMid && arrs[i] != 0)
            return false;
        if(i > nMid && arrs[i] != 1)
            return false;
    }
    return true;
}

vector<vector<vector<int> > > overallBest;
vector<vector<int> > bestMoves;
int minSize = 9999;
bool search(vector<int> arrs, int depth)
{
    bestMoves.push_back(arrs);
    vector<vector<int> > movs = genMoves(arrs);
    if(!movs.size())
     {
         if(hasDone(arrs)) {
            if(depth + 1 < minSize) {
               minSize = depth + 1;
           }
            overallBest.push_back(bestMoves);
            bestMoves.pop_back();
            return true;
         } else {
            bestMoves.pop_back();
            return false;
          }
     }
    bool bDone = false;
    for(int i=0; i<movs.size(); i++){
        if(search(movs[i], depth+1)) {
           bDone = true;
           bestMoves.clear();
           bestMoves.push_back(arrs);
        }
    }
    if(!bDone)
    {
        bestMoves.pop_back();
        return false;
    } else
        return true;
}


int main()
{
    vector<int> tests;

    int test;
    cin >> test;

    for(int i=0; i<test/2; i++){
        tests.push_back(1);
    }
    tests.push_back(0);
    for(int i=test/2+1; i<test; i++){
        tests.push_back(2);
    }
    search(tests, 0);
    cout << "minium step is " << minSize << endl;
    for(int i=0; i<overallBest.size(); i++){
        cout << "s size is " << overallBest[i].size() << endl;
        for(int n=0; n<overallBest[i].size(); n++) {
            for(int m=0; m<overallBest[i][n].size(); m++)
            if(m<overallBest[i][n].size()-1)
                cout << overallBest[i][n][m];
            else
                cout << overallBest[i][n][m] << endl;
        }
    }
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
            }
            else {
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
    clock_t begin = clock();
    clock_t end;
    double elapsed_secs;
    vector<vector<int> > out = a.threeSum(tests);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Run time: " << elapsed_secs << "s" << endl;
    cout << "result size is " << out.size() << endl;
#if 0
    for(int i=0; i<out.size(); i++) {
        for(int j=0; j<out[i].size(); j++){
            if(j!=out[i].size()-1)
	            cout << out[i][j] << "," ;
            else
                cout << out[i][j] << endl;
        }
    }
#endif
#endif
    return 0;
}

