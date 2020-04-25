#include <vector>
#include <numeric>
#include <iostream>

class MCTree {
public:
  // class node {
  //  public:
  //   node(node* lh, node* rh) : val(lh->val * rh->val), child_lh(lh), child_rh(rh) { }
  //   node(int v) : val(v), child_lh(nullptr), child_rh(nullptr) { }

  //   int val;
  //   node* child_lh;
  //   node* child_rh;

  //   int GetMax() {
  //     if(IsLeaf()) return val;
  //     return std::max(child_lh->val,child_rh->val);
  //   }

  //   int GetCost() {
  //     if(IsLeaf()) return 0;
  //     int cost = val;
  //     if(!child_lh->IsLeaf()) cost += child_lh->GetCost();
  //     if(!child_rh->IsLeaf()) cost += child_rh->GetCost();
  //     return cost;
  //   }

  //   bool IsLeaf() {
  //     return child_lh == nullptr && child_rh == nullptr;
  //   }
  // };


  int mctFromLeafValues(std::vector<int>& arr) {
    size_t n = arr.size();
    std::vector<std::vector<int>> max(n, std::vector<int>(n,0));
    std::vector<std::vector<int>> min_cost(n, std::vector<int>(n,INT32_MAX));
    
    for(size_t i = 0; i < n; ++i) {
      max[i][i] = arr[i];
      for(size_t j = i + 1; j < n; ++j) {
        max[i][j] = std::max(max[i][j-1], arr[j]);
      }
    }

    return dp(0,n-1,max,min_cost);
  }

  int dp(size_t left,size_t right,std::vector<std::vector<int>>& max, std::vector<std::vector<int>>& min_cost) {
    if(left == right) {
      min_cost[left][right] = 0;
      return 0;
    }
    int cost = min_cost[left][right];
    if(cost != INT32_MAX) return cost;
    
    for(size_t i = left; i<right; ++i) {
      cost = std::min(cost, dp(left,i,max,min_cost) + dp(i+1,right,max,min_cost) + max[left][i] * max[i+1][right] );
    }
    
    min_cost[left][right] = cost;
    return cost;
  }
};