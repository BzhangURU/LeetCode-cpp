/*You have a number of envelopes with widths and heights given as a pair of integers (w, h). One envelope can fit into another 
if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Example:
Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).*/


class Solution {
public:
    struct mycompare{
    	bool operator()(pair<int,int> a,pair<int,int> b){
    		if(a.first!=b.first)
    			return (a.first<b.first);
    		else return (a.second>b.second);
    	}
    }myobject;
    
    int longest_increasing_subsequence(vector<int> nums){
    	int L=nums.size();
    	if(L==0)
    		return 0;
    	else if(L==1)
    		return 1;
    	vector<int> B;//the j the element in B is the largest A[i](first element of sequence) we have seen so far that L[i]>=j
    	B.push_back(nums[L-1]);
    	for(int i=L-2;i>=0;i--){
    		if(nums[i]>B[0])
    			B[0]=nums[i];
    		else if(nums[i]<B[B.size()-1])
    			B.push_back(nums[i]);
    		else{//find max in B that is strictly smaller than nums[i]
    			int left=0,right=B.size()-1,middle;
    			while(left+1<right){//decreasing sequence
    				middle=left+(right-left)/2;
    				if(B[middle]>=nums[i])
    					left=middle;
    				else right=middle;
    			}
    			if(B[right]<nums[i]&&B[left]>nums[i])
    				B[right]=nums[i];
    		}
    	}
    	return B.size();
    }
    
    
    
    
    //int maxEnvelopes(vector<int>& envelopes) {
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
       //sort(envelopes.begin(),envelopes.end());
    	sort(envelopes.begin(),envelopes.end(),myobject);
    	vector<int> nums(envelopes.size());
    	for(int i=0;i<envelopes.size();i++)
    		nums[i]=envelopes[i].second;
    	return longest_increasing_subsequence(nums);
    }
};
