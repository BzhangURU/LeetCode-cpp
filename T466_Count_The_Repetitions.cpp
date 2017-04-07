/*Define S = [s,n] as the string S which consists of n connected strings s. For example, ["abc", 3] ="abcabcabc".

On the other hand, we define that string s1 can be obtained from string s2 if we can remove some characters 
from s2 such that it becomes s1. For example, “abc” can be obtained from “abdbec” based on our definition, 
but it can not be obtained from “acbbe”.

You are given two non-empty strings s1 and s2 (each at most 100 characters long) and two integers 0 ≤ n1 ≤ 10^6 
and 1 ≤ n2 ≤ 10^6. Now consider the strings S1 and S2, where S1=[s1,n1] and S2=[s2,n2]. Find the maximum integer 
M such that [S2,M] can be obtained from S1.

Example:

Input:
s1="acb", n1=4
s2="ab", n2=2

Return:
2*/

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
         //if there is some letters in s2 that is not in s1, then return 0
    	vector<bool> s1_contain(256,false);
    	for(int i=0;i<s1.size();i++)
    	s1_contain[(int)s1[i]]=true;
    	for(int i=0;i<s2.size();i++)
    	if(!s1_contain[(int)s2[i]])
    		return 0;
    	//first get minimum positive period, just avoid s1="aabbaacc"  s2="aaaaa"   s2 shrink to "a"
    	int min_period1=1;
    	for(;min_period1<=s1.size();min_period1++){
    		if(s1.size()%min_period1==0){
    			int num1=s1.size()/min_period1;
    			bool is_min_period=true;
    			for(int ind=0;ind<min_period1;ind++){
    				for(int count1=1;count1<num1;count1++){
    					if(s1[count1*min_period1+ind]!=s1[ind]){
    						is_min_period=false;
    						break;
    					}
    				}
    				if(!is_min_period)
    					break;
    			}
    			if(is_min_period){
    				break;
    			}
    		}
    	}
    	if(min_period1<s1.size()){
    		n1*=(s1.size()/min_period1);
    		s1=s1.substr(0,min_period1);
    	}
    	
    
    
    	int min_period2=1;
    	for(;min_period2<=s2.size();min_period2++){
    		if(s2.size()%min_period2==0){
    			int num2=s2.size()/min_period2;
    			bool is_min_period=true;
    			for(int ind=0;ind<min_period2;ind++){
    				for(int count2=1;count2<num2;count2++){
    					if(s2[count2*min_period2+ind]!=s2[ind]){
    						is_min_period=false;
    						break;
    					}
    				}
    				if(!is_min_period)
    					break;
    			}
    			if(is_min_period){
    				break;
    			}
    		}
    	}
    	if(min_period2<s2.size()){
    		n2*=(s2.size()/min_period2);
    		s2=s2.substr(0,min_period2);
    	}
    
    	
    	vector<vector<bool>> s1_s2_visited;//if s1[a] s2[b] was visited before, check map for old two indexes, then we form a loop
    	vector<vector<int>> s1_s2_current_s2_num_scanned;//how many s2 was scanned when s1[a]==s2[b]
    	for(int i=0;i<s1.size();i++){
    		vector<bool> new_v(s2.size(),false);
    		s1_s2_visited.push_back(new_v);
    		vector<int> new_c(s2.size(),0);
    		s1_s2_current_s2_num_scanned.push_back(new_c);
    	}
    	unordered_map<int, pair<int,int>> map;//first int saves 1000*a+b, pair saves <old_global_ind1, old_global_ind2>
    	int global_ind1=0;
    	int global_ind2=0;
    	int num_of_s2=0;
    	bool find_loop=false;
    	int old_global_ind1;
    	int old_global_ind2;
    	int old_num_of_s2=0;
    	while(global_ind1<s1.size()*n1){
    		while(s1[global_ind1%s1.size()]!=s2[global_ind2%s2.size()]){
    			global_ind1++;
    			if(global_ind1>=s1.size()*n1)
    				return num_of_s2/n2;
    		}
    		if((global_ind2%s2.size())==s2.size()-1)
    			num_of_s2++;
    
    		//now s1[global_ind1%s1.size()]==s2[global_ind2%s2.size()]
    		if(s1_s2_visited[global_ind1%s1.size()][global_ind2%s2.size()]){
    			old_global_ind1=map[1000*(global_ind1%s1.size())+(global_ind2%s2.size())].first;
    			old_global_ind2=map[1000*(global_ind1%s1.size())+(global_ind2%s2.size())].second;
    			find_loop=true;
    			old_num_of_s2=s1_s2_current_s2_num_scanned[global_ind1%s1.size()][global_ind2%s2.size()];
    			break;
    		}
    		//now s1[global_ind1%s1.size()]==s2[global_ind2%s2.size()], s1[a]==s2[b]save them
    		s1_s2_visited[global_ind1%s1.size()][global_ind2%s2.size()]=true;
    		map[1000*(global_ind1%s1.size())+(global_ind2%s2.size())]=make_pair(global_ind1,global_ind2);
    		s1_s2_current_s2_num_scanned[global_ind1%s1.size()][global_ind2%s2.size()]=num_of_s2;
    
    
    		
    		global_ind1++;
    		global_ind2++;
    
    	}
    	if(!find_loop)//in this case  global_ind1==s1.size()*n1, already scanned them all
    		return num_of_s2/n2;
    
    	int loop_s2_num=num_of_s2-old_num_of_s2;//how many s2 scanned in one loop
    	int loop_ind1_step=global_ind1-old_global_ind1;//how many steps ind1 goes in one loop
    	int loop_ind2_step=global_ind2-old_global_ind2;//how many steps ind2 goes in one loop
    
    	int remaining_ind1_steps=s1.size()*n1-1-global_ind1;//remaining steps
    	int count_loops_jumped=remaining_ind1_steps/loop_ind1_step;//how many loops jumped from current to end
    	
    	num_of_s2+=loop_s2_num*count_loops_jumped;
    	global_ind1+=loop_ind1_step*count_loops_jumped;
    	global_ind2+=loop_ind2_step*count_loops_jumped;
    
    	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    	//Now there is only less one loop left, continue to reach end
    	global_ind1++;
    	global_ind2++;
    	while(global_ind1<s1.size()*n1){
    		while(s1[global_ind1%s1.size()]!=s2[global_ind2%s2.size()]){
    			global_ind1++;
    			if(global_ind1>=s1.size()*n1)
    				return num_of_s2/n2;
    		}
    		if((global_ind2%s2.size())==s2.size()-1)
    			num_of_s2++;
    		global_ind1++;
    		global_ind2++;
    
    	}
    	return num_of_s2/n2;
    
    }
};
