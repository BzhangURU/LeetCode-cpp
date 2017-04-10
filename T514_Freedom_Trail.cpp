/*In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring", 
and use the dial to spell a specific keyword in order to open the door.

Given a string ring, which represents the code engraved on the outer ring and another string key, which represents the keyword 
needs to be spelled. You need to find the minimum number of steps in order to spell all the characters in the keyword.

Initially, the first character of the ring is aligned at 12:00 direction. You need to spell all the characters in the string key one by one 
by rotating the ring clockwise or anticlockwise to make each character of the string key aligned at 12:00 direction and then by 
pressing the center button. 
At the stage of rotating the ring to spell the key character key[i]:
You can rotate the ring clockwise or anticlockwise one place, which counts as 1 step. The final purpose of the rotation is to align 
one of the string ring's characters at the 12:00 direction, where this character must equal to the character key[i].
If the character key[i] has been aligned at the 12:00 direction, you need to press the center button to spell, which also counts as 
1 step. After the pressing, you could begin to spell the next character in the key (next stage), otherwise, you've finished all the spelling.
Example:


Input: ring = "godding", key = "gd"
Output: 4
Explanation:
 For the first key character 'g', since it is already in place, we just need 1 step to spell this character. 
 For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
 Also, we need 1 more step for spelling.
 So the final output is 4.
Note:
Length of both ring and key will be in range 1 to 100.
There are only lowercase letters in both strings and might be some duplcate characters in both strings.
It's guaranteed that string key could always be spelled by rotating the string ring.*/


//my thinking: 
//does greedy(always find nearest) work? not always,  maybe go to the reversed direction
//This topic reminds me of Viterbi decoding!!!


class Solution {
public:
    int findRotateSteps(string ring, string key) {
        unordered_map<char,vector<int>> map_char2loc;
    	for(int i=0;i<ring.size();i++){
    		if(map_char2loc.find(ring[i])==map_char2loc.end()){
    			vector<int> new_char;
    			new_char.push_back(i);
    			map_char2loc[ring[i]]=new_char;
    		}else map_char2loc[ring[i]].push_back(i);
    	}
    
    	//Viterbi decoding
    	vector<int> current_steps;
    	vector<int> current_locations;
    	current_steps.push_back(0);
    	current_locations.push_back(0);
    	for(int i=0;i<key.size();i++){
    		
    
    		vector<int> updated_steps(map_char2loc[key[i]].size(),INT_MAX);
    		vector<int> new_locations(map_char2loc[key[i]]);
    		for(int ind_old=0;ind_old<current_locations.size();ind_old++){
    			for(int ind_new=0;ind_new<map_char2loc[key[i]].size();ind_new++){
    				int increased_steps;
    				if(current_locations[ind_old]>new_locations[ind_new]){
    					increased_steps=min(current_locations[ind_old]-new_locations[ind_new],new_locations[ind_new]+(int)ring.size()-current_locations[ind_old]);
    				}else{
    					increased_steps=min(new_locations[ind_new]-current_locations[ind_old],(int)ring.size()+current_locations[ind_old]-new_locations[ind_new]);
    				}
    				increased_steps++;
    				if(current_steps[ind_old]+increased_steps<updated_steps[ind_new])
    					updated_steps[ind_new]=current_steps[ind_old]+increased_steps;
    			}
    		}
    		current_steps=updated_steps;
    		current_locations=new_locations;
    
    	}
    	int result=INT_MAX;
    
    	for(int ind=0;ind<current_steps.size();ind++){
    		if(result>current_steps[ind])
    			result=current_steps[ind];
    	}
    	return result;
    }
};
