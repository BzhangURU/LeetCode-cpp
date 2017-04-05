/*Implement a data structure supporting the following operations:

Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.
Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1. 
If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".
Challenge: Perform all these in O(1) time complexity.*/
struct node432{
	int value;
	node432* next;
	node432* previous;
	node432(int v){
		this->value=v;
		this->next=NULL;
		this->previous=NULL;
	}
};
class AllOne {
public:
	unordered_map<string,node432*> map_str2node;
	unordered_map<int,unordered_set<string>> map_value2set;
	node432* start_node;
	node432* end_node;

    /** Initialize your data structure here. */
    AllOne() {
		//build an ordered(inreasing) linked list, no duplicates
        node432* start_n=new node432(-1);
		node432* end_n=new node432(-1);
		start_n->next=end_n;
		end_n->previous=start_n;
		start_node=start_n;
		end_node=end_n;
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
		unordered_map<string,node432*>::iterator iter=map_str2node.find(key);
        if(iter==map_str2node.end()){//a new string, so value=1
			if(start_node->next->value==1){
				map_str2node[key]=start_node->next;
				//unordered_map<int,unordered_set<string>>::iterator ier2=map_value2set.find(1);
				map_value2set[1].insert(key);
			}else{//there is no string whose value is 1 before
				node432* new_node=new node432(1);
				new_node->next=start_node->next;
				new_node->previous=start_node;
				start_node->next->previous=new_node;
				start_node->next=new_node;
				map_str2node[key]=new_node;
				unordered_set<string> new_set;
				new_set.insert(key);
				map_value2set[1]=new_set;
			}
			
		}else{//not a new string
			int value=map_str2node[key]->value;
			unordered_map<int,unordered_set<string>>::iterator iter_value=map_value2set.find(value);
			unordered_map<int,unordered_set<string>>::iterator iter_valueadd1=map_value2set.find(value+1);
			//both value and value+1 exist except key
			if(((*iter_value).second).size()>1&&(iter_valueadd1!=map_value2set.end())){
				((*iter_value).second).erase(key);
				((*iter_valueadd1).second).insert(key);
				((*iter).second)=((*iter).second)->next;
			}else if(map_value2set[value].size()==1&&(iter_valueadd1!=map_value2set.end())){//only value+1 exists except key
				//only value+1  exists except key
				//delete node
				//((*iter).second)==map_str2node[key]
				((*iter).second)->previous->next=((*iter).second)->next;
				((*iter).second)->next->previous=((*iter).second)->previous;
				((*iter).second)=((*iter).second)->next;
				((*iter_valueadd1).second).insert(key);
				map_value2set.erase(value);
			}else if(map_value2set[value].size()>1&&(iter_valueadd1==map_value2set.end())){
				//only value exists except key

				//create new node[value+1]
				node432* new_node=new node432(value+1);
				new_node->previous=(*iter).second;
				new_node->next=((*iter).second)->next;
				new_node->next->previous=new_node;
				new_node->previous->next=new_node;
				((*iter).second)=new_node;

				((*iter_value).second).erase(key);

				unordered_set<string> new_set;
				new_set.insert(key);
				map_value2set[value+1]=new_set;

			}else{
				//neither value nor value+1 exists except key
				((*iter).second)->value=value+1;
				unordered_set<string> new_set;
				new_set.insert(key);
				map_value2set[value+1]=new_set;
				map_value2set.erase(value);//neither value nor value+1 exists except key

			}
		}
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {

		unordered_map<string,node432*>::iterator iter=map_str2node.find(key);
        if(iter!=map_str2node.end()){//not a new string. otherwise do nothing
			int value=map_str2node[key]->value;
			if(value==1){
				unordered_map<int,unordered_set<string>>::iterator iter_value=map_value2set.find(value);
				if(((*iter_value).second).size()>1){
					((*iter_value).second).erase(key);
					map_str2node.erase(key);

				}else{
					map_value2set.erase(1);
					//delete node
					((*iter).second)->next->previous=((*iter).second)->previous;
					((*iter).second)->previous->next=((*iter).second)->next;
					map_str2node.erase(key);
				}
			}else{




				unordered_map<int,unordered_set<string>>::iterator iter_value=map_value2set.find(value);
				unordered_map<int,unordered_set<string>>::iterator iter_valueminus1=map_value2set.find(value-1);
				//both value and value-1 exist except key
				if(((*iter_value).second).size()>1&&(iter_valueminus1!=map_value2set.end())){
					((*iter_value).second).erase(key);
					((*iter_valueminus1).second).insert(key);
					((*iter).second)=((*iter).second)->previous;
				}else if(map_value2set[value].size()==1&&(iter_valueminus1!=map_value2set.end())){//only value+1 exists except key
					//only value-1  exists except key
					//delete node
					//((*iter).second)==map_str2node[key]
					((*iter).second)->next->previous=((*iter).second)->previous;
					((*iter).second)->previous->next=((*iter).second)->next;
					((*iter).second)=((*iter).second)->previous;
					((*iter_valueminus1).second).insert(key);
					map_value2set.erase(value);
				}else if(map_value2set[value].size()>1&&(iter_valueminus1==map_value2set.end())){
					//only value exists except key

					//create new node[value+1]
					node432* new_node=new node432(value-1);
					new_node->next=(*iter).second;
					new_node->previous=((*iter).second)->previous;
					new_node->previous->next=new_node;
					new_node->next->previous=new_node;
					((*iter).second)=new_node;

					((*iter_value).second).erase(key);

					unordered_set<string> new_set;
					new_set.insert(key);
					map_value2set[value-1]=new_set;

				}else{
					//neither value nor value+1 exists except key
					((*iter).second)->value=value-1;
					unordered_set<string> new_set;
					new_set.insert(key);
					map_value2set[value-1]=new_set;
					map_value2set.erase(value);//neither value nor value+1 exists except key

				}

			}
		}


    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
			if(end_node->previous->value==-1)
				return "";
			else return *(map_value2set[end_node->previous->value].begin());
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
	
		if(start_node->next->value==-1)
			return "";
		else return *(map_value2set[start_node->next->value].begin());
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */
