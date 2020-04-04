#include <vector>
#include <stack>
#include <algorithm>

class MaximalRectangle {
public:
  int maximalRectangle(std::vector<std::vector<char>>& matrix) {
    if(matrix.empty()) return 0;
    size_t m = matrix.size();
    size_t n = matrix[0].size();

    std::vector<int> height(n,0);
    auto convert = [](char tgt) {
      return tgt - '0';
    };

    int global_max = 0;

    for(size_t i = 0; i < m; ++i) {
      for(size_t j = 0; j < n; ++j) {
        if (matrix[i][j] == '0') {
          height[j] = 0;
        } else {
          height[j] = height[j] + convert(matrix[i][j]);
        }
      }
      global_max = std::max(global_max, calculateArea(height));
    }

    return global_max;
  }

  int calculateArea(std::vector<int> height) {
    std::stack<int> s;
    height.push_back(0);
    int max = 0;
    for(int i = 0; i < height.size(); ++i) {
      if(s.empty() || height[s.top()] <= height[i]) {
        s.push(i);
      } else {
        int top = s.top();
        s.pop();
        int width = s.empty() ? i : i - s.top() - 1;
        max = std::max(max, width * height[top]);
        --i;
      }
    }
    return max;
  }
};