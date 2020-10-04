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

struct Value {
  int num_songs;
  int length;

  bool operator<(const Value& rhs) const {
    if (num_songs < rhs.num_songs) return true;
    if (num_songs > rhs.num_songs) return false;
    return length < rhs.length;
  }
};

void solve() {
  int n, T;
  cin >> n >> T;
  int time[n];
  for (int i = 0; i < n; ++i) cin >> time[i];

  Value dp[T];
  memset(dp, 0, sizeof(dp));

  for (int i = 0; i < n; ++i) {
    for (int t = T - 1; t >= 0; --t) {
      if (t >= time[i]) {
        dp[t] = max(dp[t], {dp[t - time[i]].num_songs + 1, dp[t - time[i]].length + time[i]});
      }
    }
  }

  cout << dp[T - 1].num_songs + 1 << " " << dp[T - 1].length + 678 << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cout << "Case " << t + 1 << ": ";
    solve();
  }

  return 0;
}
