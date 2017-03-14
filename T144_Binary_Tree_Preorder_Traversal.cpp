/*Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,2,3].

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
vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
		if(root==NULL)
			return result;
		stack<TreeNode*> st;
		TreeNode* node=root;
		while(node!=NULL||!st.empty()){
			if(node!=NULL){
				result.push_back(node->val);
				if(node->right!=NULL)
					st.push(node->right);
				node=node->left;
			}else{
				node=st.top();
				st.pop();
			}
		}
		return result;


}
