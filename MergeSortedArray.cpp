#include <iostream>
#include <vector>

class MergeSortedArray {
public:
  void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    if(n == 0) {
      return;
    }
    if(m == 0) {
      nums1 = nums2;
      return;
    }
    if(nums1[0] >= nums2[n-1]) {
      for(size_t i = 0; i < n; ++i) {
        Insert(nums1,i,nums2[i]);
      }
      return;
    }
    if(nums1[m-1] <= nums2[0]) {
      for(size_t i = 0; i < n; ++i) {
        Insert(nums1,i + m, nums2[i]);
      }
      return;
    }
    
    size_t idx = 0;
    size_t end = m-1;
    for(auto merging_num : nums2) {
      /*merging num이 num1의 max 값보다 작을 때*/
      while(idx <= end) {
        if(nums1[idx] > merging_num) {
          Insert(nums1,idx,merging_num);
          idx += 1;
          end += 1;
          break;
        }
        idx += 1;
      }
      /*merging num이 num1의 max 값보다 클 때*/
      if(idx > end) {
        Insert(nums1,idx,merging_num);
        idx += 1;
        continue;
      }
    }
  }


  void Insert(std::vector<int>& tgt_vector, size_t idx, int arg) {
    for(size_t i = tgt_vector.size() - 1; i > idx; --i) {
      tgt_vector[i] = tgt_vector[i-1];
    }
    tgt_vector[idx] = arg;
  }

};