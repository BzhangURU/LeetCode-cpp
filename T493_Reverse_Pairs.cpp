/*Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].

You need to return the number of important reverse pairs in the given array.

Example1:

Input: [1,3,2,3,1]
Output: 2
Example2:

Input: [2,4,3,5,1]
Output: 3
Note:
The length of the given array will not exceed 50,000.
All the numbers in the input array are in the range of 32-bit integer.*/

class Solution {
public:
      //merge sort
      //count the total inside interval[start, ending], 
     //they include three parts: 1: all inside[start, middle] 2. all inside [middle+1,ending]  3. one in [start, middle], the other in [middle+1,ending]
     int count_while_merging(vector<int>& nums, int start, int ending){
    	if(start>=ending)
    		return 0;
    	int middle=(start+ending)/2;
    	int count=count_while_merging(nums,start, middle)+count_while_merging(nums,middle+1, ending);
    	int left_pointer=start,right_pointer=middle+1;
    	for(;left_pointer<=middle;left_pointer++){
    		while(right_pointer<=ending&&(long long)nums[left_pointer]>(long long)nums[right_pointer]*2)
    			right_pointer++;
    
    		//now right_pointer is the beginning of no important reverse pair
    		count+=right_pointer-(middle+1);
    
    	}
    	//now sort left half and right half
    	left_pointer=start;
    	right_pointer=middle+1;
    	vector<int> temp(ending-start+1);
    	int temp_pointer=0;
    	while(left_pointer<=middle||right_pointer<=ending){
    		if(right_pointer>ending)
    			temp[temp_pointer++]=nums[left_pointer++];
    		else if(left_pointer>middle)
    			temp[temp_pointer++]=nums[right_pointer++];
    		else if(nums[left_pointer]<nums[right_pointer])
    			temp[temp_pointer++]=nums[left_pointer++];
    		else temp[temp_pointer++]=nums[right_pointer++];
    	}
    	for(int i=0;i<ending-start+1;i++)
    		nums[i+start]=temp[i];
    	return count;
    
    
    }
    
    
    int reversePairs(vector<int>& nums) {
            return count_while_merging(nums,0,nums.size()-1);
    }
};
