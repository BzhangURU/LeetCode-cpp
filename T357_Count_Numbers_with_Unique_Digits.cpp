/*Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10n.

Example:
Given n = 2, return 91. (The answer should be the total numbers in the range of 0 ≤ x < 100, excluding [11,22,33,44,55,66,77,88,99])
*/

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n>10)
		return countNumbersWithUniqueDigits(10);
	if(n==0)
		return 1;
	int current=9;
	int result=10;
	for(int i=1;i<n;i++){
		current=current*(9-(i+1)+2);
		result+=current;
	}
	return result;
    }
};
