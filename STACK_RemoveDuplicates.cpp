#include <vector>
#include <stack>
#include <string>

class Remover {
public:
  std::string removeDuplicates(std::string S) {
    std::stack<char> save;
    size_t idx = 0;
    while(idx < S.size()) {
      if(save.empty()) {
        save.push(S[idx]);
        idx++;
        continue;
      }
      const auto& top = save.top();
      if(top == S[idx]) {
        save.pop();
        idx++;
      } else {
        save.push(S[idx]);
        idx++;
      }
    }

    std::string ret = "";
    ret.reserve(S.size());
    
    while(!save.empty()) {
      ret = save.top() + ret;
      save.pop();
    }
    return ret;
  }

  std::string removeDuplicates2(std::string S) {
    size_t idx = 0;
    std::string ret{};
    ret.reserve(S.size());

    while(idx < S.size()) {
      if(ret.size() == 0) {
        ret = S[idx];
        idx++;
        continue;
      }
      if(ret.back() == S[idx]) {
        ret.pop_back();
        idx++;
      } else {
        ret.push_back(S[idx]);
        idx++;
      }
    }
    return ret;
  }
};