/*
 * [24] Swap Nodes in Pairs
 *
 * https://leetcode.com/problems/swap-nodes-in-pairs/description/
 *
 * algorithms
 * Medium (45.05%)
 * Total Accepted:    323.6K
 * Total Submissions: 718.2K
 * Testcase Example:  '[1,2,3,4]'
 *
 * Given a linked list, swap every two adjacent nodes and return its head.
 *
 * You may not modify the values in the list's nodes, only nodes itself may be
 * changed.
 *
 *
 *
 * Example:
 *
 *
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 *
 *
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <time.h>
#include <vector>
using namespace std;
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
  ListNode *swapPairs(ListNode *head) {
    if (!head)
      return NULL;

    ListNode *pNode = head;
    ListNode *pNode2 = NULL;
    ListNode *pHead = NULL;
    ListNode *pLast = NULL;

    while (1) {
      pNode2 = pNode->next;
      if (pLast && pNode2)
        pLast->next = pNode2;
      else if (pLast)
        pLast->next = pNode;

      ListNode *pTail = NULL;
      if (pNode2)
        pTail = pNode2->next;
      else {
        if (!pHead)
          pHead = pNode;
        break;
      }
      if (!pHead)
        pHead = pNode2;
      pNode2->next = pNode;
      pNode->next = pTail;
      if (!pTail)
        break;

      pLast = pNode;
      pNode = pTail;
    }
    return pHead;
  }
};
#if 1
int main() {
  Solution a;
  vector<int> tests;
  while (1) {
    int test;
    cin >> test;
    if (test == 999)
      break;
    tests.push_back(test);
  }
  ListNode *head = NULL;
  ListNode *pLast = head;
  for (int i = 0; i < tests.size(); i++) {
    ListNode *pNode = new ListNode(tests[i]);
    if (head == NULL)
      head = pNode;
    else if (pLast)
      pLast->next = pNode;
    pLast = pNode;
  }
  //   tests.clear();
  //   while (1) {
  //     int test;
  //     cin >> test;
  //     if (test == 999)
  //       break;
  //     tests.push_back(test);
  //   }
  //   ListNode *head2 = NULL;
  //   ListNode *pLast2 = head2;
  //   for (int i = 0; i < tests.size(); i++) {
  //     ListNode *pNode2 = new ListNode(tests[i]);
  //     if (head2 == NULL)
  //       head2 = pNode2;
  //     else if (pLast2)
  //       pLast2->next = pNode2;
  //     pLast2 = pNode2;
  //   }
  //   tests.clear();
  //   while (1) {
  //     int test;
  //     cin >> test;
  //     if (test == 999)
  //       break;
  //     tests.push_back(test);
  //   }
  //   ListNode *head3 = NULL;
  //   ListNode *pLast3 = head3;
  //   for (int i = 0; i < tests.size(); i++) {
  //     ListNode *pNode3 = new ListNode(tests[i]);
  //     if (head3 == NULL)
  //       head3 = pNode3;
  //     else if (pLast3)
  //       pLast3->next = pNode3;
  //     pLast3 = pNode3;
  //   }
  /*
  string line;
  ifstream myfile("../tests");
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      const char *chInput = line.c_str();
      while (*chInput) {
        if (*chInput == '[') {
          chInput++;
          continue;
        } else if (*chInput == ']') {
          chInput++;
          continue;
        } else if (*chInput == ',') {
          chInput++;
          continue;
        } else if (*chInput == ' ') {
          chInput++;
          continue;
        } else {
          char input[999] = {0};
          int i = 0;
          for (; *chInput == '-' || (*chInput >= '0' && *chInput <= '9');
               chInput++, i++) {
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
  */
  clock_t begin = clock();
  clock_t end;
  double elapsed_secs;
  ListNode *out = a.swapPairs(head);
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Run time: " << elapsed_secs << "s" << endl;
#if 1
  while (out) {
    cout << out->val << endl;
    out = out->next;
  }
#endif

  return 0;
}
#endif