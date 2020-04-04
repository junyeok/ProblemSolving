#include <iostream>
#include <vector>
#include <limits>

class MaxProduct {
public:
  int maxProduct(std::vector<int>& nums) {
    
    if(nums.size() == 1) {
      return nums[0];
    }

    auto iter = nums.begin();
    int global_max = *iter;
    std::advance(iter,1);

    int prev_max = global_max;
    int prev_min = global_max;

    for(iter; iter != nums.end();) {
      int curr_num = *iter;
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