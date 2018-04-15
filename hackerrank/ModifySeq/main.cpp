#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <time.h>
using namespace std;
class IntArray {
public:
	int data;
	int len;
	int number;
public:
	IntArray() { len = 0; number = -1;}
	void Copy(int a, int n, int num) {
		data = a;
		len = n;
		number = num;
	}
	int CopyTo() {
		return data;
	}
	void Destroy() {
		len = 0;
		number = -1;
	}
};
IntArray* cache = NULL;
int nCache = 0;


int CeilIndex(std::vector<int> &v, int l, int r, int key) {
    //int ol = r;
    while (r-l > 1) {
        int m = l + (r-l)/2;
        if (v[m] <= key)
            l = m;
        else
            r = m;
    }
    return r;
}


int lnds(int *v, int len) {
    if (len == 0)
        return 0;
    
    std::vector<int> tail(len, 0);
    int length = 1;
    
    tail[0] = v[0];
    for (size_t i = 1; i < len; i++) {
        if (v[i] < tail[0])
            
            tail[0] = v[i];
        else if (v[i] >= tail[length-1])
            
            tail[length++] = v[i];
        else
            tail[CeilIndex(tail, -1, length-1, v[i])] = v[i];
    }
    
    return length;
}


int getModifyNumbers(int *a, int len)
{
    int *mods = new int[len];
    int alen = 0;
    for(int i=0; i<len; i++) {
        a[i] -= (i+1);
        if(a[i] >=0)
            mods[alen++] = a[i];
    }
    int num = lnds(mods, alen);
    delete[] mods;
    return len - num;
}

int modifyseq(int *a, int number, int max_try)
{
    if(number<2) {
        return 0;
    }
    if(number==2) {
        if(a[0] < a[1])
            return 0;

        if(a[1] - 1<= 0) {
            a[1] = a[0] + 1;
            return 1;
        } else
           a[0] = a[1] - 1;
        return 1;
    }
    int num = 0;
	// Stepwise processing
	//
      if(a[0] < a[1]) {
		    int b[2] = {0};
			int inum = -1;
		    b[0] = a[0];
			b[1] = b[0] + 1;
			if(b[1] != a[1]) {
				inum = 1;
				cache[2%2*nCache+1].Copy(b[1], 2, inum);
			}

			int c[2];
			inum = -1;
			c[0] = 1;
			c[1] = 2;
			if(c[0] != a[0] && c[1] != a[1]) {
				inum = 2;
				cache[2%2*nCache+2].Copy(c[1], 2, inum);
			}

			cache[2%2*nCache].Copy(a[1], 2, 0);

            num = 0;

	  } else {
        if(a[1] == 1) {
				int atmp = a[1];
                a[1] = a[0] + 1;
                num = 1;
				cache[2%2*nCache].Copy(a[1],2, num);
				a[1] = atmp;
				int b[2];
				b[0] = 1;
				b[1] = 2;
				int inum = -1;
				if(b[1] != a[1]) {
					inum = 2;
					cache[2%2*nCache+1].Copy(b[1], 2, inum);
				}
        } else {
		   int atmp = a[0];
           a[0] = a[1] - 1;
           num = 1;
		   cache[2%2*nCache].Copy(a[1],2, num);
		   a[0] = atmp;
		   int b[2];
		   b[0] = 1;
		   b[1] = 2;
		   int inum = -1;
			if(b[1] != a[1]){
				inum = 2;
				cache[2%2*nCache+1].Copy(b[1], 2, inum);
			}

		}
	  }
    for(int n=3; n<=number; n++){
		// calc n,[0,..,n]
		for(int m=0; m<=max_try && m<=number-n; m++){
			bool bDone = false;
			int inum = -1;
			if(m>=1) {
				inum = cache[n%2*nCache].number + m;
				if(inum == cache[(n-1)%2*nCache+m-1].number+1) {
					if(cache[(n-1)%2*nCache+m-1].number >= 0) {
						if(cache[(n-1)%2*nCache+m-1].data < a[n-1]
						&& cache[(n-1)%2*nCache+m-1].data+1 != a[n-1]) {
							if(cache[(n-1)%2*nCache+m-1].number+1 == inum) {
								cache[n%2*nCache + m].Copy(cache[(n-1)%2*nCache+m-1].data + 1,
									n, cache[(n-1)%2*nCache+m-1].number+1);
								bDone = true;
							}
						}
					}
				} else {
					if(cache[(n-1)%2*nCache+m+1].number >= 0
						&& cache[(n-1)%2*nCache+m+1].data < a[n-1]
					&& ( cache[(n-1)%2*nCache+m].number < 0
						|| (cache[(n-1)%2*nCache+m].number >= 0 && cache[(n-1)%2*nCache+m].data+1 >= a[n-1]) )) {
							if(cache[(n-1)%2*nCache+m+1].number == inum) {
								cache[n%2*nCache+m].Copy(a[n-1], n, cache[(n-1)%2*nCache+m+1].number);
								bDone = true;
							}
					} else if(cache[(n-1)%2*nCache+m].number >= 0
						/*&& cache[(n-1)%2*nCache+m].data+1 != a[n-1]*/) {
							if(cache[(n-1)%2*nCache+m].number+1 == inum) {
								cache[n%2*nCache+m].Copy(cache[(n-1)%2*nCache+m].data+1,
									n, cache[(n-1)%2*nCache+m].number+1);
								bDone = true;
							}
					}
				}
			} else {
				if(cache[(n-1)%2*nCache].CopyTo() < a[n-1]){
					cache[n%2*nCache+m].Copy(a[n-1], n, cache[(n-1)%2*nCache].number);
					bDone = true;
				} else {
					if(cache[(n-1)%2*nCache+m+1].number >= 0
						&& cache[(n-1)%2*nCache+m+1].data < a[n-1]
					&& ( cache[(n-1)%2*nCache+m].number < 0
						|| (cache[(n-1)%2*nCache+m].number >= 0 && cache[(n-1)%2*nCache+m].data+1 >= a[n-1]) )) {
							cache[n%2*nCache+m].Copy(a[n-1], n, cache[(n-1)%2*nCache+m+1].number);
							bDone = true;
					} else if(cache[(n-1)%2*nCache+m].number >= 0
						/*&& cache[(n-1)%2*nCache+m].data != a[n-1]*/) {
							cache[n%2*nCache+m].Copy(cache[(n-1)%2*nCache+m].data+1,
								n, cache[(n-1)%2*nCache+m].number+1);
							bDone = true;
					}
				}

			}
			if(!bDone)
				cache[n%2*nCache+m].number = -1;
		}
    }
    return cache[number%2*nCache].number;
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

int main()
{

#if 0
    int N = 23;
#else
	int N;
    cin >> N;
#endif
#if 0
	string input;
	ifstream ifs("test.txt");
	getline(ifs, input);
	N = atoi(input.c_str());
	getline(ifs, input);
	//input = "540162997 705949 794 1000000000 3466311 601139 38172 73045 92 99 46087528 1000000000 4876 25150656 1059 16 1000000000 29 318352140 7 548714 86 1838944";
	//input = "1 99 100 4";
	vector<string> tokens = split(input, ' ');
	//N = tokens.size();
    int *a = (int*)malloc(N*sizeof(int));
    //int a[1000000];
	for(int i=0; i<N;i++)
		a[i] = atoi(tokens[i].c_str());
#else
    int *a = (int*)malloc(N*sizeof(int));
	for(int i=0; i<N; i++)
		cin >> a[i];
#endif
	cache = new IntArray[2*(N+1)];
	nCache = N+1;

	bool bFound = false;
	int iLast = -1;
	int idelta = 400;
	int iFirst = idelta;
	if(N<2) {
		cout << 0 << endl;
		free(a);
		return 0;
	}
	if(N<idelta)
		iFirst = N-1;
    clock_t begin = clock();
    clock_t end;
    double elapsed_secs;
#if 1
    iLast = getModifyNumbers(a, N);
   // iLast = lnds(a, N);
#else
    
	for(int i=iFirst; i<N && !bFound; i+=idelta) {
		int iCur = modifyseq(a, N, i);
		if(iLast == iCur)
			bFound = true;
		else
			iLast = iCur;
        bFound = true;
		idelta = idelta/2;
	}
#endif
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << iLast << endl;
    cout << "Run time: " << elapsed_secs << "s" << endl;
    free(a);
    delete[] cache;
    return 0;
}

