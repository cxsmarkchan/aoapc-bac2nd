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


#define MAXN 1000005
int p[MAXN];
int s[MAXN];

int h_left[MAXN];
int h_right[MAXN];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }

  h_left[0] = s[0];
  for (int i = 1; i < n; ++i) {
    h_left[i] = min(max(h_left[i - 1], p[i]), s[i]);
  }
  h_right[n - 1] = s[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    h_right[i] = min(max(h_right[i + 1], p[i]), s[i]);
  }

  int area = 0;
  for (int i = 0; i < n; ++i) {
    int h = min(h_left[i], h_right[i]);
    area += max(h - p[i], 0);
  }

  cout << area << "\n";
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
