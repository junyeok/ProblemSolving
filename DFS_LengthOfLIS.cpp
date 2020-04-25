#include <vector>

class LongestIncreasingSubseq {
public:
  int lengthOfLIS(std::vector<int>& nums) {
    int max = 0;
    std::vector<int> dp(nums.size(), 1);

    for(size_t i = 0; i < nums.size(); ++i) {      
      for(size_t j = 0; j < i; ++j) {
        if(nums[j] < nums[i]) {
          dp[i] = std::max(dp[i],dp[j] + 1);
        }
      }
      max = std::max(max,dp[i]);
    }
    return max;
  }
};
