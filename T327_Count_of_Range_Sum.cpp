/* Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.

Example:
Given nums = [-2, 5, -1], lower = -2, upper = 2,
Return 3.
The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums are: -2, -1, 2. */
//my idea: first calculate the accumulated sum from beginning, then use Binrary Search Tree to calculate count of range sum
class Solution {
    public: 
    struct BST_Tree{
    	long long val;
    	int count_all_left;//number of nodes on root.left
    	BST_Tree* left;
    	BST_Tree* right;
    	BST_Tree(long long value): val(value),count_all_left(0), left(NULL),right(NULL){}
    };
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        if(nums.size()==0)
			return 0;
		long long lower_l=(long long)lower;
		long long upper_l=(long long)upper;
		vector<long long> sum(nums.size()+1);
		
		sum[0]=0;
		for(int i=0;i<nums.size();i++){
			sum[i+1]=sum[i]+(long long)(nums[i]);
		}

		BST_Tree* root=NULL;
		int count=0;
		int num1,num2;
		for(int i=sum.size()-1;i>=0;i--){
			num1=find_num_lessequal(root,sum[i]+upper_l);//find total number of sum already in tree that is less than or equal to sum[i]+upper
			num2=find_num_less(root,sum[i]+lower_l);//find total number of sum already in tree that is less than sum[i]+lower
			root=build(root,sum[i],0);
			count+=num1-num2;
		}
		return count;
    }
    BST_Tree* build(BST_Tree* root,long long val,int sum_beforeroot){
		if(root==NULL){
			BST_Tree* node=new BST_Tree(val);
			node->count_all_left=0;
			return node;
		}else if(val>=root->val){
			root->right=build(root->right,val,sum_beforeroot+root->count_all_left+(val==root->val?0:1));
		}else{
			root->count_all_left++;
			root->left=build(root->left,val,sum_beforeroot);
		}
		return root;
	}
    int find_num_lessequal(BST_Tree* root,long long threshold){
    	if(root==NULL)
    		return 0;
    	else if(threshold>=root->val)
    		return root->count_all_left+1+find_num_lessequal(root->right,threshold);
    	else return find_num_lessequal(root->left,threshold);
    }
    int find_num_less(BST_Tree* root,long long threshold){
    	if(root==NULL)
    		return 0;
    	else if(threshold>=root->val)
    		return root->count_all_left+(threshold==root->val?0:1)+find_num_less(root->right,threshold);
    	else return find_num_less(root->left,threshold);
    }
};
