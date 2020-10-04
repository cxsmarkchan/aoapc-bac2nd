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

int a_plus_b[16000000];

int find_num(int k, int target) {
  int begin = -1, end = k;
  while (end - begin > 1) {
    int mid = (begin + end) / 2;
    if (a_plus_b[mid] < target) begin = mid;
    else end = mid;
  }
  int first_larger_or_equal = end;

  begin = -1, end = k;
  while (end - begin > 1) {
    int mid = (begin + end) / 2;
    if (a_plus_b[mid] <= target) begin = mid;
    else end = mid;
  }
  int last_less_or_equal = begin;
  if (first_larger_or_equal > last_less_or_equal) return 0;
  return last_less_or_equal - first_larger_or_equal + 1;
}

void solve() {
  int n;
  cin >> n;

  int a[n], b[n], c[n], d[n];

  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> b[i] >> c[i] >> d[i];
  }

  int k = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a_plus_b[k++] = a[i] + b[j];
    }
  }

  sort(a_plus_b, a_plus_b + k);

  int num = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      num += find_num(k, -c[i] - d[j]);
    }
  }
  cout << num << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    solve();
    if (T > 0) cout << "\n";
  }

  return 0;
}
