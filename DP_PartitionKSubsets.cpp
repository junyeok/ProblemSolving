#include <vector>
#include <numeric>
#include <algorithm>

class PartitionKSubsets {
public:
	bool canPartitionKSubsets(std::vector<int>& nums, int k) {
		if(nums.size() < k) return false;
		int sum = std::accumulate(nums.begin(),nums.end(),0);
		if(sum % k != 0) return false;
		int mean = sum / k;
		
		std::vector<bool> visited(nums.size(), false);
		return dfs(0,0,mean,k,nums,visited);
	}

	bool dfs(size_t idx, int val, int tgt, int k, std::vector<int>& nums, std::vector<bool>& visited) {
		// 나머지 경우가 모두 통과하고 k가 1일 때 남은 원소의 값은 항상 tgt와 같다. (평균이 균일하므로)
		if(k == 1) return true;
		if(val > tgt) return false;
		if(val == tgt) return dfs(0,0,tgt,k-1,nums,visited);
		for (int i = idx; i<nums.size(); i++) {
			if(!visited[i]){
				visited[i] = true;
				if(dfs(i + 1, val + nums[i], tgt, k, nums, visited)) return true;
				visited[i] = false;
			}
		}
		return false;
	}
};
