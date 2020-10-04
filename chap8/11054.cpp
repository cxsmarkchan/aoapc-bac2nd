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
#include <cmath>

using namespace std;

struct QuickRead {
  QuickRead() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
  }
} quickread;

void solve(int n) {
  long long current_buy = 0;
  long long work = 0;

  for (int i = 0; i < n; ++i) {
    long long buy;
    cin >> buy;

    current_buy += buy;
    work += abs(current_buy);
  }

  cout << work << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n;
  while (cin >> n, n > 0) {
    solve(n);
  }

  return 0;
}
