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
  // https://leetcode.com/problems/reverse-linked-list/
  ListNode* reverseList(ListNode* head);
  // https://leetcode.com/problems/palindrome-linked-list/
  bool isPalindrome(ListNode* head);
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

ListNode* Solution::reverseList(ListNode* head) {
  if (head == nullptr) return nullptr;
  ListNode* node = head->next;
  head->next = nullptr;
  while (node) {
    ListNode* temp = node->next;
    node->next = head;
    head = node;
    node = temp;
  }
  return head;
}


// We want an algorithm with O(n) time and O(1) space
bool Solution::isPalindrome(ListNode* head) {
  if (head == nullptr || head->next == nullptr) return true;
  if (head->next->next == nullptr) return head->val == head->next->val;
  ListNode* fastptr(head), slowptr(head->next), revptr(head);
  while (fastptr->next->next->next) { // need to be fixed
    fastptr = fastptr->next->next;
    ListNode* temp = slowptr->next;
    slowptr->next = revptr;
    revptr = slowptr;
    slowptr = temp;
  }
  bool is_palindrome = true;
  ListNode* revlag = slowptr;
  if (fastptr->next->next) {
    is_palindrome = slowptr->val == slowptr->next->val;
    slowptr = slowptr->next->next;
  }
  while (revptr != head) {
    ListNode* temp = revptr->next;
    revptr->next = revlag;
    revlog = revptr;
    revptr = temp;
  
  }

  return is_palindrome;
}
