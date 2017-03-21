
/*Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
*/
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
    	if(s.size()<p.size())
    		return result;
        int count_p[256];
    	int count[256];
    	for(int i=0;i<256;i++){
    		count_p[i]=0;
    		count[i]=0;
    	}
    	for(int i=0;i<p.size();i++){
    		count_p[(int)p[i]]++;
    		count[(int)s[i]]++;
    	}
    	bool match=true;
    	for(int j=0;j<256;j++){
    		if(count_p[j]!=count[j]){
    			match=false;
    			break;
    		}
    	}
    	if(match)
    		result.push_back(0);
    	for(int i=p.size();i<s.size();i++){
    		count[(int)s[i]]++;
    		count[(int)s[i-p.size()]]--;
    		match=true;
    		for(int j=0;j<256;j++){
    			if(count_p[j]!=count[j]){
    				match=false;
    				break;
    			}
    		}
    		if(match)
    			result.push_back(i+1-p.size());
    	}
    	return result;
    }
};
