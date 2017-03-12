class Solution {
public:
    int totalNQueens(int n) {
        
		if(n<=0)
			return 0;
		if(n==1){
			return 1;
		}
		int result_num=0;
		vector<int> queen_cols;
		solve(result_num,n,queen_cols);
		return result_num;






    }
    
    //each line has just one queen, so just record each queen's column
    void solve(int& result_num,int n,vector<int>& queen_cols){
    	int line=queen_cols.size();
    	if(line==n){
    		result_num++;
    	}else{
    		for(int i=0;i<n;i++){
    			if(valid_to_put(queen_cols, i,n)){
    				queen_cols.push_back(i);
    				solve(result_num,n,queen_cols);
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
