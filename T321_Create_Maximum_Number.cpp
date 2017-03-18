class Solution {
public:
    #define MIN(a,b) (a<b?a:b)
    #define MAX(a,b) (a>b?a:b)
    //the first vector is largest number for max_length==min(size(),k), the last vector is longest without length constraint. 
    //for example if nums1=[3, 4, 6, 5], max_length=3, min_length=1
    //then largest_num1=  4 6 5(start from length=3)
    //											6  5(length=2), 
    //											6(length=1)
    //The min possible length of last vector in largest_num1 is 0
    //The min possible length of first vector in largest_num1 is 1
    void build_largest_number_for_each_length(vector<vector<int>>& largest_num1,vector<int>& nums1,int max_length,int min_length){
    	if(nums1.size()==0)
    		return;
    	vector<int> vec;
    	if(max_length<nums1.size()){
    		int dif=nums1.size()-max_length;
    		//vector<int> temp;
    		stack<int>  st;
    		int t=0;
    		while(t<nums1.size()){
    			while(!st.empty()&&st.top()<nums1[t]&&dif>0){
    				st.pop();
    				dif--;
    			}
    			st.push(nums1[t]);
    			t++;
    		}
    
    		///put nums in stack into first vector of largest_num1
    		stack<int> st_temp;
    		while(!st.empty()){
    			st_temp.push(st.top());
    			st.pop();
    		}
    		int count=0;
    		while(count<max_length&&!st_temp.empty()){
    			vec.push_back(st_temp.top());
    			st_temp.pop();
    			count++;
    		}
    	}else{
    		copy(nums1.begin(), nums1.end(), back_inserter(vec));
    	}
    	largest_num1.push_back(vec);
    
    	///////build remaining vectors to largest_num1///////////////////////////////////////////////
    	vector<int> vec_prev(vec);
    	for(int i=max_length-1;i>=min_length;i--){
    		vector<int> vec_cur;
    		int k=0;
    		while(k<vec_prev.size()-1){
    			if(vec_prev[k]>=vec_prev[k+1]){
    				vec_cur.push_back(vec_prev[k]);
    				k++;
    			}else{
    				k++;
    				break;
    			}
    		}
    		if(vec_cur.size()==vec_prev.size()-1){//already without length constraint
    			;//do nothing, just don't copy the last element of vec_prev
    		}else{
    			while(k<vec_prev.size()){
    				vec_cur.push_back(vec_prev[k]);
    				k++;
    			}
    		}
    		largest_num1.push_back(vec_cur);
    		vec_prev.clear();
    		copy(vec_cur.begin(), vec_cur.end(), back_inserter(vec_prev));
    
    	}
    
    }
    //if max_result is larger, return -1, else return the index that need to start to replace
    int max_result_replace_start_ind(vector<int> max_result,vector<int> cur_vector){
    	for(int i=0;i<max_result.size();i++){
    		if(max_result[i]<cur_vector[i])
    			return i;
    		else if(max_result[i]>cur_vector[i])
    			return -1;//!!!!!!!
    	}
    	return -1;
    }
    
    
    //v1=67   v2=604,     which 6 should you merge first????
    vector<int> merge_vector(vector<int> vector1,vector<int> vector2){
    	vector<int> result;
    	int k1=0,k2=0;
    	while(k1<vector1.size()||k2<vector2.size()){
    		if(k1==vector1.size()){
    			result.push_back(vector2[k2]);
    			k2++;
    		}else if(k2==vector2.size()){
    			result.push_back(vector1[k1]);
    			k1++;
    		}else if(vector1[k1]>vector2[k2]){
    			result.push_back(vector1[k1]);
    			k1++;
    		}else if(vector1[k1]<vector2[k2]){
    			result.push_back(vector2[k2]);
    			k2++;
    		}else{//vector1[k1]==vector2[k2]    666        6666669,                           668   6666
    			int temp_k1=k1+1,temp_k2=k2+1;
    			//while(temp_k1!=vector1.size()&&temp_k2!=vector2.size()){
    			while(true){
    				if(temp_k1==vector1.size()){
    					result.push_back(vector2[k2]);
    							k2++;
    					while(k2<vector2.size()&&vector2[k2]==vector2[k2-1]){
    						result.push_back(vector2[k2]);
    						k2++;
    					}
    					break;
    					
    				}else if(temp_k2==vector2.size()){
    					result.push_back(vector1[k1]);
    							k1++;
    					while(k1<vector1.size()&&vector1[k1]==vector1[k1-1]){
    						result.push_back(vector1[k1]);
    						k1++;
    					}
    					break;
    
    
    				}else if(vector1[temp_k1]>vector2[temp_k2]){//!!!!!!!!!!!!!!!
    					result.push_back(vector1[k1]);
    							k1++;
    					while(k1<vector1.size()&&vector1[k1]==vector1[k1-1]){
    						result.push_back(vector1[k1]);
    						k1++;
    					}
    					break;
    				}else if(vector1[temp_k1]<vector2[temp_k2]){
    					result.push_back(vector2[k2]);
    							k2++;
    					while(k2<vector2.size()&&vector2[k2]==vector2[k2-1]){
    						result.push_back(vector2[k2]);
    						k2++;
    					}
    					break;
    				}else{
    					temp_k1++;
    					temp_k2++;
    				}
    			}//while(true)
    			
    
    
    		}
    	}
    	return result;
    }
    
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
            vector<int> max_result;
    		if(k<=0)
    			return max_result;
    		//then k>0, so m+n>0
    		for(int i=0;i<k;i++)
    			max_result.push_back(0);
    		vector<vector<int>> largest_num1;
    		vector<vector<int>> largest_num2;
    		if(nums1.size()==0){
    			build_largest_number_for_each_length(largest_num2,nums2,k,k);
    			return largest_num2[0];
    		}else if(nums2.size()==0){
    			build_largest_number_for_each_length(largest_num1,nums1,k,k);
    			return largest_num1[0];
    		}
    		int max_length1=MIN((int)nums1.size(),k);
    		int max_length2=MIN((int)nums2.size(),k);
    		int min_length1=MAX(0,k-(int)nums2.size());// size is unsigned
    		int min_length2=MAX(0,k-(int)nums1.size());
    		build_largest_number_for_each_length(largest_num1,nums1,max_length1,min_length1);
    		build_largest_number_for_each_length(largest_num2,nums2,max_length2,min_length2);
    		int length2;
    		for(int length1=min_length1;length1<=max_length1;length1++){
    			length2=k-length1;
    			vector<int> v1_extract=largest_num1[max_length1-length1];
    			vector<int> v2_extract=largest_num2[max_length2-length2];
    			//merge_v12 is the largest num when take length1 digits from vector1, and take length2 digits from vector2
    			vector<int> merge_v12=merge_vector(v1_extract,v2_extract);
    			
    			//compare
    			int start_ind=max_result_replace_start_ind(max_result,merge_v12);
    			if(start_ind>=0){//merge_v12 is larger
    				
    				for(int i=start_ind;i<k;i++){
    					max_result[i]=merge_v12[i];
    				}
    			}
    			
    		}
    		return max_result;
    }

};
