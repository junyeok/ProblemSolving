#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

class CheckInclusion
{
public:
  bool checkInclusion(std::string s1, std::string s2) {

    size_t s1_size = s1.size();
    size_t s2_size = s2.size();

    if(s1_size > s2_size) {
      return false;
    }
    
    std::array<int,26> s1_map = {0};
    std::array<int,26> s2_map = {0};

    for(size_t i = 0; i < s1_size; ++i) {
      s1_map[s1[i] - 'a']++;
      s2_map[s2[i] - 'a']++;
    }

    for(size_t i = 0; i < s2_size - s1_size; ++i) {
      if(s1_map == s2_map) {
        return true;
      }
      s2_map[s2[i] - 'a']--;
      s2_map[s2[s1_size + i] - 'a']++;
    }

    return s1_map == s2_map;
  }
};
