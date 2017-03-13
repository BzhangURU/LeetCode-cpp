/* Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut. */

class Solution {
public:
    int minCut(string s) {
       
    	if(s.size()==0)
    		return 0;
    	if(s.size()==1)
    		return 0;
    	 //int mincut=s.size();
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
    	//C is center(that reaches farest right end), R is the right end we explored, we start from left end
    	int C=0, R=0;
    	P[0]=0;
    	for(int i=1;i<T.size()-1;i++)
    	{
    		int mirr=2*C-i;//mirr is the mirror point symmetric with i with center at C
    				
    		if(i<R)
    			P[i]=min(R-i, P[mirr]);//R-i--- to prevent reach the end of string
    				
    		/*while(T[i+(1+P[i])]==T[i-(1+P[i])])
    			P[i]++;*/
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
    	vector<int> dp_mincut(s.size()+1);
    	for(int i=0;i<s.size()+1;i++)
    		dp_mincut[i]=s.size()-1;
    	//final result is dp_mincut[s.size()],at most s.size()-1
    
    	//T132_solve(s, 0,cur_result, P, dp_mincut);
    	int middle,ending;
    	dp_mincut[0]=-1;
    	dp_mincut[1]=0;
    	for(int i=2;i<=s.size();i++){
    		ending=i-1;
    		for(int start=0;start<=ending;start++){
    			middle=start+ending;	
    			if(P[middle]>=2*ending-middle)
    				if(dp_mincut[i]>dp_mincut[start]+1)
    					dp_mincut[i]=dp_mincut[start]+1;
    		}
    	}
    	return dp_mincut[s.size()];
    }
};
