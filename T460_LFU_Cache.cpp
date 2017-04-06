/*Design and implement a data structure for Least Frequently Used (LFU) cache. 
It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, 
it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, 
when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LFUCache cache = new LFUCache( 2  );//capacity

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4*/
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
struct node460{
	int key;
	int value;
	int frequency;
	node460* previous;
	node460* next;
	node460(int k, int v,int f){
		this->key=k;
		this->value=v;
		this->frequency=f;
		this->previous=NULL;
		this->next=NULL;
	}
};

//my solution: for each frequency, there is a linked list with nodes, the fake start node is most currently used, 
//the fake end node is least currently used
//Each node in linked list has same frequency
class LFUCache {
public:
	int capacity;
	int current_size;
	int lowest_fre;
	unordered_map<int,node460*> map_key2node;
	unordered_map<int,pair<node460*,node460*>> map_fre2nodes;//first node is start(often used), second is end node(least recently used)
    LFUCache(int capacity) {
		this->capacity=capacity;
		this->current_size=0;
		this->lowest_fre=0;//==0 if there is nothing
    }
    
    int get(int key) {
		if(map_key2node.find(key)==map_key2node.end())
			return -1;
		else{
			int node_old_fre=map_key2node[key]->frequency;
			(map_key2node[key]->frequency)++;
			int value=map_key2node[key]->value;
			if(lowest_fre==node_old_fre&&map_fre2nodes[node_old_fre].first->next->next->next==NULL){//there is only one element in linked list
				lowest_fre++;
			}

			//there is only one element in linked list, erase it
			//process linked list of  node_old_fre
			if(map_fre2nodes[node_old_fre].first->next->next->next==NULL)
				map_fre2nodes.erase(node_old_fre);
			else{
				node460* cur_node=map_key2node[key];
				cur_node->previous->next=cur_node->next;
				cur_node->next->previous=cur_node->previous;
			}


			//process linked list of  node_old_fre+1
			if(map_fre2nodes.find(node_old_fre+1)!=map_fre2nodes.end()){
				node460* new_node=new node460(key,value,node_old_fre+1);
				node460* start_n=map_fre2nodes[node_old_fre+1].first;
				//node460* end_n=map_fre2nodes[node_old_fre+1].second;
				new_node->next=start_n->next;
				new_node->previous=start_n;
				start_n->next->previous=new_node;
				start_n->next=new_node;
				map_key2node[key]=new_node;
			}else{//build a new linked list
				node460* new_node=new node460(key,value,node_old_fre+1);
				node460* start_n=new node460(-1,-1,node_old_fre+1);
				node460* end_n=new node460(-1,-1,node_old_fre+1);
				start_n->next=new_node;
				new_node->next=end_n;
				end_n->previous=new_node;
				new_node->previous=start_n;
				map_fre2nodes[node_old_fre+1]=make_pair(start_n,end_n);
				map_key2node[key]=new_node;
			}


			return value;
		}
    }
    
    void put(int key, int value) {
		if(capacity<=0)
			return;
		if(map_key2node.find(key)==map_key2node.end()){//new node
			if(current_size>=capacity){
				//delete a node(end of lowest frequency), if lowest frequency==1, don't delete start node and end node of fre==1
				if(lowest_fre==1){
					node460* end_node=map_fre2nodes[1].second;
					map_key2node.erase(end_node->previous->key);
					end_node->previous->previous->next=end_node;
					end_node->previous=end_node->previous->previous;
				}else{
					//node460* start_node=map_fre2nodes[lowest_fre].first;
					node460* end_node=map_fre2nodes[lowest_fre].second;
					map_key2node.erase(end_node->previous->key);
					end_node->previous->previous->next=end_node;
					end_node->previous=end_node->previous->previous;
					if(end_node->previous->previous==NULL)
						map_fre2nodes.erase(lowest_fre);
				}
				
			}else
				current_size++;

			node460* new_node=new node460(key,value,1);//initial fre=1
			if(lowest_fre==1){//add node to front of linked list of fre=1
				node460* start_node=map_fre2nodes[1].first;
				new_node->next=start_node->next;
				new_node->previous=start_node;
				start_node->next->previous=new_node;
				start_node->next=new_node;
			}else{//create a new linked list of fre=1
				node460* new_node=new node460(key,value,1);
				node460* start_n=new node460(-1,-1,1);
				node460* end_n=new node460(-1,-1,1);
				start_n->next=new_node;
				new_node->next=end_n;
				end_n->previous=new_node;
				new_node->previous=start_n;
				map_fre2nodes[1]=make_pair(start_n,end_n);
			}
			map_key2node[key]=new_node;
			lowest_fre=1;
		}else{//key already exists, just change its value
			//node460* current_node=map_key2node[key];
			//current_node->value=value;
			int node_old_fre=map_key2node[key]->frequency;
			//node460* start_node=map_fre2nodes[old_frequency].first;
			


			if(map_fre2nodes[node_old_fre].first->next->next->next==NULL){
				map_fre2nodes.erase(node_old_fre);
				if(node_old_fre==lowest_fre)
					lowest_fre++;
			}else{
				node460* cur_node=map_key2node[key];
				cur_node->previous->next=cur_node->next;
				cur_node->next->previous=cur_node->previous;
			}




			//process linked list of  node_old_fre+1
			if(map_fre2nodes.find(node_old_fre+1)!=map_fre2nodes.end()){
				node460* new_node=new node460(key,value,node_old_fre+1);
				node460* start_n=map_fre2nodes[node_old_fre+1].first;
				//node460* end_n=map_fre2nodes[node_old_fre+1].second;
				new_node->next=start_n->next;
				new_node->previous=start_n;
				start_n->next->previous=new_node;
				start_n->next=new_node;
				map_key2node[key]=new_node;
			}else{//build a new linked list
				node460* new_node=new node460(key,value,node_old_fre+1);
				node460* start_n=new node460(-1,-1,node_old_fre+1);
				node460* end_n=new node460(-1,-1,node_old_fre+1);
				start_n->next=new_node;
				new_node->next=end_n;
				end_n->previous=new_node;
				new_node->previous=start_n;
				map_fre2nodes[node_old_fre+1]=make_pair(start_n,end_n);
				map_key2node[key]=new_node;
			}





		}
		

    }
};

