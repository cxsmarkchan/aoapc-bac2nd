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
  int n;
  cin >> n;
  int num[n];
  for (int i = 0; i < n; ++i) {
    cin >> num[i];
  }

  int left[n], right[n];
  left[0] = 1;
  for (int i = 1; i < n; ++i) {
    if (num[i] > num[i - 1]) {
      left[i] = left[i - 1] + 1;
    } else {
      left[i] = 1;
    }
  }
  right[n - 1] = 1;
  for (int i = n - 2; i >= 0; --i) {
    if (num[i] < num[i + 1]) {
      right[i] = right[i + 1] + 1;
    } else {
      right[i] = 1;
    }
  }

  unsigned int min_left[n + 1];
  memset(min_left, -1, sizeof(min_left));
  min_left[0] = 0;

  int ret = 0;
  for (int i = 0; i < n; ++i) {
    int begin = 0, end = n + 1;
    while (end - begin > 1) {
      int mid = (begin + end) / 2;
      if (min_left[mid] < num[i]) begin = mid;
      else end = mid;
    }
    ret = max(ret, begin + right[i]);
    min_left[left[i]] = min(min_left[left[i]], (unsigned int)num[i]);
  }

  cout << ret << "\n";
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
