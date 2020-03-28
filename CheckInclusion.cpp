#include <iostream>
#include <vector>
#include <algorithm>

class CheckInclusion
{
public:
  bool checkInclusion(std::string s1, std::string s2)
  {
    int start = s2.find(s1[0],0);
    size_t s1_size = s1.size();
    size_t s2_size = s2.size();

    if(s1_size > s2_size) {
      return false;
    }
    
    if(start == std::string::npos) {
      return false;
    } else {
      start = std::max(0,start - (int)s1_size + 1);
    }

    std::sort(s1.begin(),s1.end());

    for(size_t i = 0; i < s2_size - s1_size + 1; ++i) {
      std::string sub_str2 = s2.substr(i,s1_size);
      std::sort(sub_str2.begin(),sub_str2.end());
      if(s1 == sub_str2) {
        return true;
      }
    }

    return false;
  }
};
