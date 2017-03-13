
/* Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution? */


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void recoverTree(TreeNode* root) {
        int min=INT_MAX;
    	int max=INT_MIN;
    	int previous=INT_MIN;
    
    	TreeNode* node_min=root;
    	TreeNode* node_max=root;
    	TreeNode* node_prev=root;
         //in order traversal, find min and max num that seems incorrect
    	stack<TreeNode*> st;
    	TreeNode* node=root;
    	while(!st.empty()||node!=NULL){
    		if(node!=NULL){
    			st.push(node);
    			node=node->left;
    		}else{
    			node=st.top();
    			st.pop();
    			if(node->val<previous&&min==INT_MAX){//first incorrect
    				min=previous;
    				node_min=node_prev;
    			}
    			if(node->val<previous){//last incorrect
    				max=node->val;
    				node_max=node;
    			}
    			previous=node->val;
    			node_prev=node;
    			node=node->right;
    		}
    	}
    	node_min->val=max;
    	node_max->val=min;
    }
};
