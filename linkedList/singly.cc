struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  // https://leetcode.com/problems/remove-nth-node-from-end-of-list/
  ListNode* removeNthFromEnd(ListNode* head, int n);
  // https://leetcode.com/problems/remove-linked-list-elements/
  ListNode* removeElements(ListNode* head, int val);
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

ListNode* Solution::removeElements(ListNode* head, int val) {
  if (head == nullptr) return nullptr;
  while (head->val == val) {
    ListNode* temp = head->next;
    delete head;
    head = temp;
    if (head == nullptr) return nullptr;
  }
  ListNode* node = head;
  while (node->next) {
    if (node->next->val == val) {
      ListNode* temp = node->next->next;
      delete node->next;
      node->next = temp;
    } else {
      node = node->next;
    }
  }
  return head;
}

