/*
Given a sorted positive integer array nums and an integer n, add/patch elements to the array such 
that any number in range [1, n] inclusive can be formed by the sum of some elements in the array. 
Return the minimum number of patches required.

Example 1:
nums = [1, 3], n = 6
Return 1.

Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.

Example 2:
nums = [1, 5, 10], n = 20
Return 2.
The two patches can be [2, 4].

Example 3:
nums = [1, 2, 2], n = 5
Return 0.*/
/*My idea: we scan the array from beginning and calculate the accumulated sum, each time if the next element in array is larger than
the sum+1, we add (sum+1) into array*/

class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        if(n<=0)
          return 0;
        long long long_n=(long long)n;
            long long temp_sum=0;
        long long new_add;
        int result=0;
        for(int i=0;i<nums.size();i++){
          while(temp_sum<(long long)nums[i]-1){
            new_add=temp_sum+1;
            temp_sum+=new_add;
            result++;
            if(temp_sum>=long_n)
            return result;
          }
          temp_sum+=nums[i];
          if(temp_sum>=long_n)
            return result;
        }
        while(temp_sum<long_n){
          new_add=temp_sum+1;
            temp_sum+=new_add;
            result++;
            if(temp_sum>=long_n)
            return result;
        }


        return result;
   }
};
