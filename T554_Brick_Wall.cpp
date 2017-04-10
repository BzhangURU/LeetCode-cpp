/*There is a brick wall in front of you. The wall is rectangular and has several rows of bricks. The bricks have the same 
height but different width. You want to draw a vertical line from the top to the bottom and cross the least bricks.

The brick wall is represented by a list of rows. Each row is a list of integers representing the width of each brick in this 
row from left to right.

If your line go through the edge of a brick, then the brick is not considered as crossed. You need to find out how to draw 
the line to cross the least bricks and return the number of crossed bricks.

You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.

Example:
Input: 
[[1,2,2,1],
 [3,1,2],
 [1,3,2],
 [2,4],
 [3,1,2],
 [1,3,1,1]]
Output: 2
Explanation: 

Note:
The width sum of bricks in different rows are the same and won't exceed INT_MAX.
The number of bricks in each row is in range [1,10,000]. The height of wall is in range [1,10,000]. Total number of 
bricks of the wall won't exceed 20,000.*/



class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        int height=wall.size();
		if(height==0)
			return 0;
		int width=0;
		for(int i=0;i<wall[0].size();i++)
			width+=wall[0][i];
		set<int> heap;
		map<int,int> map_pos2num;

		for(int row=0;row<wall.size();row++){
			int pos=0;
			for(int ind=0;ind<wall[row].size()-1;ind++){
				pos+=wall[row][ind];
				auto iter=map_pos2num.find(pos);
				if(iter==map_pos2num.end()){
					map_pos2num[pos]=1;
					heap.insert(pos);
				}else
					map_pos2num[pos]++;
			}
		}
		int result=height;
		for(auto iter=heap.begin();iter!=heap.end();iter++)
			if(result>height-map_pos2num[*iter])
				result=height-map_pos2num[*iter];
		return result;
    }
};
