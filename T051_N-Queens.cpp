class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
		if(n<=0)
			return result;
		if(n==1){
			vector<string> v;
			v.push_back("Q");
			result.push_back(v);
			return result;
		}

		vector<int> queen_cols;
		solve(result,n,queen_cols);
		return result;






    }
    
    //each line has just one queen, so just record each queen's column
    void solve(vector<vector<string>>& result,int n,vector<int>& queen_cols){
    	int line=queen_cols.size();
    	if(line==n){
    		vector<string> one_result;
    		//line i
    		for(int i=0;i<n;i++){
    			string str(n,'.');
    			str[queen_cols[i]]='Q';
    			one_result.push_back(str);
    		}
    		result.push_back(one_result);
    	}else{
    		for(int i=0;i<n;i++){
    			if(valid_to_put(queen_cols, i,n)){
    				queen_cols.push_back(i);
    				solve(result,n,queen_cols);
    				queen_cols.pop_back();
    			}
    		}
    	}
    
    
    
    
    }
    bool valid_to_put(vector<int>& queen_cols, int new_col,int n){
    	if(new_col>n-1||new_col<0)
    		return false;
    	int line=queen_cols.size();
    	if(line>n-1)
    		return false;
    	for(int i=0;i<line;i++){
    		if(queen_cols[i]==new_col)
    			return false;
    		if((new_col-queen_cols[i]==line-i)||(queen_cols[i]-new_col==line-i))
    			return false;
    	}
    	return true;
    
    }
};
