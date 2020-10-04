#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;
typedef long long ll;

struct QuickRead {
  QuickRead() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
  }
} quickread;

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    int D, I;
    cin >> D >> I;
    I--;
    int num = 1;
    for (int i = 1; i < D; ++i) {
      num = (num << 1) + (I & 1);
      I >>= 1;
    }
    cout << num << "\n";
  }

  return 0;
}
