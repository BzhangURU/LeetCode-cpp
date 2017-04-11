/*Given several boxes with different colors represented by different positive numbers. 
You may experience several rounds to remove boxes until there is no box left. Each time you can 
choose some continuous boxes with the same color (composed of k boxes, k >= 1), remove them and get k*k points.
Find the maximum points you can get.

Example 1:
Input:

[1, 3, 2, 2, 2, 3, 4, 3, 1]
Output:
23
Explanation:
[1, 3, 2, 2, 2, 3, 4, 3, 1] 
----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
----> [1, 3, 3, 3, 1] (1*1=1 points) 
----> [1, 1] (3*3=9 points) 
----> [] (2*2=4 points)
Note: The number of boxes n would not exceed 100.*/


class Solution {
public:
    //num_before_start is number of continuous boxes with same color of boxes[start]
    int points(int dp[100][100][100],int start, int ending, int num_before_start,vector<int>& boxes, vector<int>& ind2length){
    	if(start>ending)
    		return 0;
    	if(start==ending)
    		return (num_before_start+1)*(num_before_start+1);
    	if(dp[start][ending][num_before_start]!=0)
    		return dp[start][ending][num_before_start];
    	int new_length=ind2length[start];
    
    	int result=points(dp,start+new_length,ending,0,boxes,ind2length)+(num_before_start+new_length)*(num_before_start+new_length);
    	for(int i=start+1;i<=ending;i++){
    		if(ind2length[i]>0&&boxes[i]==boxes[start]){
    			int temp_result=points(dp,start+new_length,i-1,0,boxes,ind2length)+points(dp,i,ending,num_before_start+new_length,boxes,ind2length);
    			result=max(temp_result,result);
    		}
    	}
    
    	dp[start][ending][num_before_start]=result;
    	return result;
    
    
    }
    
    
    int removeBoxes(vector<int>& boxes){
    	if(boxes.size()==0)
    		return 0;
    	//show length of each continuous boxes with the same color
    	//for example: if boxes are:   3 3 3 5 5 3 5, then ind2length[0]=3(there are three 3), 
    	//ind2length[3]=2(two 5), ind2length[5]=1, ind2length[6]=1, all others are -1
    	vector<int> ind2length(boxes.size(),-1);
    	int temp_ind=0;
    	ind2length[temp_ind]=1;
    	for(int i=1;i<boxes.size();i++){
    		if(boxes[i]==boxes[i-1]){
    			ind2length[temp_ind]++;
    		}else{
    			temp_ind=i;
    			ind2length[temp_ind]=1;
    		}
    	}
        int dp[100][100][100]={0};
    	/*vector<vector<vector<int>>> dp;
    	for(int ind1=0;ind1<boxes.size();ind1++){
    		vector<vector<int>> vv;
    		for(int ind2=0;ind2<boxes.size();ind2++){
    			vector<int> new_v(boxes.size(),0);
    			vv.push_back(new_v);
    		}
    		dp.push_back(vv);
    	}*/
    	
    	return points(dp,0,boxes.size()-1,0,boxes,ind2length);
    
    
    }
};
