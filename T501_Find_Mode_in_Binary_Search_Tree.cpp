/*Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than or equal to the node's key.
    The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
    Both the left and right subtrees must also be binary search trees.

For example:
Given BST [1,null,2,2],

   1
    \
     2
    /
   2

return [2].

Note: If a tree has more than one mode, you can return them in any order.

Follow up: Could you do that without using any extra space? 
(Assume that the implicit stack space incurred due to recursion does not count). */
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
    vector<int> findMode(TreeNode* root) {
    	vector<int> result;
    	if(root==NULL){
    		return result;
    	}
            int max_fre=0;
    		int cur_fre=0;
    		int cur_num=0;
    		inorder_traversal_getmaxfre(root,max_fre,cur_num,cur_fre);
    		cur_fre=0;
    		cur_num=0;
    		inorder_traversal_get_result(root, result,max_fre,cur_num,cur_fre);
    		return result;
    
    }
    void inorder_traversal_getmaxfre(TreeNode* root, int& max_fre,int& cur_num,int& cur_fre){
    	if(root==NULL)
    		return;
    	inorder_traversal_getmaxfre(root->left,max_fre,cur_num,cur_fre);
    	if(root->val==cur_num){
    		cur_fre++;
    		if(cur_fre>max_fre)
    			max_fre=cur_fre;
    	}else{
    		cur_num=root->val;
    		cur_fre=1;
    		if(cur_fre>max_fre)
    			max_fre=cur_fre;
    	}
    
    	inorder_traversal_getmaxfre(root->right,max_fre,cur_num,cur_fre);
    }
    
    void inorder_traversal_get_result(TreeNode* root, vector<int>& result, int max_fre, int& cur_num,int& cur_fre){
    	if(root==NULL)
    		return;
    	inorder_traversal_get_result(root->left,result, max_fre,cur_num,cur_fre);
    	if(root->val==cur_num){
    		cur_fre++;
    		if(cur_fre==max_fre)
    			result.push_back(cur_num);
    			
    		
    	}else{
    		cur_num=root->val;
    		cur_fre=1;
    		if(cur_fre==max_fre)
    			result.push_back(cur_num);
    			
    	}
    	inorder_traversal_get_result(root->right, result,max_fre,cur_num,cur_fre);
    
    }
    
    
    void T501_implement(){
    	TreeNode node0(1);
    	TreeNode node1(2);
    	node0.right=&node1;
    	TreeNode node2(2);
    	node1.right=&node2;
    	vector<int> answer=findMode(&node0);
    }
};
