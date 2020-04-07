#include <vector>
#include <queue>
#include <functional>


class NumIslands {
 public:

  struct Key {
    Key(int r, int c, bool con) : row(r), col(c), continuing(con) { }
    int row;
    int col;
    bool continuing;
  };


  int numIslands(std::vector<std::vector<char>>& grid) {
    if(grid.size() == 0) return 0; 
    auto KeyCompare = [&grid](const Key& lh, const Key& rh) {
      return grid[lh.row][lh.col] < grid[rh.row][rh.col];
    };

    std::priority_queue<Key,std::vector<Key>,std::function<bool(Key, Key)>> pq(KeyCompare);
    std::vector<std::vector<bool>> visited(grid.size(),std::vector<bool>(grid[0].size(),false));

    pq.push( Key{0,0,false} );

    int ret = 0;
    while (!pq.empty()) {
      const auto top = pq.top();
      pq.pop();
      
      if(visited[top.row][top.col]) continue;
      
      visited[top.row][top.col] = true;
      
      bool to_continue = false;
      if(grid[top.row][top.col] == '1') {
        if (!top.continuing) {
          ret += 1;
        }
        to_continue = true;
      }

      if(top.row + 1 < grid.size()) {
        pq.push( Key{top.row + 1, top.col, to_continue});
      }
      if(top.row - 1 >= 0) {
        pq.push( Key{top.row - 1, top.col, to_continue});
      }
      if(top.col + 1 < grid[0].size()) {
        pq.push( Key{top.row, top.col + 1, to_continue});
      }
      if(top.col - 1 >= 0) {
        pq.push( Key{top.row, top.col - 1, to_continue});
      }
    }

    return ret;
  }
};