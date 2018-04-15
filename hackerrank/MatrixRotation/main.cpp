#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

// Do the in-place matrix rotation
void matrixrotate(int matrix[][300], int left, int top, int w, int h, int n)
{
    int numbers[2*300+2*300-4] = {0};
    while(w > 0 && h > 0)
    {
        // copy to numbers
        // Front row
        int len = 0;
        for(int i=0; i<w-1; i++)
            numbers[len++] = matrix[top][left+i];

        // Right column
        for(int i=0; i<h-1; i++)
            numbers[len++] = matrix[top+i][left+w-1];

        // Bottom row
        for(int i=w-1; i>0; i--)
            numbers[len++] = matrix[top+h-1][left+i];

        // Left column
        for(int i=h-1; i>0; i--)
            numbers[len++] = matrix[top+i][left];


        int nindex = n % len;
        // Front row
        for(int i=0; i<w-1; i++)
            matrix[top][left+i] = numbers[(nindex++)%len];

        // Right column
        for(int i=0; i<h-1; i++)
            matrix[top+i][left+w-1] = numbers[(nindex++)%len];

        // Bottom row
        for(int i=w-1; i>0; i--)
            matrix[top+h-1][left+i] = numbers[(nindex++)%len];

        // Left column
        for(int i=h-1; i>0; i--)
            matrix[top+i][left] = numbers[(nindex++)%len];

        left += 1;
        top += 1;
        w -= 2;
        h -= 2;
    }
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int matrix[300][300] = {0};
    int M,N,R;
    string line;
    int nline = 0;
    while(getline(cin, line)) {
        int sz = line.size();
        if(sz<1)
            break;
        vector<string> tokens = split(line, ' ');
        if(!nline) {
            M = atoi(tokens[0].c_str());
            N = atoi(tokens[1].c_str());
            R = atoi(tokens[2].c_str());
        } else {
            for(int i=0; i<tokens.size();i++)
                matrix[nline-1][i] = atoi(tokens[i].c_str());
        }
        nline++;
    }
    int n = R;
    matrixrotate(matrix, 0, 0, N, M, R);
    for(int i=0; i<M; i++) {
        for(int j=0;j<N;j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    return 0;
}
