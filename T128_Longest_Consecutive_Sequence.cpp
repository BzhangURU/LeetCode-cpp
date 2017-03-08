/* Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity. */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        //first put nums into hashset
    	unordered_set<int> set;
    	for(int i=0;i<nums.size();i++){
    		if(set.find(nums[i])==set.end())
    			set.insert(nums[i]);
    	}
    	int max=0;
    	//for each element, check its neighbors
    	for(int i=0;i<nums.size();i++){
    		if(set.find(nums[i])==set.end())
    			continue;
    		int smaller=nums[i]-1;
    		int larger=nums[i]+1;
    		while(set.find(smaller)!=set.end()){
    			set.erase(smaller);
    			smaller--;
    		}
    		while(set.find(larger)!=set.end()){
    			set.erase(larger);
    			larger++;
    		}
    		if(larger-smaller-1>max)
    			max=larger-smaller-1;
    
    
    		set.erase(nums[i]);
    	}
    
    	return max;
    }
};
