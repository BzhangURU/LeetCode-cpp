/*Given a positive 32-bit integer n, you need to find the smallest 32-bit integer which has exactly 
the same digits existing in the integer n and is greater in value than n. If no such positive 32-bit integer exists, you need to return -1.

Example 1:
Input: 12
Output: 21
Example 2:
Input: 21
Output: -1*/

class Solution {
public:
    int nextGreaterElement(int n) {
        multiset<int> digits;//123426
		int d;
		long long num=(long long)n;
		while(num!=0){
			d=(int)num%10;//digit
			if(digits.empty()||d>=*digits.rbegin())
				digits.insert(d);
			else{
				set<int>::iterator insert_pos=digits.upper_bound(d);
				int change_d=*insert_pos;
				digits.erase(digits.find(change_d));
				digits.insert(d);
				num=num/10;
				num=10*num+(long long)change_d;
				//recover n
				for(auto iter=digits.begin();iter!=digits.end();iter++){
					num=10*num+(long long)*iter;
				}
				if(num>(long long)INT_MAX)
					return -1;
				else return num;
			}
			num=num/10;
		}
		return -1;
    }
};
