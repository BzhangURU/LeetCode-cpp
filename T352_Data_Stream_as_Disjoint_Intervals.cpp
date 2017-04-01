/*Given a data stream input of non-negative integers a1, a2, ..., an, ..., summarize the numbers seen so far as a list of disjoint intervals.

For example, suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the summary will be:

[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]
Follow up:
What if there are lots of merges and the number of disjoint intervals are small compared to the data stream's size?*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class SummaryRanges {
public:
	vector<Interval> intervals;


    /** Initialize your data structure here. */
    SummaryRanges() {
        
    }
    
    void addNum(int val) {

        if(intervals.size()==0){
			Interval new_in(val,val);
			intervals.push_back(new_in);
			return;
		}
		
		
		//int ind_involved=0;
		//make sure left is the earliest involved index, left-1 would never change in this operation
		int left=0,right=intervals.size()-1,middle;
		while(left<right){
			middle=left+((right-left)/2);
			if(intervals[middle].end<val-1)
				left=middle+1;
			else if(intervals[middle].start>val+1)
				right=middle-1;
			else if(intervals[middle].end==val-1){
				left=middle;
				right=min(left+1,(int)intervals.size()-1);
				break;
			}else if(intervals[middle].start==val+1){
				if(middle>0){
					if(intervals[middle-1].end==val-1){
						left=middle-1;
						right=middle;
						break;
					}else{
						left=middle;
						break;
					}
				}else break;
			}else return;//val is in an interval,no need to change
		}
		right=min(left+1,(int)intervals.size()-1);

		if(intervals[left].start>val+1){
			Interval new_in(val,val);
			intervals.insert(intervals.begin()+left,new_in);
		}else if(intervals[left].start==val+1)
			intervals[left].start=val;
		else if(intervals[left].end>=val)
			;//do nothing
		else if(intervals[left].end==val-1){
			if(intervals[right].start==val+1){
				intervals[left].end=intervals[right].end;
				intervals.erase(intervals.begin()+right);
			}else
				intervals[left].end=val;
		}else {
			Interval new_in(val,val);
			intervals.insert(intervals.begin()+left+1,new_in);
		}

    }
    
    vector<Interval> getIntervals() {
        return intervals;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */
