#include <vector>
#include <string>


class Solution {
public:
  std::vector<std::string> removeInvalidParentheses(std::string s) {
    if(s.size() == 0) return std::vector<std::string>{s};

    std::vector<std::vector<std::string>> res;
    std::vector<size_t> left_idx, right_idx;
    
    size_t min_left = s.length(), max_right = 0;
    for(size_t i = 0; i < s.size(); ++i) {
      if(s[i] == '(') {
        left_idx.push_back(i);
      }
      if(s[i] == ')') {
        right_idx.push_back(i);
      }
      int n = (int)left_idx.size() - (int)right_idx.size();
      if(n < 0) {
        if(!left_idx.empty()) {
          std::vector<std::string> sub_strs;
          size_t last_right_idx=right_idx[0];
          /*n<0 인 시점은 항상 right - left == 1인 상황*/
          for(size_t j = 0; j < right_idx.size(); ++j) {
            std::string sub_str = s.substr(left_idx.front(),right_idx.back()-left_idx.front()+1);
            size_t cur_right_idx = right_idx[j];
            if(cur_right_idx-last_right_idx != 1) {
              sub_str.erase(sub_str.begin() + cur_right_idx - left_idx.front());
              sub_strs.push_back(sub_str);
            }
            last_right_idx = right_idx[j];
          }
          min_left = std::min(left_idx.front(),min_left);
          max_right = std::max(right_idx.back(),max_right);
          res.push_back(sub_strs);
          left_idx.clear();
        }
        right_idx.clear();
      }
    }

    
    if(!left_idx.empty() && !right_idx.empty()) {
      int offset = left_idx.front();
      std::string residue = s.substr(left_idx.front(),right_idx.back()-left_idx.front()+1);
      left_idx.clear();
      right_idx.clear();

      std::vector<std::vector<std::string>> additional_res;
      for(int i = residue.size()-1; i >= 0; --i) {        
        if(residue[i] == '(') {
          left_idx.push_back(i);
        } else if(residue[i] == ')') {
          right_idx.push_back(i);
        }
        int n = (int)right_idx.size() - (int)left_idx.size();
        if(n < 0) {
          if(!right_idx.empty()) {
            std::vector<std::string> sub_strs;
            size_t last_left_idx=left_idx[0];
            /*n<0 인 시점은 항상 left - right == 1인 상황*/
            for(size_t j = 0; j < left_idx.size(); ++j) {
              std::string sub_str = residue.substr(left_idx.back(),right_idx.front()-left_idx.back()+1);
              size_t cur_left_idx = left_idx[j];
              if(last_left_idx - cur_left_idx != 1) {
                sub_str.erase(sub_str.begin() + cur_left_idx - left_idx.back());
                sub_strs.push_back(sub_str);
              }
              last_left_idx = left_idx[j];
            }
            additional_res.push_back(sub_strs);
            min_left = std::min(offset+left_idx.back(),min_left);
            max_right = std::max(offset+right_idx.front(),max_right);
            right_idx.clear();
          }
          left_idx.clear();
        }
      }
      res.insert(res.end(),additional_res.rbegin(),additional_res.rend());
      if(!right_idx.empty() && !left_idx.empty()) {
        std::vector<std::string> sub_strs = {residue.substr(left_idx.back(),right_idx.front()-left_idx.back()+1)};
        min_left = std::min(offset+left_idx.back(),min_left);
        max_right = std::max(offset+right_idx.front(),max_right);
        res.push_back(sub_strs);
      }
    }   
    std::vector<std::string> ret;

    std::string add_left = "", add_right = "";
    if(min_left < max_right) {      
      for(size_t i = 0; i < min_left; ++i) {
        if(s[i] != '(' && s[i] != ')') {
         add_left.push_back(s[i]);
        }
      }
      for(size_t i = max_right; i < s.length(); ++i) {
        if(s[i] != '(' && s[i] != ')') {
         add_right.push_back(s[i]);
        }
      }
    }

    if(res.empty()) {
      std::string alphabets = "";
      for(const char a : s) {
        if(a != '(' && a != ')') {
          alphabets.push_back(a);
        }
      }
      ret.push_back(alphabets);
    } else {
      dfs(res,0,"",ret);
      for(auto& str : ret) {
        str = add_left + str + add_right;
      }
    }
    return ret;
  }

  void dfs(std::vector<std::vector<std::string>>& res, size_t level, std::string valid_str, std::vector<std::string>& ret) {
    if(level > res.size() - 1) {
      ret.push_back(valid_str);
      return;
    }
    for(size_t i = 0; i < res[level].size(); ++i) {
      std::string new_str = valid_str+res[level][i];
      dfs(res,level+1,new_str,ret);
    }
  }
};

