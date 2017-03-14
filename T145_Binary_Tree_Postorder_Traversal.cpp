/*Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
		if(root==NULL)
			return result;
		TreeNode* previous_node=NULL;
		TreeNode* node=root;
		stack<TreeNode*> st;
		while(!st.empty()||node!=NULL){
			if(node!=NULL){
				st.push(node);
				node=node->left;
			}else{
				node=st.top();
				if(node->right!=NULL&&previous_node!=node->right){
					node=node->right;
				}else{
					st.pop();
					result.push_back(node->val);
					previous_node=node;
					node=NULL;
				}
			}
		}
		return result;
}
