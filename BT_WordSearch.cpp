#include <vector>
#include <string>

/**
 * board의 특정 위치에서 상/하/좌/우로만 이동가능할 때 반복 이동해서 word에 있는 모든 문자를 찾을 수 있는지에 대한 문제.
 * Backtracking으로 풀이함
 * 1. board[cur_row][cur_col]이 word의 알바벳과 같으면 dfs로 계속 탐색함. 이 때 재탐색되는 것을 방지하기 위해 null character로 해당 위치의 문자를 바꿔줌
 * 2. 만약 해당 위치의 모든 다음 스텝의 단어가 다르다면 board의 문자를 다시 원상태로 바꿔준다. 
 * 
 */
class SearchWord {
 public:
  bool exist(std::vector<std::vector<char>>& board, std::string word) {
    m = board.size();
    n = board[0].size();
    word_size = word.size();
    if(m * n < word_size) return false;    
    for(size_t i = 0; i < m; ++i) {
      for(size_t j = 0; j < n; ++j) {
        if(dfs(board, word.c_str(),i,j)) return true;
      }
    }
    return false;
  }

 private:
  bool dfs(std::vector<std::vector<char>>& board, const char* word, int cur_row, int cur_col) {
    if(cur_row < 0 || cur_col < 0 || cur_row >= m || cur_col >= n || board[cur_row][cur_col] != *word ) return false;
    
    char temp = *word;
    board[cur_row][cur_col] = '\0';
    if(*(word+1) == '\0') return true;
    
    if(( dfs(board,word+1,cur_row-1,cur_col) ) || 
       ( dfs(board,word+1,cur_row+1,cur_col) ) || 
       ( dfs(board,word+1,cur_row,cur_col-1) ) || 
       ( dfs(board,word+1,cur_row,cur_col+1) ) ){
      return true;
    } 

    board[cur_row][cur_col] = temp;
    return false;
  }

  int m,n,word_size;
};

/**
 * 1과 유사하게 접근하였으나 같은 문자를 checking할 때 visited vector를 활용하였는데, time limit exceeded.
 * 왜 탐색 속도에서 차이가 있는지 모르겠다.
 */
class SearchWord2 {
public:
  bool exist(std::vector<std::vector<char>>& board, std::string word) {
    m = board.size();
    n = board[0].size();
    word_size = word.size();
    if(m * n < word_size) return false;
    
    _board = board;
    _word = word;
    
    for(size_t i = 0; i < m; ++i) {
      for(size_t j = 0; j < n; ++j) {
        std::vector<std::vector<bool>> visited(m,std::vector<bool>(n,false));
        if(dfs(visited,0,i,j)) return true;
      }
    }
    return false;
  }

  bool dfs(std::vector<std::vector<bool>>& visited, int cur_idx, int cur_row, int cur_col) {
    if(cur_row < 0 || cur_col < 0 || cur_row >= m || cur_col >= n || visited[cur_row][cur_col] || _board[cur_row][cur_col] != _word[cur_idx] ) return false;
    
    visited[cur_row][cur_col] = true;
    if(cur_idx == word_size - 1) return true;
    
    if(( dfs(visited,cur_idx+1,cur_row-1,cur_col) ) || 
       ( dfs(visited,cur_idx+1,cur_row+1,cur_col) ) || 
       ( dfs(visited,cur_idx+1,cur_row,cur_col-1) ) || 
       ( dfs(visited,cur_idx+1,cur_row,cur_col+1) ) ){
      return true;
    } 

    visited[cur_row][cur_col] = false;
    return false;
  }

  std::vector<std::vector<char>> _board;
  std::string _word;
  int m,n,word_size;
};