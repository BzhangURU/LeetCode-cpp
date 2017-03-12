
/* Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t

To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t

We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a

We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1. */


class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1==s2)
			return true;
		if(s1.size()!=s2.size())
			return false;
		map<char,int> map1;
		map<char,int> map2_front;
		map<char,int> map2_rear;


		for(int i=0;i<s1.size()-1;i++){
			if(map1.find(s1[i])!=map1.end())
				map1[s1[i]]++;
			else map1[s1[i]]=1;

			if(map2_front.find(s2[i])!=map2_front.end())
				map2_front[s2[i]]++;
			else map2_front[s2[i]]=1;

			if(map2_rear.find(s2[s2.size()-1-i])!=map2_rear.end())
				map2_rear[s2[s2.size()-1-i]]++;
			else map2_rear[s2[s2.size()-1-i]]=1;

			if(map1==map2_front)
				if(isScramble(s1.substr(0,i+1), s2.substr(0,i+1))&&isScramble(s1.substr(i+1,s1.size()-1-i), s2.substr(i+1,s1.size()-1-i)))
					return true;
			if(map1==map2_rear)
				if(isScramble(s1.substr(0,i+1), s2.substr(s2.size()-1-i,i+1))&&isScramble(s1.substr(i+1,s1.size()-1-i), s2.substr(0,s2.size()-1-i)))
					return true;

		}
		return false;





    }
};
