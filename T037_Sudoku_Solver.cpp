
//always start with a cell that is strictly constrained
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        
	int num_vacancies=0;

	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			if(board[i][j]=='.')
				num_vacancies++;
	solve(board,num_vacancies);
				

}
bool solve(vector<vector<char>>& board,int num_vacancies){
	//try to find a cell where only one number can be fit into, in that place, min_num==1
  //if there is none, try to find min_num==2
	
	if(num_vacancies!=0){
	    int min_num=10,min_i,min_j;
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++){
			    if(board[i][j]!='.')
					continue;
				vector<char> vec=valid_num_vector(board,i, j);
				if(vec.size()<min_num){
					min_num=vec.size();
					min_i=i;
					min_j=j;
				}
			}
		if(min_num==0)
			return false;
		vector<char> vec_min=valid_num_vector(board,min_i, min_j);
		for(int ind=0;ind<vec_min.size();ind++){
			board[min_i][min_j]=vec_min[ind];
			if(solve(board,num_vacancies-1))
				return true;
			board[min_i][min_j]='.';
			
		}
        return false;

	}else return true;
}





//show valid numbers to fill in the pixel,don't check whether this sudoku is valid or not
vector<char> valid_num_vector(vector<vector<char>>& board,int line, int col){
	vector<char> nums;
	bool used[9];
	for(int i=1;i<=9;i++)
		used[i-1]=false;
	for(int c=0;c<9;c++){
		if(board[line][c]!='.')
			used[board[line][c]-'1']=true;
	}
	for(int c=0;c<9;c++){
		if(board[c][col]!='.')
			used[board[c][col]-'1']=true;
	}
	int x,y;
	for(int m=0;m<3;m++)
		for(int n=0;n<3;n++){
		    
			x=m+3*(line/3);
			y=n+3*(col/3);
			if(board[x][y]!='.')
			used[board[x][y]-'1']=true;
		}
	for(int i=1;i<=9;i++)
		if(!used[i-1])
			nums.push_back('0'+i);
	return nums;
}
};
