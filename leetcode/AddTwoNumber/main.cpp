#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <time.h>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

void printListNode(ListNode *l) 
{
	cout << "[";
	while(l) {
		cout << l->val;
		l = l->next;
		if(l)
			cout << ",";
	}
	cout << "]\n";
}

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int promote = 0;
		ListNode* p1 = l1;
		ListNode* p2 = l2;
		ListNode* pRet = l1;
		ListNode* pLast = pRet;
		bool bMoved = false;
		while(1) {
			int v1 = l1 ? l1->val : 0;
			int v2 = l2 ? l2->val : 0;
			int v = v1 + v2 + promote;
			if(v<10)
				promote = 0;
			else {
				v -= 10;
				promote = 1;
			} 			
			if(l1) {
				l1->val = v;
				pLast = l1;
			} else {
				if(!bMoved) {
					pLast->next = l2;
					bMoved = true;
				}
				l2->val = v;
				pLast = l2;
			}
			if(l1)
				l1 = l1->next;
			if(l2)
				l2 = l2->next;
			if(!l1 && !l2)
				break;
		}
		if(promote) {
			ListNode *pNode = new ListNode(promote);
			pLast->next = pNode;
		}		
		return pRet;
    }
};

ListNode* getInput()
{
	char token;
	cin >> token;
	ListNode *pH = NULL;
	ListNode *pN = pH;
	while (token != ']')
	{
		cin >> token;
		if (token >= '0' && token <= '9')
		{
			ListNode *pNode = new ListNode(token - '0');
			if(!pH){
				pH = pNode;
				pN = pNode;
			} else {
				pN->next = pNode;
				pN = pN->next;
			}
		}
	}
	return pH;
}

int main()
{
	ListNode* p1 = getInput();
	ListNode* p2 = getInput();

    clock_t begin = clock();
    clock_t end;
    double elapsed_secs;
	Solution a;
	printListNode(a.addTwoNumbers(p1, p2));
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Run time: " << elapsed_secs << "s" << endl;
    return 0;
}

