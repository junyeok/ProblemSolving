#include <vector>

class MinimumPathSum {
public:
	/**
	 * M * N size의 grid가 존재할 때, grid[0][0]에서 grid[m-1][n-1]까지의 최소 탐색 비용을 구하는 문제.
	 * 현재 지점까지의 minimum cost를 저장하는 방식의 DP로 품.
	 * 
	 * Time complexity: O(MN) / Space complexity: O(MN)
	 * 
	 */
	int minPathSum(std::vector<std::vector<int>>& grid) {
		size_t m = grid.size();
		size_t n = grid[0].size();
		std::vector<std::vector<int>> save(m,std::vector<int>(n,0));
		save[0][0] = grid[0][0];
		for(size_t i = 1; i < m; ++i) {
			save[i][0] = save[i-1][0] + grid[i][0];
		}
		for(size_t i = 1; i < n; ++i) {
			save[0][i] = save[0][i-1] + grid[0][i];
		}
		for(size_t i = 1; i < m; ++i ) {
			for(size_t j = 1; j < n; ++j) {
				save[i][j] = std::min(save[i-1][j],save[i][j-1])+grid[i][j];
			}
		}
		return save[m-1][n-1];
	}
};