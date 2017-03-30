/*You have a number of envelopes with widths and heights given as a pair of integers (w, h). One envelope can fit into another 
if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Example:
Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).*/

bool a_can_contain_b(vector<pair<int, int>>& envelopes,int a,int b){
	if(envelopes[a].first>envelopes[b].first&&envelopes[a].second>envelopes[b].second)
		return true;
	//else if(envelopes[a].first>envelopes[b].second&&envelopes[a].second>envelopes[b].first)
		//return true;
	else return false;
}

//get the maximum num when this_ind is the most outside envelope
int get_num_if_this_is_most_outside(vector<pair<int, int>>& envelopes, int this_ind, vector<int>& save_num){
	if(save_num[this_ind]>0)
		return save_num[this_ind];
	int num=1,temp_num;
	for(int i=0;i<envelopes.size();i++){
		//if(a_can_contain_b(envelopes,this_ind,i)){
		if(envelopes[this_ind].first>envelopes[i].first&&envelopes[this_ind].second>envelopes[i].second){
			temp_num=get_num_if_this_is_most_outside(envelopes, i, save_num);
			num=num<temp_num+1?temp_num+1:num;
		}
	}
	save_num[this_ind]=num;
	return num;
}

int maxEnvelopes(vector<pair<int, int>>& envelopes) {
    if(envelopes.size()<=0)
		return 0;
	vector<int> save_num(envelopes.size(),0);
	int max=1,num;
	for(int i=0;i<envelopes.size();i++){
		num=get_num_if_this_is_most_outside(envelopes, i, save_num);
		cout<<"pair= "<<envelopes[i].first<<","<<envelopes[i].second<<"   num="<<num<<endl;
		if(max<num)
			max=num;
	}
	return max;
}
