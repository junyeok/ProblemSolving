#include <vector>

class Permutation {
public:
  std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> sol;
    std::vector<int> sub_sol;
    std::vector<bool> visited(nums.size(),false);

    for(size_t i = 0; i < nums.size(); ++i) {
      dfs(nums,sol,sub_sol,visited,i);
    }
    return sol;
  }
  
  void dfs(std::vector<int>&nums, std::vector<std::vector<int>>& sol, std::vector<int> sub_sol, std::vector<bool> visited, int curr_idx) {
    sub_sol.push_back(nums[curr_idx]);
    visited[curr_idx] = true;
    if(sub_sol.size() == nums.size()) {
      sol.push_back(sub_sol);
      return;
    }
    for(size_t i = 0; i < nums.size(); ++i) {
      if(visited[i]) continue;
      dfs(nums,sol,sub_sol,visited,i);
    }
  }


  std::vector<std::vector<int>> permute2(std::vector<int>& nums) {
    std::vector<std::vector<int>> sol;
    dfs2(nums,sol,0);
    return sol;
  }
  
  void dfs2(std::vector<int>&nums, std::vector<std::vector<int>>& sol, int curr_idx) {
    if(curr_idx == nums.size()) {
      sol.push_back(nums);
      return;
    }
    for(size_t i = curr_idx; i < nums.size(); ++i) {
      std::swap(nums[curr_idx],nums[i]);
      dfs2(nums,sol,curr_idx+1);
      std::swap(nums[curr_idx],nums[i]);
    }
  }
};