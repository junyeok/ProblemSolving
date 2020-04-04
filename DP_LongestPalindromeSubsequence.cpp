#include <string>
#include <vector>

/**
 * len = 1 부터 차례대로 dp에 채워나감
 * i와 j 사이의 longest Palindrom을 M(i,j)라 할 때,
 *  M(i,j) = 1 when len == 1
 *  M(i,j) = M(i+1,j-1) + 2 when str(i) == str(j)
 *  M(i,j) = max(M(i+1,j),M(i,j-1)) when str(i) != str(j)
 * 이다. dp matrix를 순서대로 채워나가는 것이 중요하므로,
 * length를 기준으로 loop를 수행함
 */
class LongestPalindrome {
public:
  int longestPalindromeSubseq(std::string s) {
    size_t n = s.size();
    if(n <= 1) return n;
    
    std::vector<std::vector<int>> dp(n, std::vector<int> (n,0));
    for(size_t len = 1; len <= n; ++len) {
      for(size_t i = 0; i + len <= n; ++i) {
        size_t j = i + len - 1;
        if(len == 1) {
          dp[i][j] = 1;
        } else if(s[i] == s[j]) {
          dp[i][j] = dp[i+1][j-1] + 2;
        } else {
          dp[i][j] = std::max(dp[i+1][j],dp[i][j-1]);
        }
      }
    }

    return dp[0][n-1];   
  }
};