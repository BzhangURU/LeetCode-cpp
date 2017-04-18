/*Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
Note: 
You may assume k is always valid, 1 ≤ k ≤ n2.*/


class Solution {
public:
    struct element378{
    	int value;
    	int row;
    	int col;
    	element378(int a,int b,int c){
    		this->value=a;
    		this->row=b;
    		this->col=c;
    	}
    };
    
    struct myclass{
    	bool operator()(element378 a,element378 b){
    		return a.value<b.value;
    	}
    };
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        if(k==1)
    		return matrix[0][0];
    	int n=matrix.size();
    	unordered_map<int,int> col2row;
    	multiset<element378,myclass> heap;
    	element378 new_e(matrix[0][0],0,0);
    	heap.insert(new_e);
    	col2row[0]=0;
    
    	int get_num;
    	for(int i=0;i<k;i++){
    		get_num=(*heap.begin()).value;
    		int col=(*heap.begin()).col;
    		int row=(*heap.begin()).row;
    		heap.erase(heap.begin());
    		if(col+1<n&&col2row.find(col+1)==col2row.end()){
    			element378 new_e(matrix[row][col+1],row,col+1);
    			heap.insert(new_e);
    			col2row[col+1]=row;
    		}
    		if(row+1<n){
    			element378 new_e(matrix[row+1][col],row+1,col);
    			heap.insert(new_e);
    			col2row[col]=row+1;
    		}
    
    	}
    
    	return get_num;
    }
};

