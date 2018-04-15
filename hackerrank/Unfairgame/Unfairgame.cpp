// Unfairgame.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"


#include<iostream>
#include <ctime>
#include <vector>
#include <string.h>
using namespace std;
extern int getminwinex(int *V, int N);

#if 0
int res1[100][100][100] = { 0 };
int res[100 * 100 * 100 * 100 ] = { 0 };


const int POWER = 100;

int getindex(int* V, int N)
{
	int index = 0;
	int power = 1;
	for (int i = 0; i < N; i++) {
		index += V[N - i - 1] * power;
		power *= POWER;
	}
	return index;
}

class Piles {
public:
	int data[15];
	int nTotal;
	int index;
	void copy(int* V, int N) {
		nTotal = N;
		for (int i = 0; i < N; i++)
			data[i] = V[i];
		index = getindex(V, N);
	}
	void assign(int *V) {
		for (int i = 0; i<nTotal; i++)
			V[i] = data[i];
	}
	bool greater(int* V, int N) {
		if (nTotal != N)
			return false;
		bool bGreater = true;
		for (int i = 0; i < N; i++) {
			if (V[i] > data[i]) {
				return false;
			}
		}
		return bGreater;
	}

	bool less(int* V, int N) {
		if (nTotal != N)
			return false;
		for (int i = 0; i < N; i++) {
			if (V[i] < data[i]) {
				return false;
			}
		}
		return true;
	}
	void output() {
		for (int i = 0; i < nTotal; i++) {
			cout << data[i];
			if (i != nTotal - 1)
				cout << ",";
		}
		cout << endl;
	}
	Piles() {
		nTotal = 0;
		index = 0;
	}
};

vector<Piles> totalres[400];
vector<Piles> reshash;

void getremain(int number, int* V, int N)
{
	int remain = number;
	for (int i = 1; i <= N; i++) {
		V[N - i] = remain % POWER;
		remain -= V[N - i];
		remain /= POWER;
	}	
}

int gettotal(int* V, int N) {
	int t = 0;
	for (int i = 0; i < N; i++) {
		t += V[i];
	}
	return t;
}

void genwin()
{
#if 1
	int nMax = 0;
	int nMaxTotal = 0;
	int nCount = 0;
		for (int j = 1; j < 100; j++)
			for (int k = j; k < 100; k++)
			{
				int V[] = { k, j };
				if (j == k) {					
					res[getindex(V, 2)] = -1;
				} else {
					res[getindex(V, 2)] = 1;
				}
			}

		bool bSkip = false;
		for (int i = 1; i < 100; i++) {	
			for (int j = i; j < 100; j++) {
				for (int k = j; k < 100; k++)
				{
					int V[] = { k, j, i };
					bool bWin = false;
					for (int m = 0; m < i; m++) {
						int V1[] = { k, j, m };
						if (m > 0) {
							if (res[getindex(V1, 3)] == -1) {
								res[getindex(V, 3)] = 1;
								bWin = true;
								break;
							}
						}
						else {
							int V1[] = { k, j };
							if (res[getindex(V1, 2)] == -1) {
								res[getindex(V, 3)] = 1;
								bWin = true;
								break;
							}
						}

					}
					if (!bWin) {
						for (int m = i; m < j; m++) {
							int V1[] = { k, m, i };
							if (res[getindex(V1, 3)] == -1) {
								res[getindex(V, 3)] = 1;
								bWin = true;
								break;
							}
						}
						for (int m = 0; m < i; m++) {
							int V1[] = { k, i, m };
							if (m > 0) {
								if (res[getindex(V1, 3)] == -1) {
									res[getindex(V, 3)] = 1;
									bWin = true;
									break;
								}
							}
							else {
								int V2[] = { k, i };
								if (res[getindex(V2, 2)] == -1) {
									res[getindex(V, 3)] = 1;
									bWin = true;
									break;
								}
							}
						}
					}
					if (!bWin) {
						for (int m = j; m < k; m++) {
							int V1[] = { m, j, i };
							if (res[getindex(V1, 3)] == -1) {
								res[getindex(V, 3)] = 1;
								bWin = true;
								bSkip = true;
								break;
							}
						}
						for (int m = i; m < j; m++) {
							int V1[] = { j, m, i };
							if (res[getindex(V1, 3)] == -1) {
								res[getindex(V, 3)] = 1;
								bWin = true;
								bSkip = true;
								break;
							}
						}
						for (int m = 0; m < i; m++) {
							int V1[] = { j, i, m };
							if (m > 0) {
								if (res[getindex(V1, 3)] == -1) {
									res[getindex(V, 3)] = 1;
									bWin = true;
									bSkip = true;
									break;
								}
							}
							else {
								int V2[] = { j, i };
								if (res[getindex(V2, 2)] == -1) {
									res[getindex(V, 3)] = 1;
									bWin = true;
									bSkip = true;
									break;
								}
							}
						}
					}
					if (bSkip) {
						bSkip = false;
						break;
					}
					if (!bWin) {
						res[getindex(V, 3)] = -1;
						Piles dat;
						dat.copy(V, 3);
						totalres[gettotal(V, 3)].push_back(dat);
						//if(i >= 3 && i <= 3 && j ==5)
						//cout << nCount << ": " << k << "," << j << "," << i << endl;
						//nCount++;
					}
				}
			}
		}
		int nTotal = 0;
#if 1
	for (int i = 1; i < 100; i++)
		for (int j = i; j < 100; j++)
			for (int k = j; k < 100; k++)
				for (int h = k; h < 100; h++)
			{
				nTotal++;
				int V[] = { h, k, j, i };
				bool bWin = false;
				for (int m = 0; m < i; m++) {
					int V1[] = { h, k, j, m };
					if (m > 0) {
						if (res[getindex(V1, 4)] == -1) {
							res[getindex(V, 4)] = 1;
							bWin = true;
							break;
						}
					}
					else {
						int V1[] = { h, k, j };
						if (res[getindex(V1, 3)] == -1) {
							res[getindex(V, 4)] = 1;
							bWin = true;
							break;
						}
					}

				}
				if (!bWin) {
					for (int m = i; m < j; m++) {
						int V1[] = { h, k, m, i };
						if (res[getindex(V1, 4)] == -1) {
							res[getindex(V, 4)] = 1;
							bWin = true;
							break;
						}
					}
					for (int m = 0; m < i; m++) {
						int V1[] = { h, k, i, m };
						if (m > 0) {
							if (res[getindex(V1, 4)] == -1) {
								res[getindex(V, 4)] = 1;
								bWin = true;
								break;
							}
						}
						else {
							int V2[] = { h, k, i };
							if (res[getindex(V2, 3)] == -1) {
								res[getindex(V, 4)] = 1;
								bWin = true;
								break;
							}
						}
					}
				}
				if (!bWin) {
					for (int m = j; m < k; m++) {
						int V1[] = { h, m, j, i };
						if (res[getindex(V1, 4)] == -1) {
							res[getindex(V, 4)] = 1;
							bWin = true;
							break;
						}
					}
					for (int m = i; m < j; m++) {
						int V1[] = { h, j, m, i };
						if (res[getindex(V1, 4)] == -1) {
							res[getindex(V, 4)] = 1;
							bWin = true;
							break;
						}
					}
					for (int m = 0; m < i; m++) {
						int V1[] = { h, j, i, m };
						if (m > 0) {
							if (res[getindex(V1, 4)] == -1) {
								res[getindex(V, 4)] = 1;
								bWin = true;
								break;
							}
						}
						else {
							int V2[] = { h, j, i };
							if (res[getindex(V2, 3)] == -1) {
								res[getindex(V, 4)] = 1;
								bWin = true;
								break;
							}
						}
					}
				}

				if (!bWin) {
					for (int m = k; m < h; m++) {
						int V1[] = {m, k, j, i };
						if (res[getindex(V1, 4)] == -1) {
							res[getindex(V, 4)] = 1;
							bWin = true;
							break;
						}
					}
					for (int m = j; m < k; m++) {
						int V1[] = { k, m, j, i };
						if (res[getindex(V1, 4)] == -1) {
							res[getindex(V, 4)] = 1;
							bWin = true;
							break;
						}
					}
					for (int m = i; m < j; m++) {
						int V1[] = { k, j, m, i };
						if (res[getindex(V1, 4)] == -1) {
							res[getindex(V, 4)] = 1;
							bWin = true;
							break;
						}
					}
					for (int m = 0; m < i; m++) {
						int V1[] = { k, j, i, m };
						if (m > 0) {
							if (res[getindex(V1, 4)] == -1) {
								res[getindex(V, 4)] = 1;
								bWin = true;
								break;
							}
						}
						else {
							int V2[] = { k, j, i };
							if (res[getindex(V2, 3)] == -1) {
								res[getindex(V, 4)] = 1;
								bWin = true;
								break;
							}
						}
					}
				}
				if (!bWin) {
					res[getindex(V, 4)] = -1;
					nCount++;
					Piles dat;
					dat.copy(V, 4);
					totalres[gettotal(V, 4)].push_back(dat);
					if (totalres[gettotal(V, 4)].size() > nMax) {
						nMax = totalres[gettotal(V, 4)].size();
						nMaxTotal = gettotal(V, 4);
					}
				}

			}
#endif

#endif
	cout << "Max Total/MaxValue " << nMax << "/" << nMaxTotal << endl;
	cout << "Total: " << nCount << "/" << nTotal << endl;
	/*
	for (int i = 0; i < nMax; i++) {			
		totalres[nMaxTotal][i].output();
	}*/
}

int gethash(int* V, int N)
{
	int hash = 0;
	for (int i = 0; i < N; i++) {
		hash ^= V[i];
	}
	return hash;
}

int win(int* V, int N)
{
	if (res[gethash(V,N)] != 0)
		return res[gethash(V, N)];

	if (N == 1 && V[0] > 0) 
		{
			res[V[0]] = 1;
			return 1;
		}
	else if (N == 1) {
		res[V[0]] = -1;
		return -1;
	}
	for (int i = 0; i < N; i++) {
		int *Vt = new int[N];
		for (int j = 0; j < N; j++)
			Vt[j] = V[j];
		if (Vt[i] > 1) {
			for (int j = 1; j < V[i]; j++) {
				Vt[i] = j;
				int iScore = -win(Vt, N);
				if (iScore > 0) {
					res[gethash(V, N)] = 1;
					return 1;
				}
			}
		}
		for (int j = i; j < N-1; j++)
			Vt[j] = Vt[j + 1];
		Vt[N-1] = 0;		
		int Nt = N - 1;
		int iScore = -win(Vt, Nt);
		if (iScore > 0) {
			res[gethash(V, N)] = 1;
			return 1;
		}
	}
	res[gethash(V, N)] = -1;

	return -1;
}

bool greater(int* V, int* Vt, int N)
{
	bool bGreater = true;
	for (int i = 0; i < N; i++) {
		if (V[i] > Vt[i]) {
			return false;
		}
	}
	return bGreater;
}

bool getnext(int *V, int n)
{	
	int iIndex = 0;
	if (V[iIndex] + 1 < POWER) {
		V[iIndex] += 1;
	} else {
		while (iIndex + 1 < n
			&& V[iIndex + 1] + 1 == POWER) {			
			iIndex += 1;
		}
		if (iIndex + 1 < n) {
			V[iIndex + 1] += 1;
			for (int i = iIndex; i >= 0; i--) {
				V[i] = V[iIndex + 1];
			}
		}
		else
			return false;		
	}
	return true;
}


int nHash[POWER] = { 0 };

bool isWin(int* Vd, int n, int *V, int m)
{
	int nSame = 0;	
	memset(nHash, 0, sizeof(int)*POWER);
	for (int i = 0; i < n; i++) {
		nHash[Vd[i]] += 1;
	}
	for (int i = 0; i < m; i++) {
		if (nHash[V[i]]) {
			nHash[V[i]] -= 1;
			nSame++;
		}
	}
	if (nSame == m - 1)
		return true;
	else
		return false;
}

int gennext(int nPiles)
{
	int nBefore = reshash.size();
	int *V = new int[nPiles];
	int *VStart = new int[nPiles - 1];
	for (int i = 0; i < nPiles; i++) {
		V[i] = 1;
		if(i<nPiles-1)
			VStart[i] = 1;
	}
	
	int iStart = getindex(VStart, nPiles - 1);
	int nStartIndex = 0;
	for (int i = 0; i < reshash.size(); i++) {		
		if (reshash[i].index >= iStart) {
			nStartIndex = i;
			break;
		}
	}
	cout << "start at " << nStartIndex << endl;
	do {
		bool bWin = false;
		int index = getindex(V, nPiles);
		for (int i = reshash.size() - 1; i >= nStartIndex; i--) {
			if (isWin(reshash[i].data, reshash[i].nTotal, V, nPiles)) {
				bWin = true;
				break;
			}
		}
		if (!bWin) {
			Piles dat;
			dat.copy(V, nPiles);
			reshash.push_back(dat);
			//dat.output();
			int nc = reshash.size() - nBefore;
			if(!(nc % 2000))
				cout << nc << endl;
			Piles dat1;
			dat1.copy(V, nPiles);
			totalres[gettotal(V, 3)].push_back(dat1);
		}
	} while (getnext(V, nPiles));
	delete[] VStart;
	delete[] V;
	return reshash.size() - nBefore;
}

void gen2piles()
{
	for (int j = 1; j < POWER; j++)
	{
		int V[] = { j, j };
		Piles dat;
		dat.copy(V, 2);
		reshash.push_back(dat);
	}
}

vector<Piles> amountnext(int N, int Total)
{
	vector<Piles> res;
	if (N <= 1) {
		int V[] = { Total };
		Piles dat;
		dat.copy(V, 1);
		res.push_back(dat);
		return res;
	}
	if (Total <= 0) {
		int *V = new int[N];
		memset(V, 0, sizeof(int)*N);
		Piles dat;
		dat.copy(V, N);
		res.push_back(dat);
		delete[] V;
		return res;
	}
	int *V = new int[N];
	for (int i = 0; i <= Total; i++)
	{
		V[0] = i;
		vector<Piles> restmp = amountnext(N - 1, Total - i);
		for (int j = 0; j < restmp.size(); j++) {
			Piles dat;
			restmp[j].assign(V + 1);
			dat.copy(V, N);
			res.push_back(dat);
		}
	}
	delete[] V;
	return res;
}
#endif

int main(void) {
#if 0
	clock_t begin = clock();
	clock_t end;
	double elapsed_secs;
	bool bFind = false;
	int N = 5;
	int V[5];
	V[0] = 10;
	V[1] = 5;
	V[2] = 4;
	V[3] = 1;
	V[4] = 2;

#if 0
	genwin();
#if 0
	gen2piles();
	int nsize = gennext(3);
	cout << "Total " << nsize << endl;
	//nsize = gennext(4);
	//cout << "Total " << nsize << endl;
	//nsize = gennext(5);
	//cout << "Total " << nsize << endl;
#endif
	int totalV1 = gettotal(V, N);
	int VMax1[4] = { 99,99,99,99 };
	int nMaxIndex1 = gettotal(VMax1, N);
#if 0
	for (int id = totalV1; id > 0; id--) {
		for (int j = 0; j < totalres[id].size(); j++) {
			if (totalres[id][j].less(V, N)) {
				cout << totalV1 - id<< endl;
				totalres[id][j].output();
				bFind = true;
				//end = clock();
				//elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
				//cout << "Run time: " << elapsed_secs << "s" << endl;
				//return 1;
			}
		}
		if (bFind) {
			end = clock();
			elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			cout << "Run time: " << elapsed_secs << "s" << endl;
			return 1;
		}
	}
#endif
	for (int id = totalV1; id < nMaxIndex1; id++) {
		for (int j = 0; j < totalres[id].size(); j++) {
			if (totalres[id][j].greater(V, N)) {
				cout << id - totalV1 << endl;
				totalres[id][j].output();
				bFind = true;
				//end = clock();
				//elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
				//cout << "Run time: " << elapsed_secs << "s" << endl;
				//return 1;
			}
		}
		if (bFind) {
			end = clock();
			elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			cout << "Run time: " << elapsed_secs << "s" << endl;
			return 1;
		}
	}
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Run time: " << elapsed_secs << "s" << endl;
	return -1;
#endif
	int result = 1;
	int *Vr = new int[N];
	bool bFindE = false;
	int VMax2[4] = { 99,99,99,99 };
	int nMaxIndex2 = gettotal(VMax2, N);
#if 1
	for (int id = 0; id < nMaxIndex2 && !bFindE; id++) {
		vector<Piles> rest = amountnext(N, id);
		for (int j = 0; j < rest.size(); j++) {
			rest[j].assign(Vr);
			for (int i = 0; i < N; i++) {
				Vr[i] = V[i] + Vr[i];
			}
			result = win(Vr, N);
			if (result == -1) {
				bFindE = true;
				cout << id << endl;
				for (int i = 0; i < N; i++) {
					cout << Vr[i];
					if (i != N - 1)
						cout << ",";
				}
				cout << endl;
				break;
			}
		}
	}

	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Run time: " << elapsed_secs << "s" << endl;
	return 1;
#endif 
	int nIndex = getindex(V, N);
	int *Vt = new int[N];
	int VMax[4] = { 60,60,60,13};
	int nMaxIndex = getindex(VMax, N);
	int nMin = 500;
	int totalV = gettotal(V, N);
	while (nIndex < nMaxIndex) {
		getremain(nIndex++, Vt, N);		
		if (greater(V, Vt, N)) {
			result = win(Vt, N);
			if (result == -1) {
				int total = gettotal(Vt, N);
				if (total < nMin) {
					nMin = total;
					for (int i = 0; i < N; i++)
						Vr[i] = Vt[i];
					if (total == totalV) {
						break;
					}
				}
			}
		}
			//result = res[getindex(Vt, 3)];
	}
	cout << nMin - totalV << endl;
	for (int i = 0; i < N; i++) {
		cout << Vr[i];
		if (i != N - 1)
			cout << ",";
	}
	cout << endl;
	//V[3] = 1;
	//int result = win(V, 3);
	//cout << result << endl;	
#if 0
	int nCount = 0;
	for (int i = 0; i < 100; i++)
		for (int j = i; j < 100; j++)
			for (int k = j; k < 100; k++)
				for (int h = k; h < 100; h++){
				int V[4];
				V[0] = h;
				V[1] = k;
				V[2] = j;
				V[3] = i;
				if (i == 0 && j == 0 && k == 0)
					win(V, 1);
				else if (i == 0 && j == 0)
					win(V, 2);
				else if (i == 0)
					win(V, 3);
				else
				{
					int rv = win(V, 4);
					if (rv == -1) {
						if (!bFind && i >= 1 && j >= 4 && k >= 5 && h >= 10) {
							cout << nCount << ": " << h << "," << k << "," << j << "," << i << endl;
							bFind = true;
						}
						nCount++;
					}
				}

			}
#endif 
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Run time: " << elapsed_secs << "s" << endl;
	return 1;
	//Helpers for input and output
#endif
	int test;
	vector<int> res;
	cin >> test;	
	for (int t = 0; t<test; t++) {

		int N;
		cin >> N;

		int *V = new int[N];
		for (int i = 0; i < N; i++) {
			cin >> V[i];
		}

		int result = getminwinex(V, N);
		res.push_back(result);
		delete[] V;
	}
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << endl;
	//cout << "Run time " << secs << endl;
	return 0;
}
