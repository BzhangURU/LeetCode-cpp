

/*You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7
*/
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> stack1,stack2,stack_result;
		ListNode* node1=l1;
		ListNode* node2=l2;
		while(node1!=NULL){
			stack1.push(node1->val);
			node1=node1->next;
		}
		while(node2!=NULL){
			stack2.push(node2->val);
			node2=node2->next;
		}
		int carry=0,num1,num2,num_result;
		while(!stack1.empty()||!stack2.empty()){
			if(stack1.empty())
				num1=0;
			else{
				num1=stack1.top();
				stack1.pop();
			}
			if(stack2.empty())
				num2=0;
			else{
				num2=stack2.top();
				stack2.pop();
			}
			num_result=num1+num2+carry;
			carry=num_result/10;
			num_result=num_result%10;
			stack_result.push(num_result);
		}
		if(carry!=0)
			stack_result.push(carry);
		ListNode* root=new ListNode(-1);
		ListNode* node=root;
		while(!stack_result.empty()){
			ListNode* new_node=new ListNode(stack_result.top());
			stack_result.pop();
			node->next=new_node;
			node=node->next;
		}
		return root->next;
    }
};
