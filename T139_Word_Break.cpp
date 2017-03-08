/* Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented 
into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

UPDATE (2017/1/4):
The wordDict parameter had been changed to a list of strings (instead of a set of strings). Please reload the code definition to 
get the latest changes. */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict;
        int min_length=INT_MAX;
        int max_length=0;
        for(int i=0;i<wordDict.size();i++){
          dict.insert(wordDict[i]);
          if(wordDict[i].size()>max_length)
            max_length=wordDict[i].size();
          if(wordDict[i].size()<min_length)
            min_length=wordDict[i].size();
        }
        //available[i] saves the number of options that can end with letter s[i]
        vector<int> available(s.size());
        for(int i=0;i<available.size();i++){
          available[i]=0;
        }

        for(int i=0;i<s.size();i++){
          for(int start=i-max_length+1;start<=i-min_length+1;start++){
            if(start>0){
              if(available[start-1]>0&&dict.find(s.substr(start,i-start+1))!=dict.end()){
                available[i]++;
                break;//to speed up, since we don't need every solution
              }
            }else if(start==0){
              if(dict.find(s.substr(0,i+1))!=dict.end()){
                available[i]++;
                break;//to speed up, since we don't need every solution
              }
            }

          }
        }
        return available[s.size()-1]>0;
    }
};
