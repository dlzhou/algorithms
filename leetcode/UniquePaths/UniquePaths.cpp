// UniquePaths.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

class Solution {
public:

    static int uniquePaths(int m, int n) {
		int mat[102][102] = {0};
		mat[1][1] = 1;
		for(int i=1; i<=n;i++)
			for(int j=1; j<=m; j++) {
			{
				if(i==1 && j==1)
					continue;
				mat[j][i] = mat[j][i-1] +mat[j-1][i];
			}
		}
		return mat[m][n];
    }

    static int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
 		int mat[102][102] = {0};
		mat[1][1] = 1;
		int n = obstacleGrid[0].size();
		int m = obstacleGrid.size();
		for(int i=1; i<=n;i++)
			for(int j=1; j<=m; j++) {
			{
				if(obstacleGrid[j-1][i-1] == 1) {
					if(j==1 && i==1)
						mat[1][1] = 0;						
					continue;
				}
				if(i==1 && j==1)
					continue;
				mat[j][i] = mat[j][i-1] +mat[j-1][i];
			}
		}
		return mat[m][n];       
    }
};

int main()
{
	//int m,n;
	//cin >> m;
	//cin >> n;
	//cout << Solution::uniquePaths(m, n) << endl;
	vector<vector<int>> t;
	vector<int> t1;
	t1.push_back(1);
	t.push_back(t1);
	cout << Solution::uniquePathsWithObstacles(t) << endl;
	return 0;
}

