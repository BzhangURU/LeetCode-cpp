
/*Shuffle a set of numbers without duplicates.

Example:

// Init an array with set 1, 2, and 3.
int[] nums = {1,2,3};
Solution solution = new Solution(nums);

// Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must equally likely to be returned.
solution.shuffle();

// Resets the array back to its original configuration [1,2,3].
solution.reset();

// Returns the random shuffling of array [1,2,3].
solution.shuffle();*/


#include <random>       // T384
class Solution {
  private:
    vector<int> origin;
  public:

      Solution(vector<int> nums) {
          copy(nums.begin(),nums.end(),back_inserter(origin));
      }

      /** Resets the array to its original configuration and return it. */
      vector<int> reset() {
          vector<int> reset_v(origin);
      return reset_v;
      }

      /** Returns a random shuffling of the array. */
      vector<int> shuffle() {
          vector<int> shuffle_v(origin);
      // obtain a time-based seed:
      std::random_shuffle ( shuffle_v.begin(), shuffle_v.end() );
      return shuffle_v;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */
