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
  string s;
  cin >> s;

  int N = s.size();

  bool is_palindrome[N][N];
  for (int k = 0; k < N; ++k) {
    int j;
    for (int i = 0; (j = (i + k)) < N; ++i) {
      if (j == i) is_palindrome[i][j] = true;
      else if (j == i + 1) is_palindrome[i][j] = (s[j] == s[i]);
      else is_palindrome[i][j] = (s[j] == s[i] && is_palindrome[i + 1][j - 1]);
    }
  }

  int dp[N + 1];
  dp[0] = 0;
  for (int i = 1; i <= N; ++i) {
    dp[i] = N + 1;
    for (int j = 0; j < i; ++j) {
      if (!is_palindrome[j][i - 1]) continue;
      dp[i] = min(dp[i], dp[j] + 1);
    }
  }

  cout << dp[N] << "\n";
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
