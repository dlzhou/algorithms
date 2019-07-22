/*
 * [25] Reverse Nodes in k-Group
 *
 * https://leetcode.com/problems/reverse-nodes-in-k-group/description/
 *
 * algorithms
 * Hard (36.81%)
 * Total Accepted:    189.7K
 * Total Submissions: 515.3K
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * Given a linked list, reverse the nodes of a linked list k at a time and
 * return its modified list.
 *
 * k is a positive integer and is less than or equal to the length of the
 * linked list. If the number of nodes is not a multiple of k then left-out
 * nodes in the end should remain as it is.
 *
 *
 *
 *
 * Example:
 *
 * Given this linked list: 1->2->3->4->5
 *
 * For k = 2, you should return: 2->1->4->3->5
 *
 * For k = 3, you should return: 3->2->1->4->5
 *
 * Note:
 *
 *
 * Only constant extra memory is allowed.
 * You may not alter the values in the list's nodes, only nodes itself may be
 * changed.
 *
 *
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
  ListNode *reverseKGroup(ListNode *head, int k) {
    if (!head)
      return NULL;
    ListNode *pNode = head;
    ListNode *pHead = pNode;
    ListNode *pLast = NULL;
    ListNode *pNext = NULL;
    ListNode *pPrev = NULL;
    ListNode *pAhead = NULL;
    while (1) {
      int i = 0;
      pHead = pNode;
      pPrev = NULL;
      while (pNode && i < k) {
        pNext = pNode->next;
        pNode->next = pPrev;
        pPrev = pNode;
        pNode = pNext;
        i++;
      }
      if (i <= k - 1) {
        // reverse back
        pNode = pPrev;
        pPrev = NULL;
        while (pNode) {
          pNext = pNode->next;
          pNode->next = pPrev;
          pPrev = pNode;
          pNode = pNext;
        }
        if (pLast)
          pLast->next = pHead;
        if (!pAhead)
          pAhead = pHead;
        break;
      } else {
        if (pLast)
          pLast->next = pPrev;
        if (!pAhead)
          pAhead = pPrev;
        pLast = pHead;
      }
    }
    return pAhead;
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
  int k = 3;
  cin >> k;
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
  ListNode *out = a.reverseKGroup(head, k);
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