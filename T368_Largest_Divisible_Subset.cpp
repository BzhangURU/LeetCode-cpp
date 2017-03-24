/* Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.

If there are multiple solutions, return any subset is fine.

Example 1:

nums: [1,2,3]

Result: [1,2] (of course, [1,3] will also be ok)

Example 2:

nums: [1,2,4,8]

Result: [1,2,4,8]
*/
class Solution {
public:
    void get_largest_divisible_subset(vector<int>& result, vector<int>& cur_vector, vector<int>& nums,int last_element_ind,vector<vector<int>>& map){
    	if(map[last_element_ind].size()==0){
    		if(result.size()<cur_vector.size()){
    			result.clear();
    			copy(cur_vector.begin(),cur_vector.end(),back_inserter(result));
    		}
    		return;
    	}
    	for(int i=0;i<map[last_element_ind].size();i++){
    		cur_vector.push_back(nums[map[last_element_ind][i]]);
    		get_largest_divisible_subset(result, cur_vector, nums,map[last_element_ind][i],map);
    		cur_vector.pop_back();
    	}
    
    }
    
    
    //one number is a multiple of another
    //my idea: get link vector, for any num, get num->{num1,num2,num3...}(They are all larger than num)
    vector<int> largestDivisibleSubset(vector<int>& nums) {
            bool has_1=false;//one would be especially considered
    		//sort
    		sort(nums.begin(),nums.end());
    		vector<vector<int>> map(nums.size());
    		vector<bool> can_be_used_as_head(nums.size());
    		for(int i=0;i<nums.size();i++){
    			can_be_used_as_head[i]=true;
    		}
    		for(int dif=1;dif<nums.size();dif++){
    			for(int i=0;i+dif<nums.size();i++)
    				if(nums[i+dif]%nums[i]==0){
    					int middle;
    					for(middle=i+1;middle<i+dif;middle++){
    						//if there are 1 4 8, then do not link 1 and 8!!!!!!!!!!!!
    						if(nums[middle]%nums[i]==0&&nums[i+dif]%nums[middle]==0)
    							break;
    					}
    					if(middle==i+dif){
    						map[i].push_back(i+dif);
    					}
    					can_be_used_as_head[i+dif]=false;
    				}
    		}
    		vector<int> result;
    		for(int i=0;i<nums.size();i++){
    			if(can_be_used_as_head[i]){
    				vector<int> cur_vector;
    				cur_vector.push_back(nums[i]);
    				get_largest_divisible_subset(result,cur_vector,nums,i,map);
    			}
    		}
    		
    		return result;
    
    
    }

};
