/*

    Follow up for "Find Minimum in Rotated Sorted Array":
    What if duplicates are allowed?

    Would this affect the run-time complexity? How and why?

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

The array may contain duplicates.*/

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
    	while(left+1<right){
    		if(nums[left]<nums[right])
    			return nums[left];
    		middle=(right+left)/2;
    		if(nums[middle]>nums[left]){
    			left=middle+1;
    		}else if(nums[middle]<nums[left])
    			right=middle;
    		else left++;
    	}
    	return nums[left]<nums[right]?nums[left]:nums[right];
    }
};
