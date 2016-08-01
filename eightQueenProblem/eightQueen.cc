#include <iostream>
#include <vector>

using namespace std;

vector<int*> all_permutes;

void findPermutation(int permute[], int j, int coltaken, int sums, int difs) {
  if (j == 8) {
    all_permutes.push_back(permute);
    return;
  }

  for (int k = 0; k < 8; ++k) {
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

  cout << all_permutes.size() << endl;

  return 0;
}
