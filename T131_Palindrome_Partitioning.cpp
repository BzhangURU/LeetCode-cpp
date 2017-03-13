/* Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
  ["aa","b"],
  ["a","a","b"]
]
*/
class Solution {
public:
    void T131_solve(vector<vector<string>>& result, string s, int start_ind,vector<string>& cur_result, vector<int>& P){//T.size() is larger than s.size()
    	if(start_ind==s.size()){
    		vector<string> one_result(cur_result);
    		result.push_back(one_result);
    		return;
    	}
    	//end_ind is included
    	int center;
    	for(int end_ind=start_ind;end_ind<s.size();end_ind++){
    		center=start_ind+end_ind;
    		//check whether [start_ind,end_ind] is palindrome
    		
    		
    		if(P[center]>=2*end_ind-center){
    			cur_result.push_back(s.substr(start_ind,end_ind-start_ind+1));
    			T131_solve(result,s,end_ind+1,cur_result,P);
    			cur_result.pop_back();
    		}
    	}
    
    
    
    
    }
    
    //inspired by T005 Longest Palindromic Substring
    vector<vector<string>> partition(string s) {
    	vector<vector<string>> result;
    	if(s.size()==0)
    		return result;
    
    	//center of palindrome may be between letters
    	//is string is abd, T is just a#b#c 
    	vector<int> T(2*s.size()-1);
    	for(int i=0;i<s.size();i++)
    	{
    		T[2*i]=(int)s[i];
    	}
    	//P[i] is the longest length of palindrome with center at i
    	//a#b#c#b#a   P[i is at c]=4(4 is length of #b#a)
    	vector<int> P(T.size());
    	P[0]=0;
    	//C is center(that reaches farest right end), R is the right end we explored, we start from left end
    	int C=0, R=0;
    			
    	for(int i=1;i<T.size()-1;i++)
    	{
    		int mirr=2*C-i;//mirr is the mirror point symmetric with i with center at C
    				
    		if(i<R)
    			P[i]=min(R-i, P[mirr]);//R-i   ---> to prevent reach the end of string
    				
    		if(!(i-(P[i])==0||i+(P[i])==T.size()-1))
    			{
    			while(T[i+(1+P[i])]==T[i-(1+P[i])])
    				{
    					P[i]++;
    					if(i-(P[i])==0||i+(P[i])==T.size()-1)
    						break;
    				}
    			}
    		//if we explore righter of right end, update
    		if(i+P[i]>R)
    		{
    			C=i;
    			R=i+P[i];
    		}
    	}
    	vector<string> cur_result;
    	T131_solve(result,s, 0,cur_result, P);
    	return result;
    
    }
};
