/*Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node 
reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

    Search for a node to remove.
    If the node is found, delete the node.

Note: Time complexity should be O(height of tree).

Example:

root = [5,3,6,2,4,null,7]
key = 3

    5
   / \
  3   6
 / \   \
2   4   7

Given key to delete is 3. So we find the node with value 3 and delete it.

One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

    5
   / \
  4   6
 /     \
2       7

Another valid answer is [5,2,6,null,4,null,7].

    5
   / \
  2   6
   \   \
    4   7
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
    TreeNode* deleteNode(TreeNode* root, int key) {
    	//first find key
    	//if key is found, use next larger num or next smaller num to replace it
    	TreeNode* key_point=NULL;
    	TreeNode* key_parent_point=NULL;
    	find_key(root,key, key_point,key_parent_point);
    	//if key is found
    	if(key_point!=NULL){
    		//if key_node is leaf
    		if(key_point->left==NULL&&key_point->right==NULL){
    			//if key_node is not root
    			if(key_parent_point!=NULL){
    				if(key_parent_point->left!=NULL&&key_parent_point->left->val==key)
    					key_parent_point->left=NULL;
    				else key_parent_point->right=NULL;
    			}else{
    				//if key_node is both leaf and root
    				return NULL;
    			}
    		}else{
    			//if key_node is not leaf
    			TreeNode* replace_point=NULL;
    			TreeNode* replace_parent_point=key_point;
    			if(key_point->right!=NULL){
    				find_replace_in_right_part(key_point->right, replace_point,replace_parent_point);
    				
    					
    				//if replace_point is direct child of key_point
    				if(replace_parent_point->val==key){
    					if(replace_point->right==NULL){
    						key_point->val=replace_point->val;
    						key_point->right=NULL;
    					}else{
    						key_point->val=replace_point->val;
    						key_point->right=replace_point->right;
    					}
    				}else{
    
    					//if replace_point is leaf
    					if(replace_point->right==NULL){
    						key_point->val=replace_point->val;
    						replace_parent_point->left=NULL;
    					}else{
    						key_point->val=replace_point->val;
    						replace_parent_point->left=replace_point->right;
    					}
    				}
    			}else{
    				find_replace_in_left_part(key_point->left, replace_point,replace_parent_point);
                        if(replace_parent_point->val==key){
    					if(replace_point->left==NULL){
    						key_point->val=replace_point->val;
    						key_point->left=NULL;
    					}else{
    						key_point->val=replace_point->val;
    						key_point->left=replace_point->left;
    					}
    				}else{
    
    					//if replace_point is leaf
    					if(replace_point->left==NULL){
    						key_point->val=replace_point->val;
    						replace_parent_point->right=NULL;
    					}else{
    						key_point->val=replace_point->val;
    						replace_parent_point->right=replace_point->left;
    					}
    
    				}
    
    
    
    			}
    
    		}
    
    
    	}
    	return root;
            
     }


    void find_key(TreeNode* node,int key, TreeNode*& key_point, TreeNode*& key_parent_point){
    	
    	while(node!=NULL){
    		if(node->val==key){
    		    key_point=node;
    			return;
    		}else if(key<node->val){
    		    key_parent_point=node;
    			node=node->left;
    			
    		}else{
    		    key_parent_point=node;
    			node=node->right;
    			
    		}
    
    	}
    
    
    
    
    }
    
    
    void find_replace_in_right_part(TreeNode* node, TreeNode*& replace_point, TreeNode*& replace_parent_point){
    	
    	while(true){
    		if(node->left==NULL){
    			replace_point=node;
    			return;
    		}else{
    			replace_parent_point=node;
    			node=node->left;
    		}
    	}
    
    }
    
    
    void find_replace_in_left_part(TreeNode* node, TreeNode*& replace_point, TreeNode*& replace_parent_point){
    	
    	while(true){
    		if(node->right==NULL){
    			replace_point=node;
    			return;
    		}else{
    			replace_parent_point=node;
    			node=node->right;
    		}
    	}
    
    }
};
