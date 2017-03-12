/*Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10]. */

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> result;
    	if(intervals.size()==0){
    		result.push_back(newInterval);
    		return result;
    	}
    	if(intervals[0].start>newInterval.end){
    		intervals.insert(intervals.begin(),newInterval);
    		return intervals;
    	}
    	if(intervals[intervals.size()-1].end<newInterval.start){
    		intervals.push_back(newInterval);
    		return intervals;
    	}
    
    	int start=newInterval.start;
    	int end=newInterval.end;
    	int size=intervals.size();
    
    	int new_start=start;
    	int new_end=end;
    	bool time_to_insert=true;
    	for(int i=0;i<size;i++){
    		//if new_interval and interval[i] can merge, one of the start point must be inside the other one
    		if((intervals[i].start<=new_end&&intervals[i].start>=new_start)||(new_start<=intervals[i].end&&new_start>=intervals[i].start)){
    			if(new_start>intervals[i].start)
    				new_start=intervals[i].start;
    			if(new_end<intervals[i].end)
    				new_end=intervals[i].end;
    		}else{
    			if(intervals[i].end<new_start)
    				result.push_back(intervals[i]);
    			//else if(intervals[i].start>new_start){
    			else{
    				if(time_to_insert){
    					Interval new_interval(new_start,new_end);
    					result.push_back(new_interval);
    					time_to_insert=false;
    				}
    				result.push_back(intervals[i]);
    			}
    
    		}
    
    	}
    	if(time_to_insert){
        	Interval new_interval(new_start,new_end);
        	result.push_back(new_interval);
        	time_to_insert=false;
        }
    
        return result;


    }
};
