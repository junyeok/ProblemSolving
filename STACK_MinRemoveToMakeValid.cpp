#include <stack>
#include <string>
#include <algorithm>

class minRemover {
public:
  std::string minRemoveToMakeValid(std::string s) {
    int std = 0;
    std::stack<char> save;
    for(auto iter = s.begin(); iter != s.end(); ++iter) {
      const auto& c = *iter;
      if(c == '(') std++;
      if(c == ')') {
        if(std == 0) continue;
        std--;
      }
      save.push(c);
    }
    std::string ret{};
    while(!save.empty()) {
      auto& top = save.top();
      if(top == '(' && std > 0) {
        save.pop();
        std--;
        continue;
      } else if(top == ')' && std < 0) {
        save.pop();
        std++;
        continue;
      } else {
        ret.push_back(top);
        save.pop();
      }
    }
    if(ret.empty()) return ret;
    std::reverse(ret.begin(),ret.end());
    return ret;
  }
};