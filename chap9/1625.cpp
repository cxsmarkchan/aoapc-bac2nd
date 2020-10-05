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

void solve() {
  string s1, s2;
  cin >> s1 >> s2;
  int N = s1.size();
  int M = s2.size();

  int min1[26], max1[26], min2[26], max2[26];
  memset(min1, -1, sizeof(min1));
  memset(min2, -1, sizeof(min2));
  memset(max1, -1, sizeof(max1));
  memset(max2, -1, sizeof(max2));

  for (int i = 0; i < N; ++i) {
    int c = s1[i] - 'A';
    if (min1[c] == -1) min1[c] = i + 1;
    max1[c] = i + 1;
  }
  for (int i = 0; i < M; ++i) {
    int c = s2[i] - 'A';
    if (min2[c] == -1) min2[c] = i + 1;
    max2[c] = i + 1;
  }

  int dp[N + 1][M + 1];
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j <= M; ++j) {
      if (i == 0 && j == 0) {
        dp[i][j] = 0;
        continue;
      }
      dp[i][j] = 100000000;
      if (i > 0) {
        int result1 = dp[i - 1][j];
        int c1 = s1[i - 1] - 'A';
        if (min1[c1] == i && (min2[c1] == -1 || min2[c1] > j)) result1 -= (i + j);
        if (max1[c1] == i && (max2[c1] == -1 || max2[c1] <= j)) result1 += (i + j);
        dp[i][j] = min(dp[i][j], result1);
      }
      if (j > 0) {
        int result2 = dp[i][j - 1];
        int c2 = s2[j - 1] - 'A';
        if (min2[c2] == j && (min1[c2] == -1 || min1[c2] > i)) result2 -= (i + j);
        if (max2[c2] == j && (max1[c2] == -1 || max1[c2] <= i)) result2 += (i + j);
        dp[i][j] = min(dp[i][j], result2);
      }
    }
  }

  cout << dp[N][M] << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
