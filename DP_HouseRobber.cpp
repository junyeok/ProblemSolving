#include <vector>


class Rob {
public:
  /**
   * 주어진 배열에서 아래 규칙을 만족하는 최대의 합을 구하는 문제
   *  < 인접한 두 요소는 연속으로 방문할 수 없다. >
   * 
   * S(n)을 n번째 인자에서의 최대의 합이라 할 때,
   * S(n) = max(S(n-2)+a(n), S(n-1)) 이다.
   * 
   * S(0) = a(0)
   * S(1) = max(a(0),a(1))
   * ... S(n)까지의 계산 결과를 채워가며 DP로 풀이함.
   * 
   * Time Complexity: O(n) / Space Complexity: O(n)
   * 
   */
  int rob1(std::vector<int>& nums) {
    size_t n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    std::vector<int> save(n,0);
    save[0] = nums[0];
    save[1] = std::max(nums[0],nums[1]);

    for(size_t i = 2; i < n; ++i) {
      save[i] = std::max(save[i-2]+nums[i], save[i-1]);
    }
    
    return save[n-1];
  }

  /**
   * rob1의 Space Complexity를 개선
   * 굳이 n개의 메모할 공간을 차지할 필요가 없고,
   * 현재 인자 위치를 기준으로, S(n-1)과 S(n-2)만 알면 충분하다.
   * 
   * Time Complexity: O(n) / Space Complexity: O(1)
   */
  int rob2(std::vector<int>& nums) {
    size_t n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    int prev = nums[0];
    int curr = std::max(nums[0],nums[1]);

    for(size_t i = 2; i < n; ++i) {
      int temp = std::max(prev+nums[i], curr);
      prev = curr;
      curr = temp;
    }
    
    return curr;
  }
};