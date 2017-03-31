/*Design a data structure that supports all following operations in average O(1) time.

Note: Duplicate elements are allowed.
insert(val): Inserts an item val to the collection.
remove(val): Removes an item val from the collection if present.
getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.
Example:

// Init an empty collection.
RandomizedCollection collection = new RandomizedCollection();

// Inserts 1 to the collection. Returns true as the collection did not contain 1.
collection.insert(1);

// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
collection.insert(1);

// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
collection.insert(2);

// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
collection.getRandom();

// Removes 1 from the collection, returns true. Collection now contains [1,2].
collection.remove(1);

// getRandom should return 1 and 2 both equally likely.
collection.getRandom();*/
class RandomizedCollection {
public:

	unordered_map<int,unordered_set<int>> get_ind;//get_ind[5] shows all locations of 5 in "nums"
	vector<int> nums;
    /** Initialize your data structure here. */
    RandomizedCollection() {
        time_t t;
		srand((unsigned)time(&t));
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        if(get_ind.find(val)!=get_ind.end()){
			get_ind[val].insert(nums.size());
			nums.push_back(val);
		}else{
			unordered_set<int> indexes;
			indexes.insert(nums.size());
			get_ind[val]=indexes;
			nums.push_back(val);
		}
		return true;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if(get_ind.find(val)==get_ind.end())
			return false;
		else{

			int location=*(get_ind[val].begin());
			if(location==nums.size()-1){
				get_ind[val].erase(nums.size()-1);
				nums.pop_back();
			}else{//swap to last element
				nums[location]=nums[nums.size()-1];
				get_ind[val].erase(location);
				get_ind[nums[nums.size()-1]].erase(nums.size()-1);
				get_ind[nums[nums.size()-1]].insert(location);
				nums.pop_back();
			}
			if(get_ind[val].empty())
					get_ind.erase(val);

			return true;
		}
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        if(nums.size()==0)
			return INT_MIN;
		return nums[rand()%nums.size()];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
