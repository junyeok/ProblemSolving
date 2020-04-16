#include <iostream>

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

class Solution {
public:
  ListNode* swapPairs(ListNode* head) {
    ListNode* next = head->next;
    if(next == NULL) return head;
    ListNode* start_node = next;
    ListNode* prev = nullptr;
    while(next != NULL) {
      if(prev != nullptr) prev->next = next;
      head->next = next->next;
      next->next = head;
      if(head->next == NULL) {
        break;
      }
      prev = head;
      head = head->next;
      next = head->next;
    }
    return start_node;
  }
};
