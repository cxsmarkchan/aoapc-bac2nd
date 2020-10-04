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

bool solve(int* left, int* right, int lo, int hi) {
  if (lo >= hi) return true;

  int l = lo, h = hi;
  bool flag = true;
  while (l <= h) {
    if (flag) {
      if (left[l] < lo && right[l] > hi) {
        if (!solve(left, right, lo, l - 1)) return false;
        if (!solve(left, right, l + 1, hi)) return false;
        return true;
      } else l++;
    } else {
      if (left[h] < lo && right[h] > hi) {
        if (!solve(left, right, lo, h - 1)) return false;
        if (!solve(left, right, h + 1, hi)) return false;
        return true;
      } else h--;
    }
    flag = !flag;
  }

  return false;
}


bool solve() {
  int n;
  cin >> n;
  int num[n];
  int left[n];
  int right[n];
  for (int i = 0; i < n; ++i) {
    cin >> num[i];
  }

  unordered_map<int, int> last_pos;
  for (int i = 0; i < n; ++i) {
    auto it = last_pos.find(num[i]);
    if (it == last_pos.end()) left[i] = -1;
    else left[i] = it->second;
    last_pos[num[i]] = i;
  }
  last_pos.clear();
  for (int i = n - 1; i >= 0; --i) {
    auto it = last_pos.find(num[i]);
    if (it == last_pos.end()) right[i] = n;
    else right[i] = it->second;
    last_pos[num[i]] = i;
  }

  return solve(left, right, 0, n - 1);
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    if (solve()) cout << "non-boring\n";
    else cout << "boring\n";
  }

  return 0;
}
