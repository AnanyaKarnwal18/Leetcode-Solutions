/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2){
    ListNode* dummyNode = new ListNode(-1);
    ListNode* res = dummyNode;

    while(list1 != NULL && list2 != NULL){
        if(list1->val <= list2->val){
            res->next = list1;
            list1= list1->next;
        }else{
            res->next = list2;
            list2 = list2->next;
        }
        res = res->next;
    }
    if (list1 != NULL)
      res->next = list1;

      else
        res->next = list2;

    return dummyNode->next;

}




    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty())
        return NULL;

        ListNode* head= lists[0];

        for(int i = 1; i<lists.size();i++){
        head = mergeTwoLists(head,lists[i]);
        }
        return head;
    }
};