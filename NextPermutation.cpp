#include <algorithm>
#include <iostream>
#include <vector>

class NextPermutation {
public:
  void nextPermutation(std::vector<int>& nums) {
    auto prev_iter = std::prev(nums.end(),1);
    auto curr_iter = std::prev(prev_iter,1);

    if(nums.size() <= 1) {
      return;
    }

    for(;prev_iter != nums.begin();) {
      if(*prev_iter <= *curr_iter) {
        prev_iter = std::prev(prev_iter,1);
        curr_iter = std::prev(curr_iter,1);
        continue;
      }

      auto target_iter = nums.end();
      while(target_iter != prev_iter) {
        target_iter = std::prev(target_iter,1);
        if(*curr_iter < *target_iter) {
          break;
        }
      }

      std::iter_swap(curr_iter,target_iter);
      std::reverse(prev_iter,nums.end());
      return;
    }

    std::reverse(nums.begin(),nums.end());
  }
};
