/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution
{
  public:
    RandomListNode *copyRandomList(RandomListNode *head)
    {
        unordered_map<RandomListNode *, RandomListNode *> mp;
        mp[nullptr] = nullptr;

        RandomListNode dummy(0);
        RandomListNode *cur = &dummy;
        RandomListNode *temp;
        while (head != nullptr)
        {
            temp = new RandomListNode(head->label);
            temp->random = head->random;
            cur->next = temp;
            cur = temp;
            mp[head] = temp;
            head = head->next;
        }
        cur->next = nullptr;
        cur = dummy.next;
        while (cur != nullptr)
        {
            cur->random = mp[cur->random];
            cur = cur->next;
        }
        return dummy.next;
    }
};