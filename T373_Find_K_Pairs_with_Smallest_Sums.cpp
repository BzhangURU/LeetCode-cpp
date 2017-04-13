/*You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

Define a pair (u,v) which consists of one element from the first array and one element from the second array.

Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:
Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3

Return: [1,2],[1,4],[1,6]

The first 3 pairs are returned from the sequence:
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
Example 2:
Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2

Return: [1,1],[1,1]

The first 2 pairs are returned from the sequence:
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
Example 3:
Given nums1 = [1,2], nums2 = [3],  k = 3 

Return: [1,3],[2,3]

All possible pairs are returned from the sequence:
[1,3],[2,3]*/


class Solution {
public:
    struct mycompare373{
    	bool operator()(vector<int> a,vector<int> b){
    		//a[0] is nums1[i], a[1] is nums2[j],  a[2] is j,  every time heap delete it, add (nums1[i], nums2[j+1], j+1) to it
    		return a[0]+a[1]<b[0]+b[1];
    	}
    };
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int,int>> result;
    	if(k<=0)
    		return result;
    	if(nums1.size()==0||nums2.size()==0)
    		return result;
    	multiset<vector<int>,mycompare373> heap;
    	for(int i=0;i<k;i++){
    		vector<int> new_v;
    		new_v.push_back(nums1[i]);
    		new_v.push_back(nums2[0]);
    		new_v.push_back(0);
    		heap.insert(new_v);
    	}
    	for(int i=0;i<k;i++){
    		if(heap.size()==0)
    			break;
    
    		vector<int> v_result;
    		v_result.push_back((*heap.begin())[0]);
    		v_result.push_back((*heap.begin())[1]);
    		v_result.push_back((*heap.begin())[2]);
    		heap.erase(heap.begin());
    		result.push_back(make_pair(v_result[0],v_result[1]));
    		if(v_result[2]<nums2.size()-1){
    			v_result[2]++;
    			v_result[1]=nums2[v_result[2]];
    			heap.insert(v_result);
    		}
    	}
    	
    	return result;
    }
};
