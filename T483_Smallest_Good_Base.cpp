/*For an integer n, we call k>=2 a good base of n, if all digits of (n base k) are 1.

Now given a string representing n, you should return the smallest good base of n in string format. 

Example 1:
Input: "13"
Output: "3"
Explanation: 13 base 3 is 111.   13=1*(3^2)   +1*3+1
Example 2:
Input: "4681"
Output: "8"
Explanation: 4681 base 8 is 11111.
Example 3:
Input: "1000000000000000000"
Output: "999999999999999999"
Explanation: 1000000000000000000 base 999999999999999999 is 11.
Note:
The range of n is [3, 10^18].
The string representing n is always valid and will not have leading zeros.*/


class Solution {
public:
    string smallestGoodBase(string n) {
    	long long num=0;
    	for(long long i=0;i<(n.size());i++)
    		num=10*num+(long long)(n[i]-'0');
    	long long max_length=0;//max possible length of 11111...111
    	long long bound=1;
    	for(int i=1;i<63;i++){
    		bound*=2;//base 2 has max length
    		if(bound>=num){
    			max_length=i;
    			break;
    		}
    	}
    	//long long base=LLONG_MAX;
    
    	long long min_possible_base=2;
    	//one_length:  length of 1
    	for(long long one_length=max_length;one_length>2;one_length--){
    		long long temp_base=have_good_base(num,one_length,min_possible_base);
    		if(temp_base>0){
    			
    			return to_string(temp_base);
    		}
    
    	}
    	return to_string(num-1);
    }
    
    
    long long have_good_base(long long num, long long one_length,long long& min_possible_base){
    	long long left=min_possible_base;
    	long long right=num;
    	
    	while(left<=right){
    		long long middle=left+(right-left)/2;
    		long long count_digits=0;
    		bool digits_all_one=true;
    		//check if num base middle is larger than 11111111 if they have same length, 1234>1111,  1020<1111
    		//because we scan from right digit to left digit in while(num!=0), also left digit is more important in comparison, 
    		//so results on left will cover right result
    		bool numBaseM_larger;
    		long long digit;
    		long long temp_num=num;
    		while(temp_num!=0){
    			digit=temp_num%middle;
    			if(digit!=1){
    				digits_all_one=false;
    				if(digit>1)
    					numBaseM_larger=true;
    				else numBaseM_larger=false;
    			}
    			temp_num=temp_num/middle;
    			count_digits++;
    		}
    		if(count_digits>one_length){//middle is smaller than expected base
    			left=middle+1;
    			min_possible_base=middle+1;
    		}else if(count_digits<one_length){
    			right=middle-1;
    		}else{
    			if(digits_all_one){
    				return middle;
    			}else{
    				if(numBaseM_larger){//middle is smaller than expected base
    					left=middle+1;
    					min_possible_base=middle+1;
    				}else{//middle is larger than expected base
    					right=middle-1;
    				}
    			}
    		}
    
    	}
    
    	return -1;
    
    
    }
};
