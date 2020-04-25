#include <deque>
#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
	/*DP : Time limit exceeded*/
	int shortestSubarray(std::vector<int>& A, int K) {
		int len = A.size();
		
		std::vector<std::vector<int>> save(len,std::vector<int>(len,0));

		int shortest_len = INT_MAX;

		for(int i = 0; i < len; ++i) {
			save[i][i] = A[i];
			if(save[i][i] >= K) {
				return 1;
			}
			for(int j = i + 1; j < len; ++j) {
				save[i][j] = save[i][j-1] + A[j];
				if(save[i][j] >= K) {
					shortest_len = std::min(shortest_len, j - i + 1);
					break;
				}
			}
		}

		return shortest_len == INT_MAX ? -1 : shortest_len;
	}

	/**Dequeue를 활용한 풀이
	 * B[i+1] = A[0] + A[1] + ... A[i]인 subsum B[i]를 정의하자.
	 * 두 index x1, x2에 대해 B(x2) - B(x1) = A(x1) + A(x1+2) + ... + A(x2-1)을 만족하므로
	 * B(x2) - B(x1) >= K이면 조건을 만족하는 subarray legnth는 x2-x1이다.
	 */
	int shortestSubarray2(std::vector<int>& A, int K) {
		int len = A.size();
		
		/*B[i+1] = A[0] + A[1] + ... A[i]*/
		std::vector<int> B(len + 1, 0);

		for(int i = 0; i < len; ++i) {
			B[i+1] = B[i] + A[i];
		}

		std::deque<int> idx;
		int shortest_len = INT_MAX;

		for(int i = 0; i < len + 1; ++i) {
			/* B(x2) - B(x1) = A(x1) + A(x1+2) + ... + A(x2-1) */
			while(!idx.empty() && B[i] >= B[idx.front()] + K) {
				shortest_len = std::min(shortest_len, i - idx.front());
				idx.pop_front();
			}
			/* i > idx.back() 일 때 B[idx.back()] 보다 B[i]가 더 작은 경우,
				 i 뒤에 y-i >= K을 만족하는 어떤 y가 존재한다고 하자.
				 이 때 y-idx.back() >= K를 만족할지라도, shortest length는 y-i이다.
				 즉 어떠한 경우에도 idx.back()이 시작 x로 작용할 여지는 없다.  */
			while(!idx.empty() && B[i] <= B[idx.back()]) {
				idx.pop_back();
			}
			idx.push_back(i);
		}

		return shortest_len == INT_MAX ? -1 : shortest_len;		
	}
};