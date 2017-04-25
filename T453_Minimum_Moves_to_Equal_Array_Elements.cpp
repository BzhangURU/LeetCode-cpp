/*Given a non-empty integer array of size n, find the minimum number of moves required to make all array 
elements equal, where a move is incrementing n - 1 elements by 1.

Example:

Input:
[1,2,3]

Output:
3

Explanation:
Only three moves are needed (remember each move increments two elements):

[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]*/
int minMoves(vector<int>& nums) {
	if(nums.size()<=1)
		return 0;
	long long num0=nums[0];
	long long min=INT_MAX;
	long long sum=0;
	for(int i=1;i<nums.size();i++){
		sum+=(long long)nums[i]-num0;
		if(min>nums[i])
			min=nums[i];
	}
	sum+=(num0-min)*nums.size();
	return sum;
}
