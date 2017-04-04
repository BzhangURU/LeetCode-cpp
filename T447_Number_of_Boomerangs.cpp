/*Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) 
such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Find the number of boomerangs. You may assume that n will be at most 500 and 
coordinates of points are all in the range [-10000, 10000] (inclusive).

Example:
Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]*/

class Solution {
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        if(points.size()<=1)
    		return 0;
    	int result=0;
    	for(int i=0;i<points.size();i++){
    	    unordered_map<int,int> map_dis_num;
    		for(int j=0;j<points.size();j++){
    			if(i==j)
    				continue;
    			int distance=(points[i].first-points[j].first)*(points[i].first-points[j].first)+(points[i].second-points[j].second)*(points[i].second-points[j].second);
    			if(map_dis_num.find(distance)==map_dis_num.end())
    				map_dis_num[distance]=1;
    			else map_dis_num[distance]++;
    		}
    		unordered_map<int,int>::iterator iter;
    		for(iter=map_dis_num.begin();iter!=map_dis_num.end();iter++)
    		    result+=(iter->second)*(iter->second-1);
    	}
    	return result;
    }
};
