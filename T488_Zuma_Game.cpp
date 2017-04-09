/*Think about Zuma Game. You have a row of balls on the table, colored red(R), yellow(Y), blue(B), green(G), and white(W). 
You also have several balls in your hand.

Each time, you may choose a ball in your hand, and insert it into the row (including the leftmost place and rightmost place). 
Then, if there is a group of 3 or more balls in the same color touching, remove these balls. Keep doing this until no more balls 
can be removed.

Find the minimal balls you have to insert to remove all the balls on the table. If you cannot remove all the balls, output -1.

Examples:

Input: "WRRBBW", "RB"
Output: -1
Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW

Input: "WWRRBBWW", "WRBRW"
Output: 2
Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty

Input:"G", "GGGGG"
Output: 2
Explanation: G -> G[G] -> GG[G] -> empty 

Input: "RBYYBBRRB", "YRBGB"
Output: 3
Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty 

Note:
You may assume that the initial row of balls on the table won’t have any 3 or more consecutive balls with the same color.
The number of balls on the table won't exceed 20, and the string represents these balls is called "board" in the input.
The number of balls in your hand won't exceed 5, and the string represents these balls is called "hand" in the input.
Both input strings will be non-empty and only contain characters 'R','Y','B','G','W'.*/


//if there is a group of 3 or more balls in the same color touching, remove these balls.
class Solution {
public:
    void autoRemoveBalls(vector<char>& board){
    	int length=board.size();
    	
    	int new_length=-1;
    	while(length!=new_length){
    		int count=1;
    		length=board.size();
    		for(int i=1;i<=length;i++){
    			if(i==length){
    				if(count>=3){
    					//board=board.substr(0,length-count);
    					board.erase(board.end()-count,board.end());
    				}
    			}else if(board[i]!=board[i-1]){
    				if(count>=3){
    					//board=board.substr(0,i-count)+board.substr(i,length-i);
    					board.erase(board.begin()+i-count,board.begin()+i);
    					break;
    				}
    				count=1;
    			}else count++;
    		}
    		new_length=board.size();
    		
    	}
    }
    
    
    bool still_balls_in_hand(vector<int>& charind_num){
    	for(int i=0;i<5;i++)
    		if(charind_num[i]>0)
    			return true;
    	return false;
    }
    
    
    
    int find_min_step_easy_ver(vector<char>& myboard,vector<char>& chars,unordered_map<char,int>& char2ind,vector<int>& charind_num){
    	autoRemoveBalls(myboard);
    	
    	if(myboard.size()==0)
    		return 0;
    	if(!still_balls_in_hand(charind_num))
    		return INT_MAX/2;
    
    	int min_step=INT_MAX/2;
    	int step;
    	int count=1;
    	for(int i=1;i<=myboard.size();i++){//insert place
    		
    		if(i==myboard.size()){
    			
    			if(charind_num[char2ind[myboard[i-1]]]>=3-count){
    				charind_num[char2ind[myboard[i-1]]]-=(3-count);
    				//myboard=myboard+chars[ind];
    				//myboard.push_back(chars[ind]);
    				vector<char> myboard_copy(myboard);
    				myboard_copy.push_back(myboard[i-1]);
    				if(3-count==2){
    					myboard_copy.push_back(myboard[i-1]);
    					step=2+find_min_step_easy_ver(myboard_copy,chars,char2ind,charind_num);
    				}else
    				    step=1+find_min_step_easy_ver(myboard_copy,chars,char2ind,charind_num);
    				if(step<min_step)
    					min_step=step;
    				charind_num[char2ind[myboard[i-1]]]+=(3-count);
    			}
    
    			break;
    		}else{
    			
    			if(myboard[i]!=myboard[i-1]&&charind_num[char2ind[myboard[i-1]]]>=3-count){
    				charind_num[char2ind[myboard[i-1]]]-=(3-count);
    				vector<char> myboard_copy(myboard);
    				myboard_copy.insert(myboard_copy.begin()+i,3-count,myboard[i-1]);
    				step=3-count+find_min_step_easy_ver(myboard_copy,chars,char2ind,charind_num);
    				if(step<min_step)
    					min_step=step;
    				charind_num[char2ind[myboard[i-1]]]+=(3-count);
    			}
    
    
    
    		}
    		
    		if(myboard[i]==myboard[i-1])
    			count++;
    		else count=1;
    
    
    	}
    
    
    
    	
    	return min_step;
    
    }
    
    
    //my rule: never put color A between A and A, never put color A before A
    int findMinStep(string board, string hand) {
            vector<char> myboard(board.size());
    		for(int i=0;i<board.size();i++)
    			myboard[i]=board[i];
    
    		vector<char> chars(5);
    		chars[0]='R';chars[1]='Y';chars[2]='B';chars[3]='G';chars[4]='W';
    
    		unordered_map<char,int> char2ind;
    		char2ind['R']=0;char2ind['Y']=1;char2ind['B']=2;char2ind['G']=3;char2ind['W']=4;
    
    
    		vector<int> charind_num(5,0);
    		for(int i=0;i<hand.size();i++)
    			charind_num[char2ind[hand[i]]]++;
    
    		int min_step=find_min_step_easy_ver(myboard,chars,char2ind,charind_num);
    		if(min_step>=INT_MAX/2)
    			return -1;
    		else return min_step;
    }
};
