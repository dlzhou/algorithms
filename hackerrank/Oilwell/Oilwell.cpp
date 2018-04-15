// Oilwell.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#ifndef __int64
#define __int64 long long
#endif
using namespace std;
#define USE_HASH 0
const int MAX_SIZE = 50;
int MAX_HASH = 0x800000;
int dists[MAX_SIZE*MAX_SIZE][MAX_SIZE*MAX_SIZE] = { 0 };

unsigned __int64 randhash[MAX_SIZE][MAX_SIZE];
class Data {
public:
	int dist;
	int nodes[30];
	int nodescol[30];
	int maxdists[30];
	int nodesnum;
	int nodesnumcol;
	Data():dist(0), nodesnum(0) {

	}
};

Data* myhash = NULL;// [MAX_HASH];
class Dist {
public:
	int iFir;
	int iSec;
	int dist;
	Dist() : iFir(0), iSec(0), dist(0) {}
};

int calcdist(int ifir, int isec, int r, int c)
{
	int ifr = ifir / c;
	int ifc = ifir % c;
	int isr = isec / c;
	int isc = isec % c;
	int ir = abs(ifr - isr);
	int ic = abs(ifc - isc);

	return std::max(ir, ic);
}

void sortdist(Dist dists[], int index)
{
	for (int i = 0; i < index; i++)
	{
		for (int j = i + 1; j < index; j++) {
			if (dists[j].dist < dists[i].dist) {
				Dist iMin = dists[i];
				dists[i] = dists[j];
				dists[j] = iMin;
			}
		}
	}
}

vector<int> getmaxdist(Dist dists[], int index)
{

	int max = dists[index-1].dist;
	vector<int> ret;
	ret.push_back(index - 1);
	for (int i = index - 2; i > 0 && dists[i].dist == max; i--) {
		ret.push_back(i);
	}
	return ret;
}

int totaldist(Dist dists[], int index, int inode)
{
	int dist = 0;
	for (int i = 0; i < index; i++) {
		if(inode == dists[i].iFir 
		|| inode == dists[i].iSec)
			dist += dists[i].dist;
	}
	return dist;
}

void removedist(Dist dists[],  int& index, int inode)
{
	for (int i = 0; i < index; i++) {
		if (inode == dists[i].iFir
			|| inode == dists[i].iSec) {
			if (i + 1 < index) {
				for (int j = i; j < index - 1;j++)
					dists[j] = dists[j + 1];
				i = i - 1;
			}
			index--;
		}
	}
}

void removeoils(int oils[], int& num, int inode)
{
	for (int i = 0; i < num; i++) {
		if (oils[i] == inode) {
			if (i + 1 < num) {
				for (int j = i; j < num - 1; j++)
					oils[j] = oils[j + 1];
				i = i - 1;
			}
			num--;
			return;
		}
	}
}

bool bfind(vector<int> src, int dst)
{
	for (int i = 0; i < src.size(); i++)
		if (src[i] == dst)
			return true;
	return false;
}

int mincost(int blocks[][MAX_SIZE], int r, int c)
{

	int oils[MAX_SIZE*MAX_SIZE] = { 0 };
	int nums = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (blocks[i][j] == 1)
				oils[nums++] = i*c + j;
		}
	Dist dists[MAX_SIZE*MAX_SIZE / 2];
	int distindex = 0;
	for (int i = 0; i < nums; i++)
		for (int j = i + 1; j < nums; j++) {
				int ds = calcdist(oils[i], oils[j], r, c);
				Dist dis;
				dis.dist = ds;
				dis.iFir = oils[i];
				dis.iSec = oils[j];
				dists[distindex++] = dis;
		}
	int dist = 0;
	while (nums > 1) {
#if 0
		int imax = 0;
		int removenode = -1;
		sortdist(dists, distindex);
		for (int i = 0; i < nums; i++) {
			int idt = totaldist(dists, distindex, oils[i]);
			if (idt > imax) {
				imax = idt;
				removenode = oils[i];
			}
		}
		for (int i = distindex - 1; i >= 0; i--) {
			if (dists[i].iFir == removenode
				|| dists[i].iSec == removenode) {
				dist += dists[i].dist;
				break;
			}
		}
		removedist(dists, distindex, removenode);
		removeoils(oils, nums, removenode);
		cout << removenode / c << "," << removenode % c << endl;
#else
		sortdist(dists, distindex);
		vector<int> dss = getmaxdist(dists, distindex);
		int imaxdis = 0;
		int removenode = -1;
		int maxdist = 0;
		vector<int> mdis;

		for (int i = 0; i < dss.size(); i++) {
			Dist ds = dists[dss[i]];
			maxdist = ds.dist;
			int ids = totaldist(dists, distindex, ds.iFir);
			int ids2 = totaldist(dists, distindex, ds.iSec);
			if (ids == imaxdis) {
				if (!bfind(mdis, ds.iFir)) mdis.push_back(ds.iFir);
			}
			if (ids2 == imaxdis) {
				if (!bfind(mdis, ds.iSec)) mdis.push_back(ds.iSec);
			}
			if (ids > imaxdis) {
				removenode = ds.iFir;
				imaxdis = ids;
				mdis.clear();
				if (!bfind(mdis, ds.iFir))
					mdis.push_back(ds.iFir);
			}
			if (ids2 > imaxdis) {
				removenode = ds.iSec;
				imaxdis = ids2;
				mdis.clear();
				if (!bfind(mdis, ds.iSec)) mdis.push_back(ds.iSec);
			}
		}
		if (mdis.size() > 1) {
			cout << "greater 1" << endl;
		}
		removedist(dists, distindex, removenode);
		cout << maxdist << ": " << removenode / c << "," << removenode % c << endl;
		dist += maxdist;
		nums--;
#endif
	}
	return dist;
}

int getmaxdist(Dist dists[], int index, int inode)
{

	int maxdist = 0;
	for (int i = index - 1; i >= 0; i--) {
		if ((dists[i].iFir == inode || dists[i].iSec == inode) && dists[i].dist > maxdist) {
			maxdist = dists[i].dist;
			return maxdist;
		}
	}
	return maxdist;
}
unsigned int gethash(int oils[], int num, int c)
{
	unsigned __int64 ihash = 0;
	for (int i = 0; i < num; i++)
		ihash ^= randhash[oils[i] / c][oils[i] %c];
	return (unsigned int)ihash;
}

void copyto(int *src, int *back, int inum)
{
	for (int i = 0; i < inum; i++)
		back[i] = src[i];
}


void copyfrom(int *src, int *back, int inum)
{
	for (int i = 0; i < inum; i++)
		src[i] = back[i];
}

void copyto(Dist *src, Dist *back, int inum)
{
	for (int i = 0; i < inum; i++)
		back[i] = src[i];
}


void copyfrom(Dist *src, Dist *back, int inum)
{
	for (int i = 0; i < inum; i++)
		src[i] = back[i];
}


int mincostrec(int blocks[][MAX_SIZE], int r, int c, vector<int>& inodes, vector<int>& maxdists)
{
	int nums = 0;
	int *oils = new int[r*c*sizeof(int)];
	//memset(oils, 0, r*c*sizeof(int));
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (blocks[i][j] == 1)
				oils[nums++] = i*c + j;
		}
	if (nums < 1) {
		delete[] oils;
		return 0;
	}
	if (nums == 1) {
		inodes.push_back(oils[nums-1]);
		maxdists.push_back(0);
		delete[] oils;
		return 0;
	}
#if 1
	int nhash = gethash(oils, nums, c) % MAX_HASH;
	bool bFalseAlarm = false;
	if (myhash[nhash].dist != 0) {
		if (nums == myhash[nhash].nodesnumcol)
			for (int i = 0; i < myhash[nhash].nodesnumcol; i++) {
				if (oils[i] != myhash[nhash].nodescol[i]) {
					bFalseAlarm = true;
					//cout << "collision hash" << endl;
					break;
				}
			}
		else 
			bFalseAlarm = true;
		
		if (!bFalseAlarm) {
			for (int i = 0; i < myhash[nhash].nodesnum; i++) {
				inodes.push_back(myhash[nhash].nodes[i]);
				maxdists.push_back(myhash[nhash].maxdists[i]);
			}
			delete[] oils;
			return myhash[nhash].dist;
		}
	}
#endif	
	int distindex = 0;
	Dist *dists = new Dist[nums*nums/2];
	//Dist dists[400];
	for (int i = 0; i < nums; i++)
		for (int j = i + 1; j < nums; j++) {
			int ds = calcdist(oils[i], oils[j], r, c);
			Dist dis;
			dis.dist = ds;
			dis.iFir = oils[i];
			dis.iSec = oils[j];
			dists[distindex++] = dis;
		}
	int mindist = INT16_MAX;
	int minindex = 0;
	int minmaxdist = 0;	
	static int max_num = 0;
	if (!max_num)
		max_num = nums;
	for (int i = 0; i < nums; i++) {
		if(nums == max_num)
			cout << i << "/" << nums << endl;
		sortdist(dists, distindex);
		int dist = 0;
		int nindex = oils[i];
		int maxdist = getmaxdist(dists, distindex, nindex);
		dist += maxdist;
		blocks[nindex / c][nindex%c] = 0;
		vector<int> ichildnodes;
		vector<int> mdists;
		dist += mincostrec(blocks, r, c, ichildnodes, mdists);
		blocks[nindex / c][nindex%c] = 1;
		if (dist < mindist) {
			mindist = dist;
			minindex = nindex;
			minmaxdist = maxdist;
			inodes = ichildnodes;
			maxdists = mdists;
		}
	}
	inodes.push_back(minindex);
	maxdists.push_back(minmaxdist);
#if 1
	myhash[nhash].dist = mindist;
	myhash[nhash].nodesnum = inodes.size();
	myhash[nhash].nodesnumcol = nums; //inodes.size();
	for (int i = 0; i < myhash[nhash].nodesnum; i++) {
		myhash[nhash].nodes[i] = inodes[i];
		myhash[nhash].maxdists[i] = maxdists[i];
	}
	for (int i = 0; i < myhash[nhash].nodesnumcol; i++) {
		myhash[nhash].nodescol[i] = oils[i];
	}
#endif
	delete[] oils;
	delete[] dists;
	return mindist;
}

class PRNG {

	__int64 s;

	__int64 rand64() {

		s ^= s >> 12, s ^= s << 25, s ^= s >> 27;
		return s * 2685821657736338717LL;
	}

public:
	PRNG(__int64 seed) : s(seed) { }

	unsigned __int64 rand() { return (unsigned __int64)rand64(); }
};


void generaterand(int r, int c)
{
	int seeds[] = { 8977, 44560, 54343, 38998,  5731, 95205, 104912, 17020, 728, 10316, 55013, 32803, 12281, 15100,  16645, 255 };
	for (int i = 0; i < r; i++) {
		PRNG rng(seeds[i]);
		for (int j = 0; j < c; j++) {
			randhash[i][j] = rng.rand();
		}
	}
}


int getmaxdist(int dists[][MAX_SIZE*MAX_SIZE], int c, int* visited, int visnums, int inode, int& maxindex)
{
	int maxdist = 0;
	for (int j = 0; j<visnums; j++)
		if(dists[visited[j]][inode] > maxdist) {
				maxdist = dists[visited[j]][inode];
				maxindex = visited[j];
			}
	return maxdist;
}

int getmaxindex(int dists[][MAX_SIZE*MAX_SIZE], int c, int* visited, int visnums, int inode, int& maxindex)
{
	int maxdist = 0;
	for (int j = 0; j<visnums; j++)
		if (dists[visited[j]][inode] > maxdist) {
			maxdist = dists[visited[j]][inode];
			maxindex = j;
		}
	return maxdist;
}

int getmaxdist(int dists[][MAX_SIZE*MAX_SIZE], int c, int* visited, int visnums, int inode, vector<int>& maxindex)
{
	int maxdist = 0;
	for (int j = 0; j<visnums; j++)
		if (dists[visited[j]][inode] > maxdist) {
			maxdist = dists[visited[j]][inode];
			maxindex.clear();
			maxindex.push_back(visited[j]);
		}
		else if (dists[visited[j]][inode] == maxdist) {
			maxindex.push_back(visited[j]);
		}
	return maxdist;
}

int mincostexstart(int* oils, int nums, int* visited, int visnums, int dists[][MAX_SIZE*MAX_SIZE], int r, int c, vector<int> &minnodes)
{
	if (!nums)
		return 0;
	int mindist = INT16_MAX;
	for (int i = 0; i < nums; i++) {
		int tmp = 0;
		int dist = getmaxdist(dists, c, visited, visnums, oils[i], tmp);
		if (dist < mindist) {
			mindist = dist;
			minnodes.clear();
			minnodes.push_back(oils[i]);
		} else if(dist == mindist)
			minnodes.push_back(oils[i]);
	}
	return mindist;
}

int deletedata(int* oils, int& nums, int data)
{
	int index = -1;
	for (int i = 0; i < nums;i++)
		if (oils[i] == data) {
			index = i;
			break;
		}
	for (int i = index; i < nums - 1; i++) {
		oils[i] = oils[i + 1];
	}
	nums--;
	return index;
}

void insertdata(int* oils, int& nums, int index, int data)
{
	for (int i = nums; i > index; i--) {
		oils[i] = oils[i-1];
	}
	oils[index] = data;
	nums++;
}

int mincostex(int blocks[][MAX_SIZE], int r, int c)
{
	int oils[MAX_SIZE*MAX_SIZE] = { 0 };
	int nums = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (blocks[i][j] == 1)
				oils[nums++] = i*c + j;
		}
	if (!nums)
		return 0;
	int distindex = 0;
	for (int i = 0; i < nums; i++)
		for (int j = i + 1; j < nums; j++) {
			int ds = calcdist(oils[i], oils[j], r, c);
			dists[oils[i]][oils[j]] = ds;
			dists[oils[j]][oils[i]] = ds;
		}
	int dist = INT16_MAX;
	int* oils_back = new int[nums];
	int* visited = new int[nums];
	int visitednum = 0;
	bool bExit = false;
	for (int i = 0; i < nums; i++) {
		for (int i = 0; i < nums; i++)
			oils_back[i] = oils[i];
		visitednum = 0;
		int bnums = nums;
		int mindist = 0;
		int index = oils[i];
		while (bnums > 0) {
			int nindex = deletedata(oils_back, bnums, index);
			insertdata(visited, visitednum, 0, index);		
			if (!bnums)
				break;
			vector<int> minnodes;
			int mdist = mincostexstart(oils_back, bnums, visited, visitednum, dists, r, c, minnodes);
			mindist += mdist;
			index = minnodes[0];
		}
		if (mindist < dist) {
			dist = mindist;
		}
	}
	delete[] oils_back;
	delete[] visited;
	return dist;
}


class DistData {
public:
	vector<int> vs;
	int dist;
	DistData(vector<int> s, int d) : vs(s), dist(d) {}
	DistData() : dist(0) {}
};

class NodesStack {
public:
	int nTop;
	vector<DistData> Data;
public:
	NodesStack() :nTop(0) {}
	void push(vector<int> vnodes, int dist) {
		DistData dd(vnodes, dist);
		Data.push_back(dd);
		nTop++;
	}
	DistData pop() {
		DistData data = Data[nTop - 1];
		nTop--;
		Data.pop_back();
		return data;
	}
	DistData top() {
		DistData data = Data[nTop - 1];
		return data;
	}
	int size() {
		return nTop;
	}

	bool isEmpty() {
		return (nTop == 0);
	}
	void clear() {
		Data.clear();
		nTop = 0;
	}
};

int calcmindist(int* vs, int vsnum, int dists[][MAX_SIZE*MAX_SIZE], int c)
{
	int ds = 0;
	int istart = vs[0];
	int* visited = new int[vsnum];
	int visitednum = 0;
	visited[visitednum++] = vs[0];
	for (int i = 1; i < vsnum; i++) {
		int maxid = 0;
		int minstt = getmaxdist(dists, c, visited, visitednum, vs[i], maxid);
		ds += minstt;
		visited[visitednum++] = vs[i];
	}
	delete[] visited;
	return ds;
}

int getmindist(int* oils, int nums, int r, int c)
{
	int dist = INT16_MAX;
	int* oils_back = new int[nums];
	int* visited = new int[nums];
	int visitednum = 0;
	bool bExit = false;
	for (int i = 0; i < nums; i++) {
		for (int i = 0; i < nums; i++)
			oils_back[i] = oils[i];
		visitednum = 0;
		int bnums = nums;
		int mindist = 0;
		int index = oils[i];
		while (bnums > 0) {
			int nindex = deletedata(oils_back, bnums, index);
			insertdata(visited, visitednum, 0, index);
			if (!bnums)
				break;
			vector<int> minnodes;
			int mdist = mincostexstart(oils_back, bnums, visited, visitednum, dists, r, c, minnodes);
			mindist += mdist;
			index = minnodes[0];
		}
		if (mindist < dist) {
			dist = mindist;
		}
	}
	delete[] oils_back;
	delete[] visited;
	return dist;
}

int getmindistst(int* oils, int nums, int r, int c, vector<int>& vs)
{
	int* visited = new int[nums];
	int visitednum = 0;
	visitednum = 0;
	int bnums = nums;
	int mindist = 0;
	int index = oils[0];
	vs.push_back(index);
	while (bnums > 0) {
		int nindex = deletedata(oils, bnums, index);
		insertdata(visited, visitednum, 0, index);
		if (!bnums)
			break;
		vector<int> minnodes;
		int mdist = mincostexstart(oils, bnums, visited, visitednum, dists, r, c, minnodes);
		mindist += mdist;
		index = minnodes[0];
		vs.push_back(index);
	}
	delete[] visited;
	return mindist;
}


typedef struct {
	int min;
	int secmin;
} TwoMin;
void bubblesort(TwoMin *dists, int index)
{
	for (int i = 0; i < index; i++)
	{
		for (int j = i + 1; j < index; j++) {
			if (dists[j].min < dists[i].min) {
				TwoMin iMin = dists[i];
				dists[i] = dists[j];
				dists[j] = iMin;
			}
		}
	}
}
int estmindist(int* oils, int nums, int r, int c)
{
	if (nums < 2)
		return 0;
	if (nums == 2)
		return dists[oils[0]][oils[1]];

	int mindist = INT16_MAX;
	int dist = 0;
	TwoMin *tmin = new TwoMin[nums];
	for (int i = 0; i < nums; i++) {
		mindist = INT16_MAX;
		int mindex = 0;
		for (int j = 0; j < nums; j++) {
			if (j == i) continue;
			if (dists[oils[i]][oils[j]] < mindist) {
				mindist = dists[oils[i]][oils[j]];
				mindex = j;
			}
		}
		dist += mindist;
		tmin[i].min = mindist;
		mindist = INT16_MAX;
		for (int j = 0; j < nums; j++) {
			if (j == i) continue;
			if (j == mindex) continue;
			if (dists[oils[i]][oils[j]] < mindist) {
				mindist = dists[oils[i]][oils[j]];
				mindex = j;
			}
		}
		dist += mindist;
		tmin[i].secmin = mindist;
	}
	//bubblesort(tmin, nums);
	//dist -= tmin[0].secmin;
	//dist -= tmin[1].secmin;
	return dist/2;
}


vector<int> getintersect(vector<int> v1, vector<int> v2)
{
	vector<int> ins;
	int nodesmap[MAX_SIZE*MAX_SIZE] = { 0 };
	int count = 0;
	for (int i = 0; i < v1.size(); i++) {
			nodesmap[v1[i]] = 1;
	}

	for (int i = 0; i < v2.size(); i++) {
		if (nodesmap[v2[i]])
			ins.push_back(v2[i]);
		else
			nodesmap[v2[i]] = 1;
	}
	return ins;
}

vector<int> getunion(vector<int> v1, vector<int> v2)
{
	vector<int> uni;
	for (int i = 0; i < v1.size(); i++) {
		uni.push_back(v1[i]);
	}
	for (int i = 0; i < v2.size(); i++) {
		uni.push_back(v2[i]);
	}
	return uni;
}

const int MAX_NODES = 600000;
const int THRESHOLD = 2;


bool isdup(vector<int> vst, vector<int> vs)
{
	int ghash[MAX_SIZE*MAX_SIZE] = { 0 };

	if (vst.size() != vs.size())
		return false;
	
	int isize = 0;
	int tsize = vst.size();
	for (int i = 0; i < vst.size(); i++) {
		ghash[vst[i]] = 1;
	}
	for (int i = 0; i < vs.size(); i++) {
		if (ghash[vs[i]] == 1)
			isize++;
	}
	return (isize == tsize);
		
}


bool finddup(vector<int> vst, int dst, vector<DistData> mindsnodes)
{
	for (int i = 0; i < mindsnodes.size(); i++) {
		if (isdup(mindsnodes[i].vs, vst) && dst == mindsnodes[i].dist)
			return true;
	}
	return false;
}

bool issame(vector<int> vs, int* visited, int visitednum)
{
	vector<int> vst;
	for (int i = 0; i < visitednum; i++)
		vst.push_back(visited[i]);
	return isdup(vs, vst);

	//if (vs.size() != visitednum)
	//	return false;
	//for (int i = 0; i < vs.size(); i++)
	//	if (vs[i] != visited[i])
	//		return false;
	//return true;
}

int mincostre(int blocks[][MAX_SIZE], int r, int c)
{
	int oils[MAX_SIZE*MAX_SIZE] = { 0 };
	int nums = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (blocks[i][j] == 1)
				oils[nums++] = i*c + j;
		}
	if (!nums)
		return 0;
	int distindex = 0;
	for (int i = 0; i < nums; i++)
		for (int j = i + 1; j < nums; j++) {
			int ds = calcdist(oils[i], oils[j], r, c);
			dists[oils[i]][oils[j]] = ds;
			dists[oils[j]][oils[i]] = ds;
		}
	int dist = 0;
	int* visited = new int[nums];
	int visitednum = 0;
	int maxnode = 0;

	NodesStack nstack;
	int imintotaldist = INT16_MAX;
	for (int i = 0; i < nums; i++) {
		for (int j = i + 1; j < nums; j++) {
			int ds = dists[oils[i]][oils[j]];
			if (ds < imintotaldist)
				imintotaldist = ds;
			vector<int> vst;
			vst.push_back(oils[i]);
			vst.push_back(oils[j]);
			nstack.push(vst, ds);
			maxnode++;
		}
	}
	dist += imintotaldist;
	int* oils_back = new int[nums];
	memcpy(oils_back, oils, sizeof(int) * nums);

	bool even = false;
	bool bEven = false;
	int lastmin = 0;
	int lastdelmin = 0;
	vector<DistData> lastnode, last2node;
	while (1) {
		bool bFull = false;
		int levelmindist = INT16_MAX;
		vector<DistData> mindsnodes;
		int lastsize = 0;
		int skipnodes = 0;
		while (!nstack.isEmpty()) {
			visitednum = 0;
			int numsback = nums;
			memcpy(oils, oils_back, sizeof(int) * nums);
			DistData dd = nstack.pop();
			vector<int> vs = dd.vs;
			int cursize = vs.size();
			int pmxdist = dd.dist;
			if (cursize != lastsize) {
				cout << cursize << "/" << nums << endl;
				cout << dist << endl;
				//			int st = vs[0];
							//if(st == 10 || st == 11)
							//for (int i = 0; i < vs.size(); i++)
							//	cout << vs[i] / c << "," << vs[i] % c << endl;
				lastsize = cursize;
			}
			if (cursize == nums) {
				bFull = true;
				break;
			}
			for (int i = 0; i < cursize; i++)
				deletedata(oils, numsback, vs[i]);

			for (int i = 0; i < cursize; i++)
				visited[visitednum++] = vs[i];
			even = false;
#if 0
			if (nums - cursize >= 2 && even) {
				int* oils_bk = new int[nums];
				int* vis_bk = new int[nums];
				int nums_bk = numsback;
				int pmxdist_bk = pmxdist;
				int visitednum_bk = visitednum;
				memcpy(oils_bk, oils, sizeof(int) * nums);
				memcpy(vis_bk, visited, sizeof(int) * nums);
				int twomin = INT16_MAX;
				vector<DistData> twonodes;
				for (int i = 0; i < numsback; i++) {
					memcpy(oils, oils_bk, sizeof(int) * nums);
					memcpy(visited, vis_bk, sizeof(int) * nums);
					visitednum = visitednum_bk;
					nums_bk = numsback;
					pmxdist = pmxdist_bk;
					int delnode = oils[i];
					pmxdist += getmaxdist(dists, c, visited, visitednum, delnode);
					deletedata(oils, nums_bk, delnode);
					visited[visitednum++] = delnode;
					vector<int> nodest;
					int mdist = pmxdist + mincostexstart(oils, nums_bk, visited, visitednum, dists, r, c, nodest);
					if (mdist < twomin) {
						twomin = mdist;
						twonodes.clear();
						for (int j = 0; j < nodest.size(); j++) {
							int ds = mdist;
							vector<int> vst = vs;
							vst.push_back(delnode);
							vst.push_back(nodest[j]);
							twonodes.push_back(DistData(vst, ds));
						}
					}
					//else if (mdist == twomin)
					//	for (int j = 0; j < nodest.size(); j++) {
					//		int ds = mdist;
					//		vector<int> vst = vs;
					//		vst.push_back(delnode);
					//		vst.push_back(nodest[j]);
					//		twonodes.push_back(DistData(vst, ds));
					//	}
				}
				if (visitednum == nums - 1 && twomin < levelmindist) {
					levelmindist = twomin;
				}
				else if (visitednum < nums - 1)
					for (int j = 0; j < twonodes.size(); j++) {
						nstack.push(twonodes[j].vs, twonodes[j].dist);
						maxnode++;
					}
				if (twomin >= levelmindist && !nstack.isEmpty()) {
					DistData dt = nstack.pop();
					while (!nstack.isEmpty() && dt.vs.size() > 1) {
						dt = nstack.pop();
						skipnodes++;
					}
					if (dt.vs.size() == 1)
						nstack.push(dt.vs, dt.dist);
				}
				delete[] oils_bk;
				delete[] vis_bk;
				bEven = true;
				lastmin = INT16_MAX;
			}
			else 
#endif
			{
				vector<int> nodest;
				int minst = pmxdist + mincostexstart(oils, numsback, visited, visitednum, dists, r, c, nodest);
				int mdist = minst;
#if 1
				vector<int> minndt = nodest;
				vector<int> minvs = vs;
				vector<DistData> vit;
				NodesStack ministk;
				for (int i = 0; i < nodest.size(); i++) {
					vector<int> mmin = vs;
					ministk.push(vs, nodest[i]);
				}
				while(!ministk.isEmpty()) {
					DistData ddt = ministk.pop();
					vector<int> vstart = ddt.vs;
					visitednum = 0;
					memcpy(oils, oils_back, sizeof(int) * nums);
					numsback = nums;
					for (int i = 0; i < vstart.size(); i++)
						deletedata(oils, numsback, vstart[i]);
					for (int i = 0; i < vstart.size(); i++)
						visited[visitednum++] = vstart[i];
					int starti = ddt.dist;
					vit.push_back(DistData(ddt.vs, starti));
					vector<int> vst;
					bool bExit = false;
					while (!bExit) {
						int maxid = 0;
						int minstt = getmaxdist(dists, c, visited, visitednum, starti, maxid);
						deletedata(visited, visitednum, maxid);
						oils[numsback++] = maxid;
						vst.push_back(maxid);
						//lastv = maxid;
						int pdst = calcmindist(visited, visitednum, dists, c);
						int tdst = getmaxdist(dists, c, visited, visitednum, starti, maxid);
						pdst += tdst;
						deletedata(oils, numsback, starti);
						visited[visitednum++] = starti;
						vector<int> ntd;
						int mit = mincostexstart(oils, numsback, visited, visitednum, dists, r, c, ntd);
						pdst += mit;
						mdist = pdst;
#if 1
						int ns = 0;
						vector<int> ntdd;
						for (int j = 0; j < ntd.size(); j++) {
							bool bEqual = false;
							for (int i = 0; i < vst.size(); i++) {
								if (vst[i] == ntd[j]) {
									bEqual = true;
									break;
								}
							}
							if (bEqual) {
								ns++;
								continue;
							} else {
								ntdd.push_back(ntd[j]);
							}
						}
						if (ns == ntd.size()) {
							bExit = true;
							break;
						}
						starti = ntdd[0];
#if 0
						for (int ic = 0; ic < ntdd.size(); ic++) {
							bool bVst = false;
							for (int i = 0; i < vit.size(); i++)
								if (vit[i].dist == ntdd[ic]/* && issame(vit[i].vs, visited, visitednum)*/) {
									bVst = true;
									break;
								}
							if (bVst)
								continue;
							if (starti == -1) {
								starti = ntdd[ic];
								vector<int> mminvs;
								for (int id = 0; id < visitednum; id++)
									mminvs.push_back(visited[id]);
								vit.push_back(DistData(mminvs, starti));
							}
							else {
								vector<int> mminvs;
								for (int id = 0; id < visitednum; id++)
									mminvs.push_back(visited[id]);
								//if (finddup(mminvs, ntdd[ic], ministk.Data))
								//	continue;
								ministk.push(mminvs, ntdd[ic]);
							}
						}
						if (starti == -1) {
							bExit = true;
							break;
						}
#endif
#endif
						if (mdist < minst) {
							minst = mdist;
							minndt = ntd;
							minvs.clear();
							for (int id = 0; id < visitednum; id++)
								minvs.push_back(visited[id]);
						}
					}
				}
				nodest = minndt;
				vs = minvs;
#endif
				if (minst < levelmindist) {
					mindsnodes.clear();
					levelmindist = minst;
					for (int i = 0; i < nodest.size(); i++) {
						int ds = minst;
						vector<int> vst = vs;
						vst.push_back(nodest[i]);
						if (finddup(vst, ds, mindsnodes))
							continue;
						mindsnodes.push_back(DistData(vst, ds));
						maxnode++;
					}
				}
				else if (minst == levelmindist) {
					for (int i = 0; i < nodest.size(); i++) {
						int ds = minst;
						vector<int> vst = vs;
						vst.push_back(nodest[i]);
						if (finddup(vst, ds, mindsnodes))
							continue;
						mindsnodes.push_back(DistData(vst, ds));
						maxnode++;
					}
				}

				bEven = false;
				int delmin = minst - lastmin;
#if 0
				if (delmin > THRESHOLD && !bEven) {
					even = true;
					if (!nstack.isEmpty()) {
						DistData dt = nstack.pop();
						while (!nstack.isEmpty() && dt.vs.size() > 1) {
							dt = nstack.pop();
						}
						if (dt.vs.size() == 1)
							nstack.push(dt.vs, dt.dist);
					}
					nstack.push(lastnode.vs, lastnode.dist);
					maxnode++;
				}
#endif
				lastmin = minst;
				lastdelmin = delmin;
			}	
		}
		if (bFull)
			break;
		dist = levelmindist;
		for (int i = 0; i < mindsnodes.size(); i++) {
			nstack.push(mindsnodes[i].vs, mindsnodes[i].dist);
		}
		if (bEven) {
			even = false;
			lastdelmin = INT16_MAX;
		}
		if (!bEven) {
			last2node = lastnode;
			lastnode = mindsnodes;
		}
		
	}
	delete[] visited;
	delete[] oils_back;
	return dist;
}

typedef struct {
	int node;
	int dist;
} DsData;

void bubblesort(DsData *dists, int index)
{
	for (int i = 0; i < index; i++)
	{
		for (int j = i + 1; j < index; j++) {
			if (dists[j].dist < dists[i].dist) {
				DsData iMin = dists[i];
				dists[i] = dists[j];
				dists[j] = iMin;
			}
		}
	}
}


void findlessdis(int *oils, int nums, int r, int c, int vnum, int minst, vector<DistData>& evals)
{
	int vn = 0;
	DsData* tmpvs = new DsData[nums];
	int mind = INT16_MAX;
	vector<int> vs;
	for (int i = 0; i < nums; i++) {
		bool bNotFind = false;
		vn = 0;
		for (int j = 0; j < nums; j++) {
			if (j == i)
				continue;
			if (dists[oils[i]][oils[j]] < minst) {
				DsData dd;
				dd.node = oils[j];
				dd.dist = dists[oils[i]][oils[j]];
				tmpvs[vn++] = dd;
			}
			if (nums - j + vn - 1 < vnum) {
				bNotFind = true;
				break;
			}
		}
		if (bNotFind)
			continue;
		if (vn < vnum)
			continue;
		bubblesort(tmpvs, vn);
		//int md = tmpvs[vnum - 1].dist;
		/*if (md < mind)*/ {
			//mind = md;	
			vs.clear();
			for (int k = 0; k < vnum; k++)
				vs.push_back(tmpvs[k].node);
			evals.push_back(DistData(vs, 0));
		}
		//else if (md == mind) {
		//	vs.clear();
		//	for (int k = 0; k < vnum; k++)
		//		vs.push_back(tmpvs[k].node);
		//	evals.push_back(DistData(vs, 0));
		//}
	}
	delete[] tmpvs;

}

int mincostdp(int blocks[][MAX_SIZE], int r, int c)
{
	int oils[MAX_SIZE*MAX_SIZE] = { 0 };
	int nums = 0;
	int maxnode = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (blocks[i][j] == 1)
				oils[nums++] = i*c + j;
		}
	if (!nums)
		return 0;	
	int* oils_back = new int[nums];
	memcpy(oils_back, oils, sizeof(int) * nums);
	int distindex = 0;
	for (int i = 0; i < nums; i++)
		for (int j = i + 1; j < nums; j++) {
			int ds = calcdist(oils[i], oils[j], r, c);
			dists[oils[i]][oils[j]] = ds;
			dists[oils[j]][oils[i]] = ds;
		}
	int dist = 0;
	int* visited = new int[nums];
	int visitednum = 0;

	DistData start;
	int imintotaldist = INT16_MAX;
	int mini, minj;
	for (int i = 0; i < nums; i++) {
		for (int j = i + 1; j < nums; j++) {
			int ds = dists[oils[i]][oils[j]];
			if (ds < imintotaldist) {
				imintotaldist = ds;
				mini = oils[i];
				minj = oils[j];
			}
		}
	}

	dist = imintotaldist;
	int totalnum = nums;
	deletedata(oils, nums, mini);
	visited[visitednum++] = mini;
	deletedata(oils, nums, minj);
	visited[visitednum++] = minj;

	for (int i = 2; i < totalnum; i++) {
		// iteratively processing
		//
		int lmindist = INT16_MAX;
		vector<int> nodest;
		vector<int> vs;
		int iminnode = 0;
		int ldist = mincostexstart(oils, nums, visited, visitednum, dists, r, c, nodest);
		int minst = dist + ldist;
		if (minst < lmindist) {
			lmindist = minst;
			iminnode = nodest[0];
			vs.clear();
			for (int i = 0; i < visitednum; i++)
				vs.push_back(visited[i]);
		}
		vector<DistData> evals;
		findlessdis(oils_back, totalnum, r, c, visitednum, ldist, evals);
		for (int id = 0; id < evals.size(); id++) {
			visitednum = 0;
			nums = totalnum;
			memcpy(oils, oils_back, sizeof(int) * nums);
			for (int i = 0; i < evals[id].vs.size(); i++) {
				visited[visitednum++] = evals[id].vs[i];
				deletedata(oils, nums, evals[id].vs[i]);
			}
			int pmdist = 0;
			int ltdist = mincostexstart(oils, nums, visited, visitednum, dists, r, c, nodest);
			pmdist = estmindist(visited, visitednum, r, c);
			if (pmdist + ltdist >= lmindist)
				continue;
			pmdist = getmindist(visited, visitednum, r, c);	
			maxnode++;
			int minst = pmdist + ltdist;
			if (minst < lmindist) {
				lmindist = minst;
				iminnode = nodest[0];
				vs.clear();
				for (int i = 0; i < visitednum; i++)
					vs.push_back(visited[i]);
			}
		}

		visitednum = 0;
		nums = totalnum;
		memcpy(oils, oils_back, sizeof(int) * nums);
		for (int i = 0; i < vs.size(); i++) {
			visited[visitednum++] = vs[i];
			deletedata(oils, nums, vs[i]);
		}
		deletedata(oils, nums, iminnode);
		visited[visitednum++] = iminnode;
		dist = lmindist;
		cout << "i " << i << " dist " << dist << endl;
	}
	cout << "manode " << maxnode << endl;
	return dist;
}


int mincostbnb(int blocks[][MAX_SIZE], int r, int c)
{
	int oils[MAX_SIZE*MAX_SIZE] = { 0 };
	int nums = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (blocks[i][j] == 1)
				oils[nums++] = i*c + j;
		}
	if (!nums)
		return 0;
	int distindex = 0;
	for (int i = 0; i < nums; i++)
		for (int j = i + 1; j < nums; j++) {
			int ds = calcdist(oils[i], oils[j], r, c);
			dists[oils[i]][oils[j]] = ds;
			dists[oils[j]][oils[i]] = ds;
		}
	int dist = 0;
	int* visited = new int[nums];
	int visitednum = 0;
	int maxnode = 0;

	NodesStack nstack;
	
	for (int i = 0; i < nums; i++) {
			vector<int> vst;
			vst.push_back(oils[i]);
			nstack.push(vst, 0);
			maxnode++;
	}

	int* oils_back = new int[nums];
	memcpy(oils_back, oils, sizeof(int) * nums);
	int imintotaldist = INT16_MAX;
	vector<int> vst;
	imintotaldist = getmindistst(oils_back, nums, r, c, vst);
	memcpy(oils_back, oils, sizeof(int) * nums);
	vector<DistData> lastnode, last2node;
	while (!nstack.isEmpty()) {
		visitednum = 0;
		int numsback = nums;
		memcpy(oils, oils_back, sizeof(int) * nums);
		DistData dd = nstack.pop();
		int cursize = dd.vs.size();
		int pmxdist = dd.dist;
		if (cursize == nums) {
			if (pmxdist < imintotaldist) {
				imintotaldist = pmxdist;
			}
		}
		else {

			for (int i = 0; i < cursize; i++)
				deletedata(oils, numsback, dd.vs[i]);
			for (int i = 0; i < cursize; i++)
				visited[visitednum++] = dd.vs[i];

			pmxdist = dd.dist + estmindist(oils, numsback, r, c);
			if (pmxdist > imintotaldist)
				continue;

			for (int i = 0; i < numsback; i++) {				
				int maxindex = 0;
				pmxdist = dd.dist + getmaxdist(dists, c, visited, visitednum, oils[i], maxindex);
				if (pmxdist > imintotaldist)
					continue;
				vector<int> vs = dd.vs;
				vs.push_back(oils[i]);
				nstack.push(vs, pmxdist);
				maxnode++;
				if (!(maxnode % 10000000))
					cout << maxnode << endl;
			}
		}
	}
	delete[] visited;
	delete[] oils_back;
	cout << "evaluated " << maxnode << endl;
	return imintotaldist;
}


int mincost2opt(int blocks[][MAX_SIZE], int r, int c)
{
	int oils[MAX_SIZE*MAX_SIZE] = { 0 };
	int nums = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (blocks[i][j] == 1)
				oils[nums++] = i*c + j;
		}
	if (!nums)
		return 0;
	int distindex = 0;
	for (int i = 0; i < nums; i++)
		for (int j = i + 1; j < nums; j++) {
			int ds = calcdist(oils[i], oils[j], r, c);
			dists[oils[i]][oils[j]] = ds;
			dists[oils[j]][oils[i]] = ds;
		}

	NodesStack nstack;

	for (int i = 0; i < nums; i++) {
		vector<int> vst;
		vst.push_back(oils[i]);
		nstack.push(vst, 0);
	}

	int* oils_back = new int[nums];
	memcpy(oils_back, oils, sizeof(int) * nums);

	int imintotaldist = INT16_MAX;
	//vector<int> vst;
	//imintotaldist = getmindistst(oils_back, nums, r, c, vst);

	int* visited = new int[nums];
	int visitednum = 0;
	bool bExit = false;
	while (!nstack.isEmpty()) {
		visitednum = 0;
		int numsback = nums;
		memcpy(oils, oils_back, sizeof(int) * nums);
		DistData dd = nstack.pop();
		int cursize = dd.vs.size();
		int pmxdist = dd.dist;
		if (cursize == nums) {
			if (pmxdist < imintotaldist) {
				imintotaldist = pmxdist;
			}
		}
		else {
			for (int i = 0; i < cursize; i++)
				deletedata(oils, numsback, dd.vs[i]);
			for (int i = 0; i < cursize; i++)
				visited[visitednum++] = dd.vs[i];

			vector<int> minnodes;
			int mdist = mincostexstart(oils, numsback, visited, visitednum, dists, r, c, minnodes);
			pmxdist = dd.dist + mdist;
			if (cursize < 2) {
				dd.vs.push_back(minnodes[0]);
				nstack.push(dd.vs, pmxdist);
				continue;
			}
			int minndt = minnodes[0];
			vector<int> minvs = dd.vs;
			for (int idindex = 0; idindex < minnodes.size(); idindex++) {
				numsback = nums;
				memcpy(oils, oils_back, sizeof(int) * nums);
				visitednum = 0;
				for (int i = 0; i < cursize; i++)
					deletedata(oils, numsback, dd.vs[i]);
				for (int i = 0; i < cursize; i++)
					visited[visitednum++] = dd.vs[i];

				int starti = minnodes[idindex];
				vector<int> vst;
				bool bExit = false;
				while (!bExit) {
					int maxid = 0;
					int minstt = getmaxdist(dists, c, visited, visitednum, starti, maxid);
					deletedata(visited, visitednum, maxid);
					oils[numsback++] = maxid;
					vst.push_back(maxid);
					int pdst = calcmindist(visited, visitednum, dists, c);
					int tdst = getmaxdist(dists, c, visited, visitednum, starti, maxid);
					pdst += tdst;
					deletedata(oils, numsback, starti);
					visited[visitednum++] = starti;
					vector<int> ntd;
					int mit = mincostexstart(oils, numsback, visited, visitednum, dists, r, c, ntd);
					pdst += mit;
					mdist = pdst;
					int ns = 0;
					vector<int> ntdd;
					for (int j = 0; j < ntd.size(); j++) {
						bool bEqual = false;
						for (int i = 0; i < vst.size(); i++) {
							if (vst[i] == ntd[j]) {
								bEqual = true;
								break;
							}
						}
						if (bEqual) {
							ns++;
							continue;
						}
						else {
							ntdd.push_back(ntd[j]);
						}
					}
					if (mdist < pmxdist) {
						pmxdist = mdist;
						minndt = ntd[0];
						minvs.clear();
						for (int id = 0; id < visitednum; id++)
							minvs.push_back(visited[id]);
					}
					if (ns == ntd.size()) {
						bExit = true;
						break;
					}
					starti = ntdd[0];
				}
			}
			if (pmxdist > imintotaldist)
				continue;
			/*for (int i = 0; i < min(2, (int)minnodes.size()); i++)*/ {
				vector<int> vs = minvs;
				vs.push_back(minndt);
				nstack.push(vs, pmxdist);
			}
		}
	}


	delete[] oils_back;
	delete[] visited;
	return imintotaldist;
}

int getpostdist(int* vs, int vsnum, int dists[][MAX_SIZE*MAX_SIZE], int c, vector<vector<int>>& mxlist)
{
	int ds = 0;
	int istart = vs[0];
	int* visited = new int[vsnum];
	int visitednum = 0;
	visited[visitednum++] = vs[0];
	for (int i = 0; i < vsnum; i++) {
		vector<int> index;
		mxlist.push_back(index);
	}
	for (int i = 1; i < vsnum; i++) {
		int maxid = 0;
		int minstt = getmaxindex(dists, c, visited, visitednum, vs[i], maxid);		
		mxlist[maxid].push_back(i);
		ds += minstt;
		visited[visitednum++] = vs[i];
	}
	delete[] visited;
	return ds;
}


int opttouronce(int dists[][MAX_SIZE*MAX_SIZE], int r, int c,
	int* oils, int num, int istart, int end1, int end2, int dist,
	vector< vector<int>>& mxlist)
{
	int* oils_back = new int[num];
	for (int i = 0; i < num; i++)
		oils_back[i] = oils[i];
	int bnums = end2+1;
	int nindex = deletedata(oils_back, bnums, oils[istart]);
	oils_back[end2] = oils[istart];
	mxlist.clear();
	int ds = getpostdist(oils_back, num, dists, c, mxlist);
	if (ds < dist) {
		for (int i = 0; i < istart; i++) {
			if (mxlist[i].size()>1) {
				ds = opttouronce(dists, r, c, oils_back, num, i,
					mxlist[i][0], mxlist[i][1], ds, mxlist);
			}
		}
		for (int i = 0; i < num; i++)
			oils[i] = oils_back[i];
		delete[] oils_back;
		return ds;
	}
	else {
		delete[] oils_back;
		return dist;
	}
}

int opttour(int dists[][MAX_SIZE*MAX_SIZE], int r, int c, int* oils, int num)
{
	NodesStack nstack;
	int mindist = INT16_MAX;
	vector< vector<int>> mxlist;
	mindist = getpostdist(oils, num, dists, c, mxlist);
	for (int i = 0; i < num; i++) {
		if (mxlist[i].size()>1) {
			//ds = opttouronce(dists, r, c, oils, num, i, mxlist[i][0], mxlist[i][1], ds, mxlist);
			int* oils_back = new int[num];
			for (int i = 0; i < num; i++)
				oils_back[i] = oils[i];
			int bnums = num;
			int nindex = deletedata(oils_back, bnums, oils[i]);
			insertdata(oils_back, bnums, mxlist[i][mxlist[i].size() - 1], oils[i]);
			vector<int> nodes;
			for (int i = 0; i < num; i++)
				nodes.push_back(oils_back[i]);	
			int dist = calcmindist(oils_back, num, dists, c);
			if (dist < mindist)
				mindist = dist;
#if USE_HASH
			int hash = gethash(oils_back, num, c) % MAX_HASH;
			myhash[hash].dist = 1;
			for (int k = 0; k < num; k++)
				myhash[hash].nodes[k] = oils_back[k];
#endif
			nstack.push(nodes, dist);
			delete[] oils_back;
		}
	}
#if USE_HASH
	int nhash = gethash(oils, num, c) % MAX_HASH;
	myhash[nhash].dist = 1;
	for (int k = 0; k < num; k++) 
		myhash[nhash].nodes[k] = oils[k];
#endif
	int icalc = 0;
	int ilast = 0;
	while (!nstack.isEmpty() && icalc < 1e6) {
		DistData dsData = nstack.pop();
		for (int i = 0; i < num; i++)
			oils[i] = dsData.vs[i];
#if USE_HASH
		nhash = gethash(oils, num, c) % MAX_HASH;
		if (myhash[nhash].dist == 1) {
			bool bFalseAlarm = false;
			for (int k = 0; k < num; k++) {
				if (oils[k] != myhash[nhash].nodes[k]) {
					bFalseAlarm = true;
					break;
				}
			}
			if (!bFalseAlarm) {
				printf("has calc\n");
				continue;
			}
		}
#endif
		vector< vector<int>> mxlist;
		int ds = getpostdist(oils, num, dists, c, mxlist);
		for (int i = 0; i < num; i++) {
			if (mxlist[i].size()>1) {
				int* oils_back = new int[num];
				for (int i = 0; i < num; i++)
					oils_back[i] = oils[i];
				int bnums = num;
				int nindex = deletedata(oils_back, bnums, oils[i]);
				insertdata(oils_back, bnums, mxlist[i][mxlist[i].size() - 1], oils[i]);
#if USE_HASH
				int hash = gethash(oils_back, num, c) % MAX_HASH;
				if (myhash[hash].dist == 1) {
					bool bFalseAlarm = false;
					for (int k = 0; k < num; k++) {
						if (oils_back[k] != myhash[hash].nodes[k]) {
							bFalseAlarm = true;
							break;
						}
					}
					if (!bFalseAlarm) {
						printf("has calc\n");
						delete[] oils_back;
						continue;
					}
				}
#endif
				vector<int> nodes;
				for (int i = 0; i < num; i++)
					nodes.push_back(oils_back[i]);
				int dist = calcmindist(oils_back, num, dists, c);
				if (dist < mindist) {
					mindist = dist;
					ilast = icalc;
				}
#if USE_HASH
				hash = gethash(oils_back, num, c) % MAX_HASH;
				myhash[hash].dist = 1;
				for (int k = 0; k < num; k++)
					myhash[hash].nodes[k] = oils_back[k];
#endif
				nstack.push(nodes, dist);
				delete[] oils_back;
			}
		}
#if USE_HASH
		myhash[nhash].dist = 1;
		for (int k = 0; k < num; k++)
			myhash[nhash].nodes[k] = oils[k];
#endif

		icalc++;
		if (icalc - ilast > 1e4)
			break;
	}
	return mindist;
}

int mincostopttour(int blocks[][MAX_SIZE], int r, int c)
{
	int oils[MAX_SIZE*MAX_SIZE] = { 0 };
	int nums = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (blocks[i][j] == 1)
				oils[nums++] = i*c + j;
		}
	if (!nums)
		return 0;
	//int data[] = { 18,19,13,14,12,24,21,1,2,20 };
	//for (int i = 0; i < nums; i++) {
	//	oils[i] = data[i];
	//}
	for (int i = 0; i < nums; i++)
		for (int j = i + 1; j < nums; j++) {
			int ds = calcdist(oils[i], oils[j], r, c);
			dists[oils[i]][oils[j]] = ds;
			dists[oils[j]][oils[i]] = ds;
		}
	return opttour(dists, r, c, oils, nums);
}

int mincostdyn(int blocks[][MAX_SIZE], int r, int c)
{
	int oils[MAX_SIZE*MAX_SIZE] = { 0 };
	int nums = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (blocks[i][j] == 1)
				oils[nums++] = i*c + j;
		}
	if (!nums)
		return 0;
	for (int i = 0; i < nums; i++)
		for (int j = i + 1; j < nums; j++) {
			int ds = calcdist(oils[i], oils[j], r, c);
			dists[oils[i]][oils[j]] = ds;
			dists[oils[j]][oils[i]] = ds;
		}

	int imintotaldist = 0;
	int* dps = new int[(1ULL << nums)];
	memset(dps, INT8_MAX, sizeof(int) * (1ULL << nums));
	for (int i = 0; i < (1ULL << nums); i++) { //iteratively calculate
		for (int j = 0; j < nums; j++) {
			if ((1ULL << j) & i) {
				if (i == (1ULL << j)) {
					dps[i] = 0;
				} else {
					int tmp = ~(1ULL << j);
					int remains = tmp & i;
					int maxindex = 0;
					int visnums = 0;
					int* visited = new int[nums];		
					for (int k = 0; k < nums; k++) {
						if (remains & (1ULL << k))
							visited[visnums++] = oils[k];
					}
					dps[i] = min(dps[i], dps[remains] + getmaxdist(dists, c, visited, visnums, oils[j], maxindex));
					delete[] visited;
				}
			}
		}
	}
	imintotaldist = dps[(1ULL << nums) - 1];
	delete[] dps;
	return imintotaldist;
}

int getindex(int r, int b, int l, int t)
{
	return r*MAX_SIZE*MAX_SIZE*MAX_SIZE + b*MAX_SIZE*MAX_SIZE + l*MAX_SIZE + t;
}

int getmindistdyn(int blocks[][MAX_SIZE], int r, int c)
{
	int* d = new int[MAX_SIZE*MAX_SIZE*MAX_SIZE*MAX_SIZE];
	for (int iRight = 0; iRight < c; iRight++)
		for (int iBottom = 0; iBottom < r; iBottom++)
			for (int iLeft = iRight; iLeft >= 0; iLeft--)
				for (int iTop = iBottom; iTop >= 0; iTop--)
				{
					d[getindex(iRight, iBottom, iLeft, iTop)] = INT16_MAX;
					if (iLeft == iRight && iTop == iBottom) {
						d[getindex(iRight,iBottom,iLeft,iTop)] = 0;
						continue;
					}
				
					// right most, bottom down
					int ds = INT16_MAX;
					if (iRight >= iLeft + 1) {
						ds = d[getindex(iRight - 1, iBottom, iLeft, iTop)];
						for (int i = iBottom; i >= iTop; i--)
							if (blocks[i][iRight])
								ds += std::max(iRight - iLeft, std::max(iBottom - i, i - iTop));
					}

					// left most, bottom down
					int ds_l = INT16_MAX;
					if (iLeft <= iRight - 1) {
						ds_l = d[getindex(iRight, iBottom, iLeft + 1, iTop)];
						for (int i = iBottom; i >= iTop; i--)
							if (blocks[i][iLeft])
								ds_l += std::max(iRight - iLeft, std::max(iBottom - i, i - iTop));
					}
					ds = (ds < ds_l) ? ds : ds_l;
					// top most, left to right
					int ds_t = INT16_MAX;
					if (iTop+1 <= iBottom) {
						ds_t = d[getindex(iRight, iBottom, iLeft, iTop + 1)];
						for (int i = iLeft; i <= iRight; i++)
							if (blocks[iTop][i])
								ds_t += std::max(iBottom - iTop, std::max(iRight - i, i - iLeft));
					}
					ds = (ds < ds_t) ? ds : ds_t;
					// bottom most, left to right
					int ds_b = INT16_MAX;
					if (iBottom-1 >= iTop) {
						ds_b = d[getindex(iRight, iBottom - 1, iLeft, iTop)];
						for (int i = iLeft; i <= iRight; i++)
							if (blocks[iBottom][i])
								ds_b += std::max(iBottom - iTop, std::max(iRight - i, i - iLeft));
					}
					ds = (ds < ds_b) ? ds : ds_b;
					d[getindex(iRight,iBottom,iLeft,iTop)] = ds;
				}
	int minds =  d[getindex(c-1, r-1, 0, 0)];
	delete[] d;
	return minds;
}

#define USE_RECURSIVE	0

int main(int args, char* argv[])
{
#if USE_HASH || USE_RECURSIVE 
	int hashMega = 3;
	if (args > 1)
		hashMega = atoi(argv[1]);
	int HASH_SIZE = hashMega * 100 * 1024 * 1024;
	int size = sizeof(Data);
	MAX_HASH = HASH_SIZE/ sizeof(Data);
	myhash = new Data[MAX_HASH];// (Data *)malloc(MAX_HASH * sizeof(Data));
	if (myhash == NULL) {
		cout << "Cannot allocate " << hashMega << "00M hash!" << endl;
		return -1;
	}
	cout << "Allocate " << hashMega << "00M hash!" << endl;
#endif
	int blocks[MAX_SIZE][MAX_SIZE] = { 0 };
	int r = 0;
	int c = 0;
	cin >> r;
	cin >> c;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> blocks[i][j];
		}
	}
	generaterand(r, c);
	clock_t begin = clock();
	clock_t end;
	double elapsed_secs;
#if USE_RECURSIVE
	vector<int> nodes;
	vector<int> mdists;
	int min = 0;
	min = mincostrec(blocks, r, c, nodes, mdists);
#else
	//int min = mincost2opt(blocks, r, c);
	//int min = mincostdyn(blocks, r, c);
	//int min = mincostopttour(blocks, r, c);
	int min = getmindistdyn(blocks, r, c);
#endif
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << min << endl;
#if USE_RECURSIVE
	for (int i = 0; i < nodes.size(); i++) {
		cout << nodes[i] / c << "," << nodes[i] % c << " " << mdists[i] << endl;
	}
#endif
	//cout << "Run time: " << elapsed_secs << "s" << endl;
	if(myhash)
		delete[] myhash;
    return 0;
}
