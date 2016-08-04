#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

class Solution {
 public:
  void solveSudoku(vector<vector<char>>& board);
};

inline int blkpos(int i, int j) { return (i/3)*3 + (j/3); }

void Solution::solveSudoku(vector<vector<char>>& board) {

  const int ALLNUM = (1 << 9) - 1; // indicate the numbers that still possible

  int candrow[9];               // possible candidates for the row as binary pos
  int candcol[9];
  int candblk[9];
  int ncandrow[9];              // number of candidates for each row
  int ncandcol[9];
  int ncandblk[9];

  std::fill_n(candrow, 9, ALLNUM);
  std::fill_n(candcol, 9, ALLNUM);
  std::fill_n(candblk, 9, ALLNUM);

  vector<int*> emptycell;

  // scan the board to narrow down the candidates
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (board[i][j] == '.') {
        int* cell = new int[5];
        cell[0] = i;
        cell[1] = j;
        cell[2] = blkpos(i, j);
        emptycell.push_back(cell);
      } else {
        int thisnum = 1 << (board[i][j] - '0'); // binary rep for the number
        candrow[i] ^= thisnum;
        candcol[j] ^= thisnum;
        candblk[blkpos(i, j)] ^= thisnum;
      }
    }
  }

  for (auto it = emptycell.begin(); it != emptycell.end(); ++it) {
    (*it)[3] = candrow[(*it)[0]] & candcol[(*it)[1]] & candblk[(*it)[2]];
    (*it)[4] = (std::bitset<9>((*it)[3])).count();
  }

}



int main()
{
  vector<vector<char>> board;
  // board.push_back(vector<char>{'5','3',})
  int n = 6^3;

  cout << "There are " << (std::bitset<9>(n)).count() << " ones in number " << n << endl;


  return 0;
}
