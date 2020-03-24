#include <iostream>
#include <vector>
#include <limits>

class Solution {
public:
  int maxProduct(std::vector<int>& nums) {
    
    if(nums.size() == 1) {
      return nums[0];
    }

    auto iter = nums.begin();
    int local_max = *iter;
    int global_max = local_max;
    std::advance(iter,1);

    int prev_max = local_max;
    int prev_min = local_max;

    for(iter; iter != nums.end();) {
      int curr_num = *iter;
      int prev_num = *(std::prev(iter,1));
      int curr_max = std::max(
        prev_min * curr_num,
        std::max(curr_num * prev_max, curr_num)
      );

      int curr_min = std::min(
        prev_min * curr_num,
        std::min(prev_max * curr_num, curr_num)
      );
      
      if(curr_max >= prev_max) {
        global_max = std::max(global_max,curr_max);
      }

      prev_max = curr_max;
      prev_min = curr_min;     
      std::advance(iter,1);
    }

    return global_max;
  }
};