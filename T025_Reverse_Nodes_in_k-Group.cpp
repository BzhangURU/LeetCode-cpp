/* Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5 */
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
        if(k==1||head==NULL)
			return head;
		
        ListNode* beforehead=new ListNode(0);
		beforehead->next=head;

		//last node of previous group
		ListNode * last_group=beforehead;
		//first(before reverse) node of current group
		ListNode* cur_group=head;
		//currently processed node
		ListNode* node=head;
		int count=0;
		while(node!=NULL){
			count++;
			node=node->next;
		}
		node=head->next;

		while(count>=k){
			for(int i=1;i<k;i++){
				cur_group->next=node->next;
				node->next=last_group->next;
				last_group->next=node;
				node=cur_group->next;
				
			}
			if(node==NULL)
				break;
			last_group=cur_group;
			cur_group=node;
			node=node->next;
			count-=k;
		}
		return beforehead->next;
    }
};
