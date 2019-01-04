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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
    // The key is how to instantiate a priority queue
        auto cmp = [](ListNode* a, ListNode* b){return a->val > b->val;};
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq_elements(cmp);
    // end
        for(auto node_ptr:lists){
            if(node_ptr!=nullptr){
                pq_elements.push(node_ptr);
            }
        }
        ListNode dummy(0);
        ListNode* current = &dummy;
        while(!pq_elements.empty()){
            ListNode* nextNode = pq_elements.top();
            pq_elements.pop();
            current->next = nextNode;
            current = nextNode;
            if(nextNode->next!=nullptr){
                pq_elements.push(nextNode->next);
            }
        }
        current->next = nullptr;
        return dummy.next;
    }
};
