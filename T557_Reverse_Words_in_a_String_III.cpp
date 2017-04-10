/*Given a string, you need to reverse the order of characters in each word within a sentence while still 
preserving whitespace and initial word order.

Example 1:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
Note: In the string, each word is separated by single space and there will not be any extra space in the string.*/


class Solution {
public:
    string reverseWords(string s) {
        int left=0,right=0;

		//first skip space on the left
		while(left<s.size()&&s[left]==' '){
			left++;
		}
		right=left;
		int temp_left,temp_right;
		while(right<s.size()){
			while(right<s.size()&&s[right]!=' '){
				right++;
			}

			//now find a new word, reverse it
			temp_right=right-1;
			temp_left=left;
			while(temp_left<temp_right){
				char l=s[temp_left];
				s[temp_left++]=s[temp_right];
				s[temp_right--]=l;
			}
			
			//skip space	
			while(right<s.size()&&s[right]==' '){
				right++;
			}
			left=right;


		}
		return s;
    }
};
