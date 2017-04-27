/*Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.

Example 1:
Input: "abab"

Output: True

Explanation: It's the substring "ab" twice.
Example 2:
Input: "aba"

Output: False
Example 3:
Input: "abcabcabcabc"

Output: True

Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)*/
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int size=s.size();

    	for(int i=size/2;i>=1;i--){
    		if(size%i==0){
    			int times=size/i;
    			int k=1;
    			for(;k<times;k++){
    				if(s.substr(0,i)!=s.substr(k*i,i))
    					break;
    			}
    			if(k==times)
    				return true;
    		}
    	}
    
    	return false;
    }
};
