/*Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.

Each rectangle is represented as a bottom-left point and a top-right point. For example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).


Example 1:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [3,2,4,4],
  [1,3,2,4],
  [2,3,3,4]
]

Return true. All 5 rectangles together form an exact cover of a rectangular region.

Example 2:

rectangles = [
  [1,1,2,3],
  [1,3,2,4],
  [3,1,4,2],
  [3,2,4,4]
]

Return false. Because there is a gap between the two rectangular regions.

Example 3:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [3,2,4,4]
]

Return false. Because there is a gap in the top center.

Example 4:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [2,2,4,4]
]
y=9
y=8



y=0, x=0				x=1			x=2

x1,y1,x2,y2

Return false. Because two of the rectangles overlap with each other.*/


class Solution {
public:
    struct myclass{
    	bool operator()(vector<int> a,vector<int> b){
    		if(a[1]!=b[1])
    			return a[1]<b[1];
    		else return a[0]<b[0];
    	}
    }myobject;
    bool isRectangleCover(vector<vector<int>>& rectangles) {
    	if(rectangles.size()==0)
    		return false;
    	//sort the whole rectangles, start from the bottom(y=0), in all y=0, sort by x, (x=0  y=0,    x=1 y=0,  x=2 y=0)
        sort(rectangles.begin(),rectangles.end(),myobject);
    	
    	int bottom_y=rectangles[0][1];
    	int left_x=rectangles[0][0];//left bound
    	int right_x;
    
    	//It is like many buildings connect to each other, then add height to each building,check if finally it is a rectangle
    
    	multiset<int> x_heap;
    	x_heap.insert(rectangles[0][0]);//each x is the x coordinates of each matrix's bottom left
    
    	unordered_map<int,int> x_to_heighty;//map x to height, min height start from bottome_y
    	x_to_heighty[rectangles[0][0]]=rectangles[0][3];
    
    	unordered_map<int,int> x_to_nextx;//map x to next x where height change, normally map rectangle[i][0] to rectangle[i][2] if no merge
    	x_to_nextx[rectangles[0][0]]=rectangles[0][2];
    	if(rectangles[0][0]>=rectangles[0][2]||rectangles[0][1]>=rectangles[0][3])
    			return false;
    	int i=1;
    	int previous_x=rectangles[0][0];
    	while(i<rectangles.size()&&rectangles[i][1]==bottom_y){
    		if(rectangles[i][0]>=rectangles[i][2]||rectangles[i][1]>=rectangles[i][3])
    			return false;
    		//if new building's x is not same as previous building's tail, then wrong
    		if(rectangles[i][0]!=rectangles[i-1][2])
    			return false;
    
    		//if building has same height with previous, merge
    		if(rectangles[i][3]==rectangles[i-1][3]){
    			x_to_nextx[previous_x]=rectangles[i][2];
    		}else{
    			x_heap.insert(rectangles[i][0]);
    			x_to_heighty[rectangles[i][0]]=rectangles[i][3];
    			x_to_nextx[rectangles[i][0]]=rectangles[i][2];
    			previous_x=rectangles[i][0];
    		}
    		i++;
    	}
    	
    	//now has scanned all the matrix that touch the bottom line, all other buildings will on the top of them
    	right_x=rectangles[i-1][2];//right bound
    
    	
    	for(;i<rectangles.size();i++){
    		if(rectangles[i][0]>=rectangles[i][2]||rectangles[i][1]>=rectangles[i][3]||rectangles[i][2]>right_x)
    			return false;
    		
    		//make sure new building's bottom left is on an old building's top left
    		if(x_heap.find(rectangles[i][0])==x_heap.end()||x_to_heighty[rectangles[i][0]]!=rectangles[i][1])
    			return false;
    
    		multiset<int>::iterator iter_find=x_heap.find(rectangles[i][0]);
    
    		int test_current_x=*iter_find;
    		int test_0=rectangles[i][0];
    		int test_1=rectangles[i][1];
    		int test_2=rectangles[i][2];
    		int test_3=rectangles[i][3];
    		//if new building's bottom right is on an old building's top right
    		if(rectangles[i][2]==x_to_nextx[*iter_find]){
    			x_to_heighty[rectangles[i][0]]=rectangles[i][3];
    			
    			
    
    			//check if need to merge left side or right side
    
    			//if not first x and has same height with left neighbor
    			if(iter_find!=x_heap.begin()){
    				iter_find--;
    				multiset<int>::iterator iter_find_previous_in_heap=iter_find;
    				iter_find++;
    				if(x_to_heighty[*(iter_find_previous_in_heap)]==rectangles[i][3]){
    					//if not the last x in the heap and has same height with right neighbor
    					if(x_to_nextx.find(rectangles[i][2])!=x_to_nextx.end()&&rectangles[i][3]==x_to_heighty[rectangles[i][2]]){
    						//merge   three intervals(before, current, after) together
    						x_to_nextx[*iter_find_previous_in_heap]=x_to_nextx[rectangles[i][2]];
    						x_to_heighty.erase(rectangles[i][2]);
    						x_to_heighty.erase(rectangles[i][0]);
    						x_to_nextx.erase(rectangles[i][2]);
    						x_to_nextx.erase(rectangles[i][0]);
    						x_heap.erase(rectangles[i][0]);
    						x_heap.erase(rectangles[i][2]);
    					}else{//merge   before and current
    						x_to_nextx[*iter_find_previous_in_heap]=rectangles[i][2];
    						x_to_heighty.erase(rectangles[i][0]);
    						x_to_nextx.erase(rectangles[i][0]);
    						x_heap.erase(rectangles[i][0]);
    					}
    
    					////if not the last x in the heap and has same height with right neighbor
    				}else if(x_to_nextx.find(rectangles[i][2])!=x_to_nextx.end()&&rectangles[i][3]==x_to_heighty[rectangles[i][2]]){
    					//merge current and after
    					x_to_nextx[rectangles[i][0]]=x_to_nextx[rectangles[i][2]];
    					x_to_heighty.erase(rectangles[i][2]);
    					x_to_nextx.erase(rectangles[i][2]);
    					x_heap.erase(rectangles[i][2]);
    				}
    
    
    			}else if(x_to_nextx.find(rectangles[i][2])!=x_to_nextx.end()&&rectangles[i][3]==x_to_heighty[rectangles[i][2]]){
    				//merge current and after
    				x_to_nextx[rectangles[i][0]]=x_to_nextx[rectangles[i][2]];
    				x_to_heighty.erase(rectangles[i][2]);
    				x_to_nextx.erase(rectangles[i][2]);
    				x_heap.erase(rectangles[i][2]);
    
    			}
    		//if new building's bottom right before old building's top right,need to split it
    		}else if(rectangles[i][2]<x_to_nextx[*iter_find]){
    			//add new one
    			x_to_nextx[rectangles[i][2]]=x_to_nextx[*iter_find];
    			x_to_heighty[rectangles[i][2]]=rectangles[i][1];
    			x_heap.insert(rectangles[i][2]);
    
    
    
    			x_to_heighty[rectangles[i][0]]=rectangles[i][3];
    			x_to_nextx[rectangles[i][0]]=rectangles[i][2];
    
    			
    
    			//check if need to merge with previous
    			if(iter_find!=x_heap.begin()){
    				iter_find--;
    				multiset<int>::iterator iter_find_previous_in_heap=iter_find;
    				iter_find++;
    				if(x_to_heighty[*(iter_find_previous_in_heap)]==rectangles[i][3]){
    					x_to_nextx[*iter_find_previous_in_heap]=rectangles[i][2];
    					x_to_heighty.erase(rectangles[i][0]);
    					x_to_nextx.erase(rectangles[i][0]);
    					x_heap.erase(rectangles[i][0]);
    				}
    			}
    			
    			
    
    
    		}else 
    			return false;//if new building's bottom right after old building's top right, has cross section
    	}
    	//finally every maxtrix should merge
    	if(x_heap.size()!=1)
    		return false;
    	else 
    		return true;
    	
    
    
    }
};
