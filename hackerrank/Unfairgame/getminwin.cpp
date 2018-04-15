#include<iostream>
#include <ctime>
#include <vector>
#include <string.h>
#include <math.h>
using namespace std;
const int MAXSIZE = 1000000000;
const int MAXPILES = 15;
const int HASHSIZE = MAXSIZE >> 4;
//int res[HASHSIZE] = { 0 };


class Piles {
public:
	int data[MAXPILES];
	int nTotal;
	void copy(int* V, int N) {
		nTotal = N;
		for (int i = 0; i < N; i++)
			data[i] = V[i];
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
	}
};

int gethash(int* V, int N)
{
	int hash = 0;
	for (int i = 0; i < N; i++) {
		hash ^= V[i];
	}
	return hash%HASHSIZE;
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
int newwin(int* V, int N)
{
	int hash = 0;
	for (int i = 0; i < N; i++) {
		hash ^= V[i];
	}
	return (hash == 0) ? -1 : 1;
}

#if 0
int win(int* V, int N)
{
	if (res[gethash(V, N)] != 0)
		return res[gethash(V, N)];

	if (N == 1 && V[0] > 0)
	{
		res[gethash(V, 1)] = 1;
		return 1;
	}
	else if (N == 1) {
		res[gethash(V, 1)] = -1;
		return -1;
	}
	else if (N == 2) {
		return (V[0] == V[1]) ? -1 : 1;
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
		for (int j = i; j < N - 1; j++)
			Vt[j] = Vt[j + 1];
		Vt[N - 1] = 0;
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
#endif
const int POWER = 1000;

bool getnext(int *V, int n)
{
	int iIndex = 0;
	if (V[iIndex] + 1 < POWER) {
		V[iIndex] += 1;
	}
	else {
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

int gettotal(int* V, int N)
{
		int t = 0;
		for (int i = 0; i < N; i++) {
			t += V[i];
		}
		return t;
}

int getminwin(int *V, int N)
{
	clock_t begin = clock();
	clock_t end;
	double elapsed_secs;
	int ret = 0;
#if 1
	int result = 1;
	int *Vr = new int[N];
	bool bFindE = false;
	int nMaxIndex2 = MAXSIZE;
	int before = gettotal(V, N);
	int start = before % 2;
	for (int id = start; id < nMaxIndex2 && !bFindE; id+=2) {
		vector<Piles> rest = amountnext(N, id);
		for (int j = 0; j < rest.size(); j++) {
			rest[j].assign(Vr);
			for (int i = 0; i < N; i++) {
				Vr[i] = V[i] + Vr[i];
			}
			result = newwin(Vr, N);
			if (result == -1) {
#if 1
				for (int i = 0; i < N; i++) {
					cout << Vr[i];
					if (i != N - 1)
						cout << ",";
				}
				cout << endl;
#endif
				bFindE = true;
				ret = id;
				break;
			}
		}
	}
#else
	ret = POWER;
	int before = gettotal(V, N);
	do {
		int result = newwin(V, N);
		if (result == -1) {
			int rettmp = gettotal(V, N) - before;
			if (rettmp < ret) {
				cout << "get one " << rettmp << endl;
				ret = rettmp;
			}
		}
	} while (getnext(V, N));
#endif
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Run time: " << elapsed_secs << "s" << endl;
	return ret;
}

double secs = 0.f;

const int MAX_LEN = 50;
typedef struct Data {
	int cur;
	int history[MAX_LEN];
	int number;
	Data() {
		number = 0;
	}
} DATA;

int gettotal(DATA* V, int N) {
	unsigned int t = 0;
	for (int i = 0; i < N; i++) {
		t += V[i].cur;
		if (t > 0)
			return 1;
	}
	return 0;
}


void bubblesort(DATA *V, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++) {
			if (V[j].cur > V[i].cur) {
				DATA iMax = V[i];
				V[i] = V[j];
				V[j] = iMax;
			}
		}
	}
}

int getminwinex(int *V, int N)
{
	int ret = 0;
	DATA *ems = new DATA[N];
	for (int i = 0; i < N; i++) {
		ems[i].cur = V[i];
	}
	bubblesort(ems, N);
	do {
		int iPower = pow(2,int(log2(ems[0].cur)));
		int iNum = 0;
		int iLast = 0;
		for (int i = 0; i < N; i++) {
			if (ems[i].cur >= iPower) {
				iNum++;
				ems[i].cur -= iPower;
				ems[i].history[ems[i].number] = iPower;
				iLast = i;
			}
			else
				ems[i].history[ems[i].number] = 0;
			ems[i].number += 1;
		}
		if (iNum % 2 && iNum < N) {
			ret += iPower - ems[iLast + 1].cur;
			ems[iLast + 1].cur = 0;
		}
		else if (iNum % 2) {
			for (int i = 0; i < N; i++) {
				ems[i].cur += iPower;
				if(ems[i].number > 0)
					ems[i].number -= 1;
			}			
			while (ems[1].number >0) {
				bool bFind = false;
				for (int i = 0; i < N;i++) {
					if (ems[i].history[ems[i].number - 1] == (iPower << 1)) {
						bFind = true;
						break;
					}
				}
				if (!bFind)
					break;

				iPower = (iPower << 1);
				for (int i = 0; i < N; i++) {
					ems[i].cur += ems[i].history[ems[i].number - 1];
					ems[i].number -= 1;
				}
			}
			bubblesort(ems, N);
			ret += (iPower << 1) - ems[1].cur;
			ems[1].cur = (iPower << 1);
		}
		bubblesort(ems, N);
	} while(gettotal(ems, N));
	delete[] ems;
	return ret;
}