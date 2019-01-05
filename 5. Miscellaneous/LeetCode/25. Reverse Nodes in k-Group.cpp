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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *khead, *newhead, *reversedTail, *prevTail;
        int n;
        ListNode dummy(0);
        prevTail = &dummy;
        khead = head;
        while(true){
            n = sliceKNodes(khead, k, newhead);
            if(n<k){
                prevTail->next = khead;
                break;
            }
            khead = reverseList(khead, reversedTail);
            prevTail->next = khead;
            prevTail = reversedTail;
            khead = newhead;
        }
        return dummy.next;
    }
    
    int sliceKNodes(ListNode* head, int k, ListNode* &newhead){
        ListNode dummy(0);
        dummy.next = head;
        newhead = &dummy;
        int i;
        for(i=0;i<k && newhead->next!=nullptr;i++){
            newhead = newhead->next;
        }
        ListNode* temp = newhead;
        newhead = newhead->next;
        temp->next = nullptr;
        return i;
    }
    
    ListNode* reverseList(ListNode* head, ListNode* & Tail) {
        Tail = head;
        ListNode* temp, * reshead=NULL;
        while(head!=NULL)
        {
            temp=head;
            head=head->next;
            temp->next=reshead;
            reshead=temp;
        }
        return reshead;
    }
};
