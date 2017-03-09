class Solution {
public:
    int findMin(vector<int>& nums) {
        if(nums.size()==0)
    		return 0;
    	if(nums.size()==1)
    		return nums[0];
    
    	int left=0;
    	int right=nums.size()-1;
    	int middle;
    	while(left!=right){
    		if(nums[left]<nums[right])
    			return nums[left];
    		middle=(right+left)/2;
    		if(nums[middle]>nums[left]){
    			left=middle+1;
    		}else if(nums[middle]<nums[left])
    			right=middle;
    		else return nums[left]<nums[right]?nums[left]:nums[right];
    	}
    	return nums[left];
    }
};
