/*Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. 
So the median is the mean of the two middle value.

Examples: 
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the 
very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. 
Your job is to output the median array for each window in the original array.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Median
---------------               -----
[1  3  -1] -3  5  3  6  7       1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7       3
 1  3  -1  -3 [5  3  6] 7       5
 1  3  -1  -3  5 [3  6  7]      6
Therefore, return the median sliding window as [1,-1,-1,3,5,6].

Note: 
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.*/

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
		multiset<int> window(nums.begin(),nums.begin()+k);
		
		for(int i=k;i<=nums.size();i++){
			auto iter_middle=next(window.begin(),k/2);
			if(k&1==1)
				result.push_back((double)(*iter_middle));
			else result.push_back(((double)(*iter_middle)+(double)(*(prev(iter_middle,1))))/2);
			
			if(i==nums.size())
				break;

			window.erase(window.find(nums[i-k]));
			window.insert(nums[i]);


		}
		return result;

    }
};
