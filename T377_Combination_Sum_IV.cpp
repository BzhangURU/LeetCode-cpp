
/*Given an integer array with all positive numbers and no duplicates, find the number of possible combinations 
that add up to a positive integer target.

Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.
Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?*/


class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {

    	unordered_map<int,int> target2num;
    	return count_num(nums,target,target2num);
    
    }
    
    
    int count_num(vector<int>& nums,int target, unordered_map<int,int>& target2num){
    	if(target<0)
    		return 0;
    	else if(target==0)
    		return 1;
    
    	if(target2num.find(target)!=target2num.end())
    		return target2num[target];
    	int count=0;
    	for(int i=0;i<nums.size();i++){
    		count+=count_num(nums,target-nums[i],target2num);
    	}
    	target2num[target]=count;
    	return count;
    	
    }
};
