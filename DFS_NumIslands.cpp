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
    std::priority_queue< Key, std::vector<Key>, std::function<bool(Key, Key)> > pq(KeyCompare);
    std::vector<std::vector<bool>> visited(grid.size(),std::vector<bool>(grid[0].size(),false));

    int ret = 0;

    pq.push( Key{0,0,false} );    
    while (!pq.empty()) {
      const auto top = pq.top();
      pq.pop();

      visited[top.row][top.col] = true;
      
      if(grid[top.row][top.col] == '1') {
        if (!top.continuing) {
          ret += 1;
        }
        if(top.row + 1 < grid.size() && !visited[top.row + 1][top.col]) {
          pq.push( Key{top.row + 1, top.col, true});
        }
        if(top.row - 1 >= 0 && !visited[top.row - 1][top.col]) {
          pq.push( Key{top.row - 1, top.col, true});
        }
        if(top.col + 1 < grid[0].size() && !visited[top.row][top.col + 1]) {
          pq.push( Key{top.row, top.col + 1, true});
        }
        if(top.col - 1 >= 0 && !visited[top.row][top.col - 1]) {
          pq.push( Key{top.row, top.col - 1, true});
        }
      } else {
        if(top.row + 1 < grid.size() && !visited[top.row + 1][top.col]) {
          pq.push( Key{top.row + 1, top.col, false});
          if(grid[top.row + 1][top.col] == '1') continue;
        }
        if(top.row - 1 >= 0 && !visited[top.row - 1][top.col]) {
          pq.push( Key{top.row - 1, top.col, false});
          if(grid[top.row - 1][top.col] == '1') continue;
        }
        if(top.col + 1 < grid[0].size() && !visited[top.row][top.col + 1]) {
          pq.push( Key{top.row, top.col + 1, false});
          if(grid[top.row][top.col + 1] == '1') continue;
        }
        if(top.col - 1 >= 0 && !visited[top.row][top.col - 1]) {
          pq.push( Key{top.row, top.col - 1, false});
          if(grid[top.row][top.col - 1] == '1') continue;
        }
      }
    }

    return ret;
  }
};