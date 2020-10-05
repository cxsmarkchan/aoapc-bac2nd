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

struct Lamp {
  int V;
  int K;
  int C;
  int L;
};

long long prices[1024];

void initialize() {
  prices[0] = 100000000;
  for (int i = 0; i < 10; ++i) {
    prices[1 << i] = i + 1;
  }
  for (int i = 0; i < 1024; ++i) {
    prices[i] = prices[i & (-i)];
  }
}

void solve(int n) {
  Lamp lamps[n];
  for (int i = 0; i < n; ++i) {
    cin >> lamps[i].V >> lamps[i].K >> lamps[i].C >> lamps[i].L;
  }

  sort(lamps, lamps + n, [](const Lamp& lhs, const Lamp& rhs) -> bool {
    return lhs.V > rhs.V;
  });

  int mask = 1 << 10;
  long long dp[mask];
  for (int i = 0; i < mask; ++i) dp[i] = 100000000;
  dp[0] = 0;

  for (int i = 0; i < n; ++i) {
    // cout << lamps[i].V << " " << lamps[i].K << " " << lamps[i].C << " " << lamps[i].L << endl;
    int cur_mask = 1 << (lamps[i].C - 1);
    for (int k = mask - 1; k >= 0; --k) {
      if (k & cur_mask) {
        dp[k] = min(dp[k] + prices[k] * lamps[i].L, dp[k ^ cur_mask] + lamps[i].C * lamps[i].L + lamps[i].K);
      } else {
        dp[k] += prices[k] * lamps[i].L;
      }
    }
  }

  for (int i = 0; i < 10; ++i) {
    cout << i << " " << dp[1 << i] << endl;
  }

  long long ret = dp[1];
  for (int i = 1; i < mask; ++i) {
    ret = min(ret, dp[i]);
  }

  cout << ret << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  initialize();

  int n;
  while (cin >> n, n > 0) {
    solve(n);
  }

  return 0;
}
