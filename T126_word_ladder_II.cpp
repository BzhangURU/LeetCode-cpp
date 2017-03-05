class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> result;
		
		vector<vector<string>> final_result;
		unordered_map<string,int> str_step;
		for(int i=0;i<wordList.size();i++){
			str_step[wordList[i]]=-1;
			}
		int step=2;
		vector<string> first;
		first.push_back(beginWord);
		str_step[beginWord]=1;
		result.push_back(first);


		bool find=false;
		while(!find&&!result.empty()){
			vector<vector<string>> result_temp;
			vector<vector<string>>::iterator iter;
			for (iter = result.begin(); iter !=result.end(); iter++)
			{
				vector<string> cur_vector= *iter;
				string last_str=cur_vector.back();
				for(int i=0;i<last_str.size();i++){
					char origin_char=last_str[i];
					for(char c='a';c<='z';c++){
						if(c!=origin_char){
							last_str[i]=c;
							if(str_step.find(last_str)!=str_step.end()&&(str_step[last_str]==-1||str_step[last_str]>=step)){

								vector<string> copy_v(cur_vector);
								copy_v.push_back(last_str);
								str_step[last_str]=step;
								result_temp.push_back(copy_v);
								if(last_str==endWord){
									find=true;
									final_result.push_back(copy_v);
								}
								

							}

						}
					}
					last_str[i]=origin_char;
				}

			}
			result=result_temp;
			step++;
		}


		if(find)
			return final_result;
		else{
			vector<vector<string>> result_null;
			return result_null;
		}
    }
};
