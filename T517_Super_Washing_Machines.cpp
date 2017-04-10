/*You have n super washing machines on a line. Initially, each washing machine has some dresses or is empty.

For each move, you could choose any m (1 ≤ m ≤ n) washing machines, and pass one dress of each washing 
machine to one of its adjacent washing machines at the same time .

Given an integer array representing the number of dresses in each washing machine from left to right on the 
line, you should find the minimum number of moves to make all the washing machines have the same number 
of dresses. If it is not possible to do it, return -1.

Example1

Input: [1,0,5]

Output: 3

Explanation: 
1st move:    1     0 <-- 5    =>    1     1     4
2nd move:    1 <-- 1 <-- 4    =>    2     1     3    
3rd move:    2     1 <-- 3    =>    2     2     2   
Example2

Input: [0,3,0]

Output: 2

Explanation: 
1st move:    0 <-- 3     0    =>    1     2     0    
2nd move:    1     2 --> 0    =>    1     1     1     
Example3

Input: [0,2,0]

Output: -1

Explanation: 
It's impossible to make all the three washing machines have the same number of dresses. 
Note:
The range of n is [1, 10000].
The range of dresses number in a super washing machine is [0, 1e5].*/


//my solution: assume at each step, you can only move one cloth from one machine to one of its neighbors, calculate
//each step, then get final answer by getting max(check my notes)

class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        //first check availability
    	int length=machines.size();
    	int average=0;
    	for(int i=0;i<machines.size();i++)
    		average+=machines[i];
    	if(average%length!=0)
    		return -1;
    	else average=average/length;
    
    	//based on above assumption, save steps needed for each machine to remove one cloth
    	//for example: if it is 9 0 0, then steps_needed is 6 0 0(The machine that takes in clothes does not count in steps)
    	//scan from left to right, after scanning, machine has average cloth
    	vector<int> steps_needed(length,0);
    	for(int i=0;i<length-1;i++){//if all other machines have average, then the last one must has average
    		if(machines[i]>=average){
    			steps_needed[i]+=machines[i]-average;
    
    			//move additional clothes to right neighbor, from machine[i] to machine[i+1]
    			machines[i+1]+=machines[i]-average;
    			machines[i]=average;
    		}else{
    			steps_needed[i+1]+=average-machines[i];
    			//move additional clothes from machine[i+1] to machine[i]
    			machines[i+1]-=(average-machines[i]);
    			machines[i]=average;
    		}
    	}
    
    	int moves=0;
    	for(int i=0;i<steps_needed.size();i++){
    		moves=max(moves,steps_needed[i]);
    	}
    	return moves;
    }
};
