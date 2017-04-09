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
/*
void autoRemoveBalls(string& board){
	int length=board.size();
	int count=1;
	int new_length=-1;
	while(length!=new_length){
		length=board.size();
		for(int i=1;i<=length;i++){
			if(i==length){
				if(count>=3){
					board=board.substr(0,length-count);
				}
			}else if(board[i]!=board[i-1]){
				if(count>=3){
					board=board.substr(0,i-count)+board.substr(i,length-i);
					break;
				}
				count=1;
			}else count++;
		}
		new_length=board.size();
		;
	}
}*/


void autoRemoveBalls(vector<char>& board){
	int length=board.size();
	
	int new_length=-1;
	cout<<"auto remove balls"<<endl;
	while(length!=new_length){
		int count=1;
		for(int k=0;k<board.size();k++)
			cout<<board[k];
		cout<<endl;
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

//my rule: never put color A between A and A
/*int find_min_step(string& myboard,vector<char>& chars,unordered_map<char,int>& char2ind,vector<int>& charind_num){
	autoRemoveBalls(myboard);
	cout<<myboard<<endl;
	if(myboard.size()==0)
		return 0;
	if(!still_balls_in_hand(charind_num))
		return INT_MAX/2;

	int min_step=INT_MAX/2;
	int step;
	for(int i=0;i<=myboard.size();i++){//insert place
		if(i==0){
			for(int ind=0;ind<5;ind++){
				if(charind_num[ind]>0&&myboard[0]!=chars[ind]){
					charind_num[ind]--;
					myboard=chars[ind]+myboard;
					step=1+find_min_step(myboard,chars,char2ind,charind_num);
					if(step<min_step)
						min_step=step;
					charind_num[ind]++;
					myboard=myboard.substr(1,myboard.size()-1);
				}
			}
		}else if(i==myboard.size()){
			for(int ind=0;ind<5;ind++){
				if(charind_num[ind]>0){
					charind_num[ind]--;
					myboard=myboard+chars[ind];
					step=1+find_min_step(myboard,chars,char2ind,charind_num);
					if(step<min_step)
						min_step=step;
					charind_num[ind]++;
					myboard=myboard.substr(0,myboard.size()-1);
				}
			}
		}else{
			for(int ind=0;ind<5;ind++){
				if(charind_num[ind]>0&&(myboard[i]!=chars[ind])){
					charind_num[ind]--;
					myboard=myboard.substr(0,i)+chars[ind]+myboard.substr(i,myboard.size()-i);
					step=1+find_min_step(myboard,chars,char2ind,charind_num);
					if(step<min_step)
						min_step=step;
					charind_num[ind]++;
					myboard=myboard.substr(0,i)+myboard.substr(i+1,myboard.size()-1-i);
				}
			}
		}
	}



	
	return min_step;

}*/

int find_min_step(vector<char>& myboard,vector<char>& chars,unordered_map<char,int>& char2ind,vector<int>& charind_num){
	autoRemoveBalls(myboard);
	for(int i=0;i<myboard.size();i++)
		cout<<myboard[i];
	cout<<"       balls in hand:  ";
	for(int j=0;j<5;j++)
		cout<<charind_num[j]<<"  ";

	if(still_balls_in_hand(charind_num))
		cout<<"still balls in hand";
	else cout<<"no balls in hand";
	cout<<endl;
	
	if(myboard.size()==0)
		return 0;
	if(!still_balls_in_hand(charind_num))
		return INT_MAX/2;

	int min_step=INT_MAX/2;
	int step;
	for(int i=0;i<=myboard.size();i++){//insert place
		if(i==0){
			for(int ind=0;ind<5;ind++){
				if(charind_num[ind]>0&&myboard[0]!=chars[ind]){
					charind_num[ind]--;
					//myboard=chars[ind]+myboard;
					vector<char> myboard_copy(myboard);
					myboard_copy.insert(myboard_copy.begin(),chars[ind]);
					step=1+find_min_step(myboard_copy,chars,char2ind,charind_num);
					if(step<min_step)
						min_step=step;
					charind_num[ind]++;
					//myboard=myboard.substr(1,myboard.size()-1);
					//myboard.erase(myboard.begin());
				}
			}
		}else if(i==myboard.size()){
			for(int ind=0;ind<5;ind++){
				if(charind_num[ind]>0){
					charind_num[ind]--;
					//myboard=myboard+chars[ind];
					//myboard.push_back(chars[ind]);
					vector<char> myboard_copy(myboard);
					myboard_copy.push_back(chars[ind]);
					step=1+find_min_step(myboard_copy,chars,char2ind,charind_num);
					if(step<min_step)
						min_step=step;
					charind_num[ind]++;
					//myboard=myboard.substr(0,myboard.size()-1);
					//myboard.pop_back();
				}
			}
		}else{
			for(int ind=0;ind<5;ind++){
				if(charind_num[ind]>0&&(myboard[i]!=chars[ind])){
					charind_num[ind]--;
					//myboard=myboard.substr(0,i)+chars[ind]+myboard.substr(i,myboard.size()-i);
					//myboard.insert(myboard.begin()+i,chars[ind]);
					vector<char> myboard_copy(myboard);
					myboard_copy.insert(myboard_copy.begin()+i,chars[ind]);
					step=1+find_min_step(myboard_copy,chars,char2ind,charind_num);
					if(step<min_step)
						min_step=step;
					charind_num[ind]++;
					//myboard=myboard.substr(0,i)+myboard.substr(i+1,myboard.size()-1-i);
					//myboard.erase(myboard.begin()+i);
				}
			}
		}
	}



	
	return min_step;

}


//just put ball after same color balls, can not handle :
//I tried case "RRWWRRBBRR", "WB". The test program gave the expected answer -1. However, I thought the answer might be 2. Because:
//RRWWRRBBRR -> RRWWRRBBR[W]R -> RRWWRRBB[B]RWR -> RRWWRRRWR -> RRWWWR -> RRR -> empty
//The possible reason might be the first [W] was inserted but not adjacent to a W in the sequence. I read the description twice but didn't find any condition about it.
int find_min_step_easy_ver(vector<char>& myboard,vector<char>& chars,unordered_map<char,int>& char2ind,vector<int>& charind_num){
	autoRemoveBalls(myboard);
	for(int i=0;i<myboard.size();i++)
		cout<<myboard[i];
	cout<<"       balls in hand:  ";
	for(int j=0;j<5;j++)
		cout<<charind_num[j]<<"  ";

	if(still_balls_in_hand(charind_num))
		cout<<"still balls in hand";
	else cout<<"no balls in hand";
	cout<<endl;
	
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
				charind_num[char2ind[myboard[i]]]-=(3-count);
				//myboard=myboard+chars[ind];
				//myboard.push_back(chars[ind]);
				vector<char> myboard_copy(myboard);
				myboard_copy.push_back(myboard[i]);
				if(3-count==2)
					myboard_copy.push_back(myboard[i]);
				step=1+find_min_step_easy_ver(myboard_copy,chars,char2ind,charind_num);
				if(step<min_step)
					min_step=step;
				charind_num[char2ind[myboard[i]]]+=(3-count);
			}


		}else{
			
			if(myboard[i]!=myboard[i-1]&&charind_num[char2ind[myboard[i-1]]]>=3-count){
				charind_num[char2ind[myboard[i]]]-=(3-count);
				//myboard=myboard+chars[ind];
				//myboard.push_back(chars[ind]);
				vector<char> myboard_copy(myboard);
				myboard_copy.insert(myboard_copy.begin()+i,3-count,myboard[i]);
				step=1+find_min_step_easy_ver(myboard_copy,chars,char2ind,charind_num);
				if(step<min_step)
					min_step=step;
				charind_num[char2ind[myboard[i]]]+=(3-count);
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
