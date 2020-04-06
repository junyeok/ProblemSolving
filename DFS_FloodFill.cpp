#include <vector>

class FloodFill {
public:
  std::vector<std::vector<int>> floodFill(std::vector<std::vector<int>>& image, int sr, int sc, int newColor) {
    int tgt = image[sr][sc];
    if(tgt != newColor) dfs(image,sr,sc,newColor,tgt);
    return image;
  }

  void dfs(std::vector<std::vector<int>>& image, int row, int col, int newColor, int tgt) {
    if(row < 0 || row >= image.size() || col < 0 || col >= image[0].size() || image[row][col] != tgt) return;
    image[row][col] = newColor;
    dfs(image,row-1,col,newColor,tgt);
    dfs(image,row+1,col,newColor,tgt);
    dfs(image,row,col-1,newColor,tgt);
    dfs(image,row,col+1,newColor,tgt);
  }
};
