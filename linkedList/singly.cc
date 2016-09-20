struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  // https://leetcode.com/problems/remove-nth-node-from-end-of-list/
  ListNode* removeNthFromEnd(ListNode* head, int n);
};

ListNode* Solution::removeNthFromEnd(ListNode* head, int n) {
  ListNode* temp = head, *prev = head;
  for (int i = 0; i < n; ++i) temp = temp->next;
  if (!temp) {
    temp = head->next;
    delete head;
    return temp;
  }
  while (temp = temp->next) prev = prev->next;
  temp = prev->next->next;
  delete prev->next;
  prev->next = temp;

  return head;
}
