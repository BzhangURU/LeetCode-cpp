/*You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
*/
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
    int pathSum(TreeNode* root, int sum) {
		return pathSum_cal(root,sum,false);
    }
    
    int pathSum_cal(TreeNode* root, int sum,bool path_began) {
    		if(root==NULL)
    			return 0;
    		int result=0;
    		if(root->val==sum)
    			result++;
    		if(path_began){
    			result+=pathSum_cal(root->left,sum-root->val,true);
    			result+=pathSum_cal(root->right,sum-root->val,true);
    		}else{
    			result+=pathSum_cal(root->left,sum,false)+pathSum_cal(root->left,sum-root->val,true);
    			result+=pathSum_cal(root->right,sum,false)+pathSum_cal(root->right,sum-root->val,true);
    		}
    		return result;
            
    }
};
