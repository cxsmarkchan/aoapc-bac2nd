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

struct QuickRead {
  QuickRead() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
  }
} quickread;

bool solve(int* W = nullptr) {
  int Wl, Dl, Wr, Dr;
  cin >> Wl >> Dl >> Wr >> Dr;
  bool ret = true;
  if (Wl == 0) {
    ret = solve(&Wl) && ret;
  }
  if (Wr == 0) {
    ret = solve(&Wr) && ret;
  }
  if (W != nullptr) {
    *W = Wl + Wr;
  }

  return ret && (Wl * Dl == Wr * Dr);
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    if (solve()) cout << "YES\n";
    else cout << "NO\n";
    if (T > 0) cout << "\n";
  }

  return 0;
}
