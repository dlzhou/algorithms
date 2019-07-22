/*
 * [21] Merge Two Sorted Lists
 *
 * https://leetcode.com/problems/merge-two-sorted-lists/description/
 *
 * algorithms
 * Easy (47.54%)
 * Total Accepted:    597.8K
 * Total Submissions: 1.3M
 * Testcase Example:  '[1,2,4]\n[1,3,4]'
 *
 * Merge two sorted linked lists and return it as a new list. The new list
 * should be made by splicing together the nodes of the first two lists.
 *
 * Example:
 *
 * Input: 1->2->4, 1->3->4
 * Output: 1->1->2->3->4->4
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
  ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode *h1 = l1;
    ListNode *h2 = l2;
    if (l1 == NULL)
      return l2;
    if (l2 == NULL)
      return l1;
    ListNode *h = h1;
    ListNode *last = NULL;
    bool bHead = false;
    while (l1 && l2) {
      while (l2 && l2->val <= l1->val) {
        if (!bHead) {
          h = h2;
          bHead = true;
        }
        last = l2;
        l2 = l2->next;
      }
      if (l2) {
        if (!bHead) {
          h = h1;
          bHead = true;
        }
        if (last)
          last->next = l1;
        while (l1 && l1->val <= l2->val) {
          last = l1;
          l1 = l1->next;
        }
        if (l1 && last) {
          last->next = l2;
        }
      }
    }
    if (l1 && last)
      last->next = l1;
    else if (l2 && last)
      last->next = l2;
    return h;
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
  tests.clear();
  while (1) {
    int test;
    cin >> test;
    if (test == 999)
      break;
    tests.push_back(test);
  }
  ListNode *head2 = NULL;
  ListNode *pLast2 = head2;
  for (int i = 0; i < tests.size(); i++) {
    ListNode *pNode2 = new ListNode(tests[i]);
    if (head2 == NULL)
      head2 = pNode2;
    else if (pLast2)
      pLast2->next = pNode2;
    pLast2 = pNode2;
  }
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
  ListNode *out = a.mergeTwoLists(head, head2);
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