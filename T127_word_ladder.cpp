class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if(beginWord.size()!=endWord.size()||beginWord.size()==0)
			return 0;
		if(beginWord==endWord)
			return 1;


		//put wordList in wordset
		unordered_set<string> myset;
		for(int i=0;i<wordList.size();i++){
			myset.insert(wordList[i]);
		}
		if(myset.find(endWord)==myset.end())
			myset.insert(endWord);
		if(myset.find(beginWord)==myset.end())
			myset.insert(beginWord);

		int step=2;
		unordered_set<string> tempset1;
		tempset1.insert(beginWord);
		myset.erase(beginWord);

		while(!tempset1.empty()){
			unordered_set<string> tempset2;
			unordered_set<string>::iterator iter;
			for (iter = tempset1.begin(); iter != tempset1.end(); iter++)
			{
				string cur_str= *iter;
				for(int i=0;i<cur_str.size();i++){
					char origin_char=cur_str[i];
					for(char c='a';c<='z';c++){
						if(c!=origin_char){
							cur_str[i]=c;
							if(myset.find(cur_str)!=myset.end()){
								if(cur_str==endWord){
									return step;
								}
								tempset2.insert(cur_str);
								myset.erase(cur_str);
							}

						}
					}
					cur_str[i]=origin_char;
				}

			}
			tempset1=tempset2;
			step++;
		}

		return 0;
    }
};
