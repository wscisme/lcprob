#include <iostream>
#include <vector>

using namespace std;

vector<int*> all_permutes;

void findPermutation(int permute[], int j, int coltaken, int sums, int difs) {
  if (j == 8) {
    int* goodpermute = new int[8];
    for (int i = 0; i < 8; ++i) goodpermute[i] = permute[i];
    all_permutes.push_back(goodpermute);
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

  cout << "Total possibilities are: " << all_permutes.size() << endl;
  for (unsigned i = 0; i < 8; ++i) {
    cout << all_permutes[0][i] << " ";
  }
  cout << endl;

  return 0;
}
