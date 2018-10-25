/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
  public:
    ListNode *middleNode(ListNode *head) {
        if (head == nullptr)
            return nullptr;
        ListNode *fast = head, *slow = head;
        while (true) {
            if (fast == nullptr || fast->next == nullptr)
                return slow;
            fast = fast->next;
            if (fast != nullptr)
                fast = fast->next;
            slow = slow->next;
        }
    }
};