/* You are given an array x of n positive numbers. You start at point (0,0) and moves x[0] metres to the north, 
then x[1] metres to the west, x[2] metres to the south, x[3] metres to the east and so on. In other words, after 
each move your direction changes counter-clockwise.

Write a one-pass algorithm with O(1) extra space to determine, if your path crosses itself, or not.

Example 1:

Given x = 
[2, 1, 1, 2]
,
┌───┐
│   │
└───┼──>
    │

Return true (self crossing)

Example 2:

Given x = 
[1, 2, 3, 4]
,
┌──────┐
│      │
│
│
└────────────>

Return false (not self crossing)

Example 3:

Given x = 
[1, 1, 1, 1]
,
┌───┐
│   │
└───┼>

Return true (self crossing)
*/

class Solution {
public:
    bool isSelfCrossing(vector<int>& x) {
        if(x.size()<=3)
			return false;
		//if must_inside_activated=true, all future lines must inside a shrinking rectangle to avoid cross, must_outside is no used then
		bool must_inside_activated=false;
		int inside_left,inside_right,inside_up,inside_down;


		//if must_outside_activated=true, all future lines must outside a expanding rectangle to avoid cross
		bool must_outside_activated=false;
		int outside_left,outside_right,outside_up,outside_down;

		//in initialization, either inside or outside is activated
		//once inside is activated, the outside would never be used
		
		int up=x[0],left=-x[1],right=0;

		//process x[2],x[3]////////////////////////////////////////////////
		//(x0,y0) is coordinates before x[i], (x1,y1) is corrdinates after x[i]
		int y0=x[0]-x[2],y1=y0;
		int x0=left,x1=left+x[3];
		//check x[2]
		if(y0>=0){
			must_inside_activated=true;
			inside_left=left;
			inside_right=0;
			inside_up=up;
			inside_down=y0;
			//check x[3]
			if(x1>=inside_right)//inside_right=0
				return true;
			else{
				inside_right=inside_left+x[3];
			}

		}else{

			if(x1<0){
				must_inside_activated=true;
				inside_left=left;
				inside_right=x1;
				inside_up=up;
				inside_down=y1;
			}else if(x1==0){
				must_inside_activated=true;
				inside_left=left;
				inside_right=x1;
				inside_up=0;
				inside_down=y1;
			}else{
				must_outside_activated=true;
				outside_left=left;
				outside_right=0;
				outside_up=up;
				outside_down=0;
			}
		}



		//process x[4],x[5],......////////////////////////////////////////////////
		for(int i=4;i<x.size();i+=4){
			
			//i,   go up
			x0=x1;y0=y1;
			y1=y0+x[i];
			if(must_inside_activated){
				if(y1>=inside_up)
					return true;
				else{
					inside_up=y1;
				}
			}else{
				if(y1<outside_down){
					must_inside_activated=true;
					inside_up=y1;
					inside_down=y0;
					inside_left=outside_left;
					inside_right=x1;
				}else if(y1<=outside_up){
					must_inside_activated=true;
					inside_left=outside_right;
					inside_up=y1;
					inside_right=x1;
					inside_down=y0;
				}else{
					outside_down=y0;
				}
			}
			if(i+1>=x.size())
				break;

			//i+1, go left
			x0=x1;y0=y1;
			x1=x0-x[i+1];
			if(must_inside_activated){
				if(x1<=inside_left)
					return true;
				else{
					inside_left=x1;
				}
			}else{
				if(x1>outside_right){
					must_inside_activated=true;
					inside_up=y1;
					inside_down=outside_down;
					inside_left=x1;
					inside_right=x0;
				}else if(x1>=outside_left){
					must_inside_activated=true;
					inside_left=x1;
					inside_up=y1;
					inside_down=outside_up;
					inside_right=x0;
				}else{
					outside_right=x0;
				}
			}
			if(i+2>=x.size())
				break;

			//i+2, go down
			x0=x1;y0=y1;
			y1=y0-x[i+2];
			if(must_inside_activated){
				if(y1<=inside_down)
					return true;
				else{
					inside_down=y1;
				}
			}else{
				if(y1>outside_up){
					must_inside_activated=true;
					inside_up=y0;
					inside_down=y1;
					inside_left=x1;
					inside_right=outside_right;
				}else if(y1>=outside_down){
					must_inside_activated=true;
					inside_left=x1;
					inside_up=y0;
					inside_right=outside_left;
					inside_down=y1;
				}else{
					outside_up=y0;
				}
			}
			if(i+3>=x.size())
				break;
			//i+3, go right
			x0=x1;y0=y1;
			x1=x0+x[i+3];
			if(must_inside_activated){
				if(x1>=inside_right)
					return true;
				else{
					inside_right=x1;
				}
			}else{
				if(x1<outside_left){
					must_inside_activated=true;
					inside_up=outside_up;
					inside_down=y1;
					inside_left=x0;
					inside_right=x1;
				}else if(x1<=outside_right){
					must_inside_activated=true;
					inside_left=x0;
					inside_up=outside_down;
					inside_down=y1;
					inside_right=x1;
				}else{
					outside_left=x0;
				}
			}

		}
		return false;
    }
};
