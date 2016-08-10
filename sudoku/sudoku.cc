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
  vector<int*> poped_at_trial;

  // scan the board to narrow down the candidates
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (board[i][j] == '.') {
        int* cell = new int[5];
        cell[0] = i;
        cell[1] = j;
        cell[2] = blkpos(i, j);
        emptycells.push_back(cell);
      } else {
        int thisnum = 1 << (board[i][j] - '0'); // binary rep for the number
        candrow[i] ^= thisnum;
        candcol[j] ^= thisnum;
        candblk[blkpos(i, j)] ^= thisnum;
      }
    }
  }

  bool under_trial = false;
  do {
    for (auto it = emptycells.begin(); it != emptycells.end(); ++it) {
      (*it)[3] = candrow[(*it)[0]] & candcol[(*it)[1]] & candblk[(*it)[2]];
      (*it)[4] = (std::bitset<10>((*it)[3])).count();
    }
    std::sort(emptycells.begin(), emptycells.end(), sortByCount);
    // cout << "A sorting is done." << endl;

    bool update_cells = false;
    for (auto it = emptycells.begin(); it != emptycells.end(); ++it) {
      // cout << "At " << (*it)[0] << " " << (*it)[1] << " with (*it)[4] = " << (*it)[4] << endl;
      if ((*it)[4] == 1) {
        update_cells = true;
        int num = 1;
        while (!((*it)[3] & (1 << num))) ++num;
        board[(*it)[0]][(*it)[1]] = num + '0';
        if (!(candrow[(*it)[0]] & (*it)[3]) ||
            !(candcol[(*it)[1]] & (*it)[3]) ||
            !(candblk[(*it)[2]] & (*it)[3])) break;
        candrow[(*it)[0]] ^= (*it)[3];
        candcol[(*it)[1]] ^= (*it)[3];
        candblk[(*it)[2]] ^= (*it)[3];
        if (under_trial) poped_at_trial.push_back(*it);
        emptycells.erase(it--);
      }
      else if ((*it)[4] == 0) {
        for (auto rit = poped_at_trial.rbegin(); rit != poped_at_trial.rend(); ) {
          if ((*rit)[4] == 1) {
            candrow[(*rit)[0]] ^= (*rit)[3];
            candcol[(*rit)[1]] ^= (*rit)[3];
            candblk[(*rit)[2]] ^= (*rit)[3];
            emptycells.insert(emptycells.begin(), (*rit));
            poped_at_trial.pop_back();
            rit = poped_at_trial.rbegin();
            continue;
          } else {
            candrow[(*rit)[0]] ^= (*rit)[4];
            candcol[(*rit)[1]] ^= (*rit)[4];
            candblk[(*rit)[2]] ^= (*rit)[4];
            int num = 1;
            while (!((*rit)[3] & (1 << num))) ++num;
            board[(*rit)[0]][(*rit)[1]] = num + '0'; // take the first available for trial
            (*rit)[4] = (1 << num);                  // use the count to store testing number
            candrow[(*rit)[0]] ^= (*rit)[4];
            candcol[(*rit)[1]] ^= (*rit)[4];
            candblk[(*rit)[2]] ^= (*rit)[4];
            (*rit)[4] = (std::bitset<10>((*rit)[3])).count();
            if ((*rit)[4] > 1) {
              (*rit)[3] ^= (*rit)[4];
              (*rit)[4] = 1 << num;
            }
            break;
          }
        }
        if (poped_at_trial.size() == 0) under_trial = false;
        break;
      }
      else if (update_cells) {
        // cout << "Updating cells!\n";
        break;
      }
      else {
        under_trial = true;
        int num = 1;
        while (!((*it)[3] & (1 << num))) ++num;
        board[(*it)[0]][(*it)[1]] = num + '0'; // take the first available for trial
        (*it)[4] = (1 << num);                 // use the count to store testing number
        candrow[(*it)[0]] ^= (*it)[4];
        candcol[(*it)[1]] ^= (*it)[4];
        candblk[(*it)[2]] ^= (*it)[4];
        (*it)[3] ^= (*it)[4];                  // take out the possiblity for next time
        poped_at_trial.push_back(*it);
        emptycells.erase(it);
        // cout << "Updating cells!\n";
        break;
      }
    }
  } while (emptycells.size() > 0);

}


int main()
{
  vector<vector<char>> board1;
  board1.push_back(vector<char>{'5','3','.', '.','7','.', '.','.','.'});
  board1.push_back(vector<char>{'6','.','.', '1','9','5', '.','.','.'});
  board1.push_back(vector<char>{'.','9','8', '.','.','.', '.','6','.'});

  board1.push_back(vector<char>{'8','.','.', '.','6','.', '.','.','3'});
  board1.push_back(vector<char>{'4','.','.', '8','.','3', '.','.','1'});
  board1.push_back(vector<char>{'7','.','.', '.','2','.', '.','.','6'});

  board1.push_back(vector<char>{'.','6','.', '.','.','.', '2','8','.'});
  board1.push_back(vector<char>{'.','.','.', '4','1','9', '.','.','5'});
  board1.push_back(vector<char>{'.','.','.', '.','8','.', '.','7','9'});

  vector<vector<char>> board2;
  board2.push_back(vector<char>{'.','.','9', '7','4','8', '.','.','.'});
  board2.push_back(vector<char>{'7','.','.', '.','.','.', '.','.','.'});
  board2.push_back(vector<char>{'.','2','.', '1','.','9', '.','.','.'});

  board2.push_back(vector<char>{'.','.','7', '.','.','.', '2','4','.'});
  board2.push_back(vector<char>{'.','6','4', '.','1','.', '5','9','.'});
  board2.push_back(vector<char>{'.','9','8', '.','.','.', '3','.','.'});

  board2.push_back(vector<char>{'.','.','.', '8','.','3', '.','2','.'});
  board2.push_back(vector<char>{'.','.','.', '.','.','.', '.','.','6'});
  board2.push_back(vector<char>{'.','.','.', '2','7','5', '9','.','.'});

  vector<vector<char>> board3;
  board3.push_back(vector<char>{'.','.','.', '2','.','.', '.','6','3'});
  board3.push_back(vector<char>{'3','.','.', '.','.','5', '4','.','1'});
  board3.push_back(vector<char>{'.','.','1', '.','.','3', '9','8','.'});
  board3.push_back(vector<char>{'.','.','.', '.','.','.', '.','9','.'});
  board3.push_back(vector<char>{'.','.','.', '5','3','8', '.','.','.'});
  board3.push_back(vector<char>{'.','3','.', '.','.','.', '.','.','.'});
  board3.push_back(vector<char>{'.','2','6', '3','.','.', '5','.','.'});
  board3.push_back(vector<char>{'5','.','3', '7','.','.', '.','.','8'});
  board3.push_back(vector<char>{'4','7','.', '.','.','1', '.','.','.'});

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
  cout << "This works: " << (n <<= 1) << endl;
  cout << "This works again: " << (n <<= 1) << endl;

  cout << "This works: " << cellbyrow[0].size() << " " << cellbyrow[1].size() << endl;

  for (auto it = cellbyrow[1].begin(); it != cellbyrow[1].end(); ++it) {
    cout << "This also works: " << (*it)[0] << endl;
    cellbyrow[1].erase(it--);
    // it = cellbyrow[1].begin();
  }
  cout << "This works: " << cellbyrow[0].size() << " " << cellbyrow[1].size() << endl << endl;
  
  Solution sol;

  cout << "The solution for board 1 is: " << endl;
  sol.solveSudoku(board1);
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j)
      cout << board1[i][j] << ' ';
    cout << endl;
  }

  cout << "The solution for board 2 is: " << endl;
  sol.solveSudoku(board2);
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j)
      cout << board2[i][j] << ' ';
    cout << endl;
  }

  cout << "The solution for board 3 is: " << endl;
  sol.solveSudoku(board3);
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j)
      cout << board3[i][j] << ' ';
    cout << endl;
  }

  return 0;
}
