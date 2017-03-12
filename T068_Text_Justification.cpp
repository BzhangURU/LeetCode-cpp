/* Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) 
justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' 
when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide 
evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:

[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Note: Each word is guaranteed not to exceed L in length. */
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
		if(words.size()==0)
			return result;

		int start_ind=0;
		int end_ind=0;

		int length;
		while(start_ind<words.size()){
			length=0;
			end_ind=start_ind;
			string str;
			bool last_line=false;
			while(length+words[end_ind].size()<=maxWidth){
				length+=words[end_ind].size()+1;//not include end_ind
				end_ind++;
				if(end_ind==words.size()){
					last_line=true;
					break;
				}
			}
			if(!last_line){
				//if there is only one word in the line
				if(end_ind==start_ind+1){
					str.append(words[start_ind]);
					string suffix(maxWidth-words[start_ind].size(),' ');
					str.append(suffix);
					result.push_back(str);
				}else{
					int num_spaces=end_ind-start_ind-1+maxWidth-(length-1);
					//how many spaces directly before last word
					int last_spaces=num_spaces/(end_ind-start_ind-1);
					int first_num=num_spaces%(end_ind-start_ind-1);
					int i=start_ind;
					//before first_num, there are last_spaces+1 spaces between words
					for(;i<start_ind+first_num;i++){
						str.append(words[i]);
						string sp_1(last_spaces+1,' ');
						str.append(sp_1);
					}
					for(;i<end_ind-1;i++){
						str.append(words[i]);
						string sp_0(last_spaces,' ');
						str.append(sp_0);
					}
					str.append(words[end_ind-1]);
					result.push_back(str);
				}
			}//if it is last line
			else{
				for(int i=start_ind;i<end_ind-1;i++){
					str.append(words[i]);
					str.append(" ");
				}
				str.append(words[end_ind-1]);
				string suffix(maxWidth-(length-1),' ');
				str.append(suffix);
				result.push_back(str);
			}

			start_ind=end_ind;

		}

		return result;
    }
};
