#include <iostream>
#include <vector>

using namespace std;

vector<int*> all_permutes;
vector<int*> unique_permutes;

bool checkUnique(int permute[]) {
  int diffcount = 0;
  for (auto it = all_permutes.begin(); it != all_permutes.end(); ++it) {
    for (int i = 0; i < 8; ++i) {
      if ((*it)[i] != permute[i]) {
        ++diffcount;
        break;
      }
    }
  }

  if (diffcount == all_permutes.size()) {
    all_permutes.push_back(permute);
    return true;
  } else {
    delete [] permute;
    return false;
  }
}

void pushUnique(int permute[]) {

  bool is_unique = true;
  
  int* original = new int[8];
  int* lrparity = new int[8];
  int* udparity = new int[8];
  int* crotate1 = new int[8];
  int* crotate2 = new int[8];
  int* crotate3 = new int[8];
  int* rotnpar1 = new int[8];
  int* rotnpar2 = new int[8];

  for (int i = 0; i < 8; ++i) {
    original[i] = permute[i];
    lrparity[i] = 7 - permute[i];
    udparity[7-i] = permute[i];
    crotate1[7-permute[i]] = i;
    crotate2[7-i] = 7 - permute[i];
    crotate3[permute[i]] = 7 - i;
    rotnpar1[7-permute[i]] = 7 - i;
    rotnpar2[permute[i]] = i;
  }
  if (checkUnique(original) &&
      checkUnique(lrparity) &&
      checkUnique(udparity) &&
      checkUnique(crotate1) &&
      checkUnique(crotate2) &&
      checkUnique(crotate3) &&
      checkUnique(rotnpar1) &&
      checkUnique(rotnpar2)) {
    unique_permutes.push_back(original);
  }
}

void findPermutation(int permute[], int j, int coltaken, int sums, int difs) {
  if (j == 8) {
    pushUnique(permute);

    return;
  }

  for (int k = 0; k < 9; ++k) {
    if (k == 8) return;
    if (coltaken & 1 << k) continue;
    if (sums & 1 << j << k) continue;
    if (difs & 1 << 7 << j >> k) continue;

    int coltaken_new = coltaken | 1 << k;
    int sums_new = sums | 1 << j << k;
    int difs_new = difs | 1 << 7 << j >> k;
    permute[j] = k;
    findPermutation(permute, j+1, coltaken_new, sums_new, difs_new);
  }
}

int main()
{
  int permute[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  int coltaken{0};
  int sums{0};
  int difs{0};

  findPermutation(permute, 0, coltaken, sums, difs);

  cout << "Total possibilities are: " << unique_permutes.size() << endl;
  for (unsigned i = 0; i < 8; ++i) {
    cout << unique_permutes[0][i] << " ";
  }
  cout << endl;

  return 0;
}
