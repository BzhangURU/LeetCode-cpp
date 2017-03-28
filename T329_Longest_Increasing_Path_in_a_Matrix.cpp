/*Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may 
NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]

Return 4
The longest increasing path is [1, 2, 6, 9].

Example 2:

nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]

Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.*/
class Solution {
public:
    //if a[i][j] is scanned, then it means we already found the longest starting from a[i][j]. So we just add previous with the remaining
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.size()==0)
			return 0;
		if(matrix[0].size()==0)
			return 0;
		int LINE=matrix.size();
		int COL=matrix[0].size();
		vector<vector<int>> save_length;//save the length start from this point, 0 if not scanned
		for(int i=0;i<LINE;i++){
			vector<int> one_line(COL,0);
			save_length.push_back(one_line);
		}
		int max_length=0;
		for(int i=0;i<LINE;i++)
			for(int j=0;j<COL;j++){
				int cur=search(matrix,save_length,i,j,LINE,COL);
				max_length=(max_length<cur?cur:max_length);
			}

		return max_length;
    
    
    
    }
    int search(vector<vector<int>>& matrix,vector<vector<int>>& save_length,int i,int j,int LINE,int COL){
    	if(save_length[i][j]>0)
    		return save_length[i][j];
    	int length=1;//length is at least 1
    	if(i>0&&matrix[i][j]<matrix[i-1][j]){
    		int up=1+search(matrix,save_length,i-1,j,LINE,COL);
    		length=length<up?up:length;
    	}
    	if(i<LINE-1&&matrix[i][j]<matrix[i+1][j]){
    		int down=1+search(matrix,save_length,i+1,j,LINE,COL);
    		length=length<down?down:length;
    	}
    	if(j>0&&matrix[i][j]<matrix[i][j-1]){
    		int left=1+search(matrix,save_length,i,j-1,LINE,COL);
    		length=length<left?left:length;
    	}
    	if(j<COL-1&&matrix[i][j]<matrix[i][j+1]){
    		int right=1+search(matrix,save_length,i,j+1,LINE,COL);
    		length=length<right?right:length;
    	}
    	save_length[i][j]=length;
    	return length;
    }
};
