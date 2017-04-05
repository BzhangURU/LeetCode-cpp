/*A password is considered strong if below conditions are all met:

It has at least 6 characters and at most 20 characters.
It must contain at least one lowercase letter, at least one uppercase letter, and at least one digit.
It must NOT contain three repeating characters in a row ("...aaa..." is weak, but "...aa...a..." is strong, assuming other conditions are met).
Write a function strongPasswordChecker(s), that takes a string s as input, and return the MINIMUM change required to make s a strong password. If s is already strong, return 0.

Insertion, deletion or replace of any one character are all considered as one change.*/


class Solution {
public:
    int steps_needed(string s,char pre_pre, char pre, int min_n, int max_n, bool lack_lowercase,bool lack_uppercase,bool lack_digit){
    	if(min_n<0)
    		min_n=0;
    	for(int i=0;i<s.size();i++){
    		if(pre_pre==pre&&pre==s[i]){
    			int step;
    
    
    			if(s.size()<min_n){
    				//when length is <min, only try add
    				if(lack_lowercase){
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i],'a',min_n-(i+2),max_n-(i+2),false,lack_uppercase,lack_digit);
    				}else if(lack_uppercase)
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i],'A',min_n-(i+2),max_n-(i+2),false,false,lack_digit);
    				else if(lack_digit)
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i],'0',min_n-(i+2),max_n-(i+2),false,false,false);
    				else{
    					if(s.size()==(i+1)||s[i+1]=='?')
    						return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i],'@',min_n-(i+2),max_n-(i+2),false,false,false);
    					else return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i],'?',min_n-(i+2),max_n-(i+2),false,false,false);
    				}
    			}else if(s.size()>max_n){
    				//when length is >suffix_target_max_num, only try delete, delete s[i]
    				step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre_pre,pre,min_n-i,max_n-i,lack_lowercase,lack_uppercase,lack_digit);
    				int temp_step;
    				if(lack_lowercase){
    					temp_step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre,'a',min_n-(i+1),max_n-(i+1),false,lack_uppercase,lack_digit);
    				}else if(lack_uppercase)
    					temp_step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre,'A',min_n-(i+1),max_n-(i+1),false,false,lack_digit);
    				else if(lack_digit)
    					temp_step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre,'0',min_n-(i+1),max_n-(i+1),false,false,false);
    				else{
    					if(s.size()==(i+1)||s[i+1]=='?')
    						temp_step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre,'@',min_n-(i+1),max_n-(i+1),false,false,false);
    					else temp_step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre,'?',min_n-(i+1),max_n-(i+1),false,false,false);
    				}
    				step=min(step,temp_step);
    				return step;
    			}else{
    
    
    				//when length is normal, only try replace
    				if(lack_lowercase){
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre,'a',min_n-(i+1),max_n-(i+1),false,lack_uppercase,lack_digit);
    				}else if(lack_uppercase)
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre,'A',min_n-(i+1),max_n-(i+1),false,false,lack_digit);
    				else if(lack_digit)
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre,'0',min_n-(i+1),max_n-(i+1),false,false,false);
    				else{
    					if(s.size()==(i+1)||s[i+1]=='?')
    						return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre,'@',min_n-(i+1),max_n-(i+1),false,false,false);
    					else return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre,'?',min_n-(i+1),max_n-(i+1),false,false,false);
    				}
    				
    
    			}
    
    		}
    
    
    		pre_pre=pre;
    		pre=s[i];
    	}
    
    
    	/////////////////////////////////////////////////////////////////////////////////////////
    	//if program reaches here, it means there is no 3 duplicates gather together, then it is easy to process
    	int count_lack=0;
    	if(lack_lowercase)
    		count_lack++;
    	if(lack_uppercase)
    		count_lack++;
    	if(lack_digit)
    		count_lack++;
    	if(s.size()<min_n)
    		return max(count_lack,min_n-(int)s.size());
    	else if((int)s.size()>max_n)
    		return count_lack+(int)s.size()-max_n;
    	else return count_lack;
    
    
    
    
    }
    
    
    
    //my solution: (maybe the string has no lowercase, uppercase and digit!!!)
    //if s.size()<=6, not allowed to deleter, if s.size()>=20, not allowed to add
    int strongPasswordChecker(string s) {
    	if(s.size()<=3)
    		return 6-s.size();
    	bool lack_lowercase=true;
    	bool lack_uppercase=true;
    	bool lack_digit=true;
    	//check diversity
    	for(int i=0;i<s.size();i++){
    		if(s[i]>='a'&&s[i]<='z')
    			lack_lowercase=false;
    		else if(s[i]>='A'&&s[i]<='Z')
    			lack_uppercase=false;
    		else if(s[i]>='0'&&s[i]<='9')
    			lack_digit=false;
    	}
    	char pre_pre=s[0];
    	char pre=s[1];
    	for(int i=2;i<s.size();i++){
    		if(pre_pre==pre&&pre==s[i]){
    			int step;
    
    
    			if(s.size()<6){
    				//when length is <6, only try add
    				if(lack_lowercase){
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i],'a',6-(i+2),20-(i+2),false,lack_uppercase,lack_digit);
    				}else if(lack_uppercase)
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i],'A',6-(i+2),20-(i+2),false,false,lack_digit);
    				else if(lack_digit)
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i],'0',6-(i+2),20-(i+2),false,false,false);
    				else{
    					if(s.size()==(i+1)||s[i+1]=='?')
    						return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i],'@',6-(i+2),20-(i+2),false,false,false);
    					else return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i],'?',6-(i+2),20-(i+2),false,false,false);
    				}
    			}else if(s.size()>20){
    				//when length is >20, try delete and replace, delete s[i], 
    				//Also try replace!!!!!!!!!!!!! think about aaaabbaaabbaaa123456A, takes 3 steps, not 4 steps aaCabbaCabbaCa123456A
    				step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),pre_pre,pre,6-i,20-i,lack_lowercase,lack_uppercase,lack_digit);
    				int temp_step;
    				if(lack_lowercase){
    					temp_step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i-1],'a',6-(i+1),20-(i+1),false,lack_uppercase,lack_digit);
    				}else if(lack_uppercase)
    					temp_step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i-1],'A',6-(i+1),20-(i+1),false,false,lack_digit);
    				else if(lack_digit)
    					temp_step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i-1],'0',6-(i+1),20-(i+1),false,false,false);
    				else{
    					if(s.size()==(i+1)||s[i+1]=='?')
    						temp_step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i-1],'@',6-(i+1),20-(i+1),false,false,false);
    					else temp_step=1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i-1],'?',6-(i+1),20-(i+1),false,false,false);
    				}
    
    
    				step=min(step,temp_step);
    				return step;
    			}else{
    
    
    				//when length is normal, only try replace
    				if(lack_lowercase){
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i-1],'a',6-(i+1),20-(i+1),false,lack_uppercase,lack_digit);
    				}else if(lack_uppercase)
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i-1],'A',6-(i+1),20-(i+1),false,false,lack_digit);
    				else if(lack_digit)
    					return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i-1],'0',6-(i+1),20-(i+1),false,false,false);
    				else{
    					if(s.size()==(i+1)||s[i+1]=='?')
    						return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i-1],'@',6-(i+1),20-(i+1),false,false,false);
    					else return 1+steps_needed(s.substr(i+1,s.size()-(i+1)),s[i-1],'?',6-(i+1),20-(i+1),false,false,false);
    				}
    				
    
    			}
    
    		}
    
    
    		pre_pre=pre;
    		pre=s[i];
    	}
    
    
    	/////////////////////////////////////////////////////////////////////////////////////////
    	//if program reaches here, it means there is no 3 duplicates gather together, then it is easy to process
    	int count_lack=0;
    	if(lack_lowercase)
    		count_lack++;
    	if(lack_uppercase)
    		count_lack++;
    	if(lack_digit)
    		count_lack++;
    	if(s.size()<6)
    		return max(count_lack,6-(int)s.size());
    	else if(s.size()>20)
    		return count_lack+(int)s.size()-20;
    	else return count_lack;
    
    	
    }

};
