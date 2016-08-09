#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

class Solution {
 public:
  void solveSudoku(vector<vector<char>>& board);
};

inline int blkpos(int i, int j) { return (i/3)*3 + (j/3); }
inline bool sortByCount(int* a, int* b) { return a[4] < b[4]; }

void Solution::solveSudoku(vector<vector<char>>& board) {

  const int ALLNUM = (1 << 10) - 2; // indicate the numbers that still possible

  int candrow[9];               // possible candidates for the row as binary pos
  int candcol[9];
  int candblk[9];
  int ncandrow[9];              // number of candidates for each row
  int ncandcol[9];
  int ncandblk[9];

  std::fill_n(candrow, 9, ALLNUM);
  std::fill_n(candcol, 9, ALLNUM);
  std::fill_n(candblk, 9, ALLNUM);

  vector<int*> emptycells;
  // vector<int*> cellcandbyrow[9];
  // vector<int*> cellcandbycol[9];

  // scan the board to narrow down the candidates
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (board[i][j] == '.') {
        int* cell = new int[5];
        cell[0] = i;
        cell[1] = j;
        cell[2] = blkpos(i, j);
        emptycells.push_back(cell);
        // cellcandbyrow[i].push_back(cell + 3);
        // cellcandbycol[j].push_back(cell + 3);
      } else {
        int thisnum = 1 << (board[i][j] - '0'); // binary rep for the number
        candrow[i] ^= thisnum;
        candcol[j] ^= thisnum;
        candblk[blkpos(i, j)] ^= thisnum;
      }
    }
  }

  bool update_cells = false;
  do {
    for (auto it = emptycells.begin(); it != emptycells.end(); ++it) {
      (*it)[3] = candrow[(*it)[0]] & candcol[(*it)[1]] & candblk[(*it)[2]];
      (*it)[4] = (std::bitset<11>((*it)[3])).count();
    }
    std::sort(emptycells.begin(), emptycells.end(), sortByCount);
    // cout << "A sorting is done." << endl;

    update_cells = false;
    for (auto it = emptycells.begin(); it != emptycells.end(); ++it) {
      // cout << "At " << (*it)[0] << " " << (*it)[1] << " with (*it)[4] = " << (*it)[4] << endl;
      if ((*it)[4] == 1) {
        update_cells = true;
        int num = 1;
        while (!((*it)[3] & (1 << num))) ++num;
        board[(*it)[0]][(*it)[1]] = num + '0';
        candrow[(*it)[0]] ^= (*it)[3];
        candcol[(*it)[1]] ^= (*it)[3];
        candblk[(*it)[2]] ^= (*it)[3];
        delete [] (*it);
        emptycells.erase(it--);
      } else {
        // cout << "A break is called!\n";
        break;
      }
    }
  } while (update_cells);

}


int main()
{
  vector<vector<char>> board;
  board.push_back(vector<char>{'5','3','.', '.','7','.', '.','.','.'});
  board.push_back(vector<char>{'6','.','.', '1','9','5', '.','.','.'});
  board.push_back(vector<char>{'.','9','8', '.','.','.', '.','6','.'});

  board.push_back(vector<char>{'8','.','.', '.','6','.', '.','.','3'});
  board.push_back(vector<char>{'4','.','.', '8','.','3', '.','.','1'});
  board.push_back(vector<char>{'7','.','.', '.','2','.', '.','.','6'});

  board.push_back(vector<char>{'.','6','.', '.','.','.', '2','8','.'});
  board.push_back(vector<char>{'.','.','.', '4','1','9', '.','.','5'});
  board.push_back(vector<char>{'.','.','.', '.','8','.', '.','7','9'});

  int n = 6^3;
  int* a = new int[9];
  int* b = new int[9];
  int* c = new int[9];
  vector<int*> cellbyrow[9];
  cellbyrow[2].push_back(&n);

  a[0] = 1;
  b[0] = 2;
  c[0] = 3;

  cellbyrow[1].push_back(a);
  cellbyrow[1].push_back(b);
  cellbyrow[1].push_back(c);

  cout << "There are " << (std::bitset<9>(n)).count() << " ones in number " << n << endl;
  cout << "This works: " << cellbyrow[0].size() << " " << cellbyrow[1].size() << endl;

  for (auto it = cellbyrow[1].begin(); it != cellbyrow[1].end(); ++it) {
    cout << "This also works: " << (*it)[0] << endl;
    cellbyrow[1].erase(it--);
    // it = cellbyrow[1].begin();
  }
  cout << "This works: " << cellbyrow[0].size() << " " << cellbyrow[1].size() << endl << endl;
  
  Solution sol;
  sol.solveSudoku(board);

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j)
      cout << board[i][j] << ' ';
    cout << endl;
  }

  return 0;
}
