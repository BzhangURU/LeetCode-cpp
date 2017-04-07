/*Given a list of words (without duplicates), please write a program that returns all concatenated words in the given list of words.

A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.
 
Example:
Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
 "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
Note:
The number of elements of the given array will not exceed 10,000
The length sum of elements in the given array will not exceed 600,000.
All the input string will only include lower case letters.
The returned elements order does not matter.*/

class Solution {
public:
    struct myclass{
    	bool operator()(string word1,string word2){
    		return word1.size()<word2.size();
    	}
    }myobject;
    
    bool isConcatenated(string word,unordered_set<string>& myset,int min_length,int max_length){
    
    	if(word.size()==0)
    		return false;
    	vector<bool> dp(word.size(),false);//if dp[i]==true, then (word[0].......word[i])  is concatenated word
    	for(int i=0;i<word.size();i++){
    		for(int start=max(0,i-max_length+1);start<=i-min_length+1;start++){
    			if(start>0){
    				if(!dp[start-1])
    					continue;
    				if(myset.find(word.substr(start,i-start+1))!=myset.end()){
    					dp[i]=true;
    					break;;
    				}
    			}else if(start==0){
    				if(myset.find(word.substr(start,i-start+1))!=myset.end()){
    					dp[i]=true;
    					break;
    				}
    			}
    		}
    
    	}
    	return dp[word.size()-1];
    }
    
    
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
            std::sort(words.begin(),words.end(),myobject);
    		vector<string> result;
    		unordered_set<string> myset;
    		int min_length=INT_MAX;
    		int max_length=0;
    		for(int i=0;i<words.size();i++){
    			if(words.size()==0)
    				continue;
    			if(min_length>words[i].size())
    				min_length=words[i].size();
    			if(max_length<words[i].size())
    				max_length=words[i].size();
    			//cout<<words[i]<<"   ";
    			if(isConcatenated(words[i],myset,min_length,max_length))
    				result.push_back(words[i]);
    			myset.insert(words[i]);
    		}
    		return result;
    
    }
};
