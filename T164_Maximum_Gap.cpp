class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int N=nums.size();
		if(N<2)
			return 0;
		int max=nums[0],min=nums[0];
		for(int i=1;i<N;i++){
			if(nums[i]>max)
				max=nums[i];
			else if(nums[i]<min)
				min=nums[i];
		}
		if(max==min)
			return 0;
		int interval=(max-min)/(N-1);
		if(interval==0)
			interval=1;
		int bucket_N=(max-min)/interval+1;
			//largest num in one bucket
		vector<int> bucket_largest(bucket_N);
		vector<int> bucket_smallest(bucket_N);
		for(int i=0;i<bucket_N;i++){
			bucket_largest[i]=-1;
			bucket_smallest[i]=-1;
		}

		for(int i=0;i<N;i++){
			int ind=((nums[i]-min)/interval);
			if(bucket_largest[ind]<nums[i])
				bucket_largest[ind]=nums[i];
			if(bucket_smallest[ind]==-1)
				bucket_smallest[ind]=nums[i];
			else if(bucket_smallest[ind]>nums[i])
				bucket_smallest[ind]=nums[i];

		}
		int gap=0;
		int low;
		int scan=0;
		// bucket_largest[scan]!=-1   <=>    bucket_smallest[scan]!=-1
		for(scan=0;scan<bucket_N;scan++){
			
			if(bucket_largest[scan]!=-1){
				low=bucket_largest[scan];
				break;
			}

		}
		scan++;
		for(;scan<bucket_N;scan++){
			
			if(bucket_smallest[scan]!=-1){
				if(gap<bucket_smallest[scan]-low)
					gap=bucket_smallest[scan]-low;
				low=bucket_largest[scan];
			}
			
		}

		return gap;
    }
};
