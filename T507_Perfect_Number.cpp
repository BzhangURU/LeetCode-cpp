/*We define the Perfect Number is a positive integer that is equal to the sum of all its positive divisors except itself.

Now, given an integer n, write a function that returns true when it is a perfect number and false when it is not.
Example:
Input: 28
Output: True
Explanation: 28 = 1 + 2 + 4 + 7 + 14
Note: The input number n will not exceed 100,000,000. (1e8)*/
class Solution {
public:
    bool checkPerfectNumber(int num) {
        if(num<=0)
    		return false;
    	if(num==1)
    		return false;
    	int sum=1;
    
    	int squareRoot=(int)sqrt((double)num);
    	int divisor2;
    	for(int i=2;i<=squareRoot;i++){
    		if(num%i==0){
    			divisor2=num/i;
    			sum+=i;
    			if(divisor2!=i)
    				sum+=divisor2;
    		}
    	}
    	return sum==num;
    }
};
