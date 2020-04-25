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

		int shortest_len = len + 1;

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

		return shortest_len == len + 1 ? -1 : shortest_len;
	}

	/**Dequeue를 활용한 풀이
	 * 
	 * B[i+1] = A[0] + A[1] + ... A[i]인 subsum B[i]를 정의하자.
	 * 두 index x1, x2에 대해 B(x2) - B(x1) = A(x1) + A(x1+2) + ... + A(x2-1)을 만족하므로
	 * B(x2) - B(x1) >= K이면 조건을 만족하는 subarray legnth는 x2-x1이다.
	 * 
	 * 상세 풀이는 다음과 같다.
	 * 	- A index에 대한 for문을 돌면서 deque에 index를 저장한다.
	 * 	- 만약 현재 index i에서 B(i) - B(deque.front) >= K를 만족할 경우 shortest len을 갱신하고 front pop을 수행한다.
	 * 		-- pop을 해도 되는 이유는, i 뒤의 index가 위 조건을 만족한다고 하더라도 i-front이 값이 가장 shortest length이기 때문이다.
	 * 	- 추가적으로, B(deque.back)이 B(i)보다 크거나 같은 경우 pruning이 가능하다.
	 * 		-- 뒤에서 위 조건을 만족하는 index y가 존재할 때, B(y)-B(deque.back)을 만족한다면 B(y)-B(i)도 만족하며,
	 * 			 이 경우 shortest length는 y-i이기 때문이다.
	 */
	int shortestSubarray2(std::vector<int>& A, int K) {
		int len = A.size();
		
		/*B[i+1] = A[0] + A[1] + ... A[i]*/
		std::vector<int> B(len + 1, 0);

		for(int i = 0; i < len; ++i) {
			B[i+1] = B[i] + A[i];
		}

		std::deque<int> idx;
		int shortest_len = len + 1;

		for(int i = 0; i < len + 1; ++i) {
			while(!idx.empty() && B[i] >= B[idx.front()] + K) {
				shortest_len = std::min(shortest_len, i - idx.front());
				idx.pop_front();
			}
			while(!idx.empty() && B[i] <= B[idx.back()]) {
				idx.pop_back();
			}
			idx.push_back(i);
		}

		return shortest_len == len + 1 ? -1 : shortest_len;		
	}
};