/*Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital, 
LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited 
resources, it can only finish at most k distinct projects before the IPO. Help LeetCode design the best way 
to maximize its total capital after finishing at most k distinct projects.

You are given several projects. For each project i, it has a pure profit Pi and a minimum capital of Ci is 
needed to start the corresponding project. Initially, you have W capital. When you finish a project, you 
will obtain its pure profit and the profit will be added to your total capital.

To sum up, pick a list of at most k distinct projects from given projects to maximize your final capital, 
and output your final maximized capital.

Example 1:
Input: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].

Output: 4

Explanation: Since your initial capital is 0, you can only start the project indexed 0.
             After finishing it you will obtain profit 1 and your capital becomes 1.
             With capital 1, you can either start the project indexed 1 or the project indexed 2.
             Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
             Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
Note:
You may assume all numbers in the input are non-negative integers.
The length of Profits array and Capital array will not exceed 50,000.
The answer is guaranteed to fit in a 32-bit signed integer.*/

class Solution {
public:
    struct myclass502{
    	bool operator()(pair<int,int> a, pair<int,int> b){
    		return a.first<b.first;
    	}
    }myobject502;
    
    
    struct mycompare_large_inc_first502{
    //put larger profit first in the heap
    	bool operator()(pair<int,int> a, pair<int,int> b){
    		return (a.second)>(b.second);
    	}
    };
    
    //my idea: in all available projects, choose project that makes money most profit
    //the difficulty is: to have less time complexity, should we sort based on capital or profit?
    //my thinking: first sort by capital, create heap, only insert ones that < current total capital, choose top of heap, then 
    //current capital increased, add more projects into heap
    
    //use pair to combine vector<int>& Profits   and  vector<int>& Capital
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
            vector<pair<int,int>> cap_pro;//capital, profit
    		for(int i=0;i<Profits.size();i++){
    			cap_pro.push_back(make_pair(Capital[i],Profits[i]));
    		}
    
    		sort(cap_pro.begin(),cap_pro.end(),myobject502);
    
    		multiset<pair<int,int>,mycompare_large_inc_first502> heap;
    		int maxCapital=W;
    		int cap_pro_ind=0;
    		for(int count=0;count<k;count++){
    			while(cap_pro_ind<cap_pro.size()&&cap_pro[cap_pro_ind].first<=maxCapital){
    				heap.insert(cap_pro[cap_pro_ind]);
    				cap_pro_ind++;
    			}
    			if((*heap.begin()).second>0){//profit>capital
    				maxCapital+=(*heap.begin()).second;
    				heap.erase(heap.begin());
    			}else //otherwise the max capital can not grow anymore
    				break;
    
    		}
    		return maxCapital;
    
    }
};
