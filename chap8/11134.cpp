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

struct Interval {
  int id;
  int left;
  int right;
  int pos;
};

bool solve(int n, const int* left, const int* right, int* pos) {
  Interval intervals[n];
  for (int i = 0; i < n; ++i) {
    intervals[i].id = i;
    intervals[i].left = left[i];
    intervals[i].right = right[i];
  }

  sort(intervals, intervals + n, [](const Interval& lhs, const Interval& rhs) -> bool {
      return lhs.left < rhs.left;
  });

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

  int k = 0;
  for (int i = 0; i < n; ++i) {
    while (k < n && intervals[k].left <= i + 1) {
      pq.push({intervals[k].right, k});
      k++;
    }
    if (pq.empty()) return false;

    auto top = pq.top();
    pq.pop();
    if (top.first < i + 1) return false;
    intervals[top.second].pos = i + 1;
  }

  sort(intervals, intervals + n, [](const Interval& lhs, const Interval& rhs) -> bool {
      return lhs.id < rhs.id;
  });

  for (int i = 0; i < n; ++i) {
    pos[i] = intervals[i].pos;
  }

  return true;
}

bool solve(int n) {
  int xl[n], yl[n], xr[n], yr[n];
  for (int i = 0; i < n; ++i) {
    cin >> xl[i] >> yl[i] >> xr[i] >> yr[i];
  }

  int x[n], y[n];
  if (!solve(n, xl, xr, x)) return false;
  if (!solve(n, yl, yr, y)) return false;

  for (int i = 0; i < n; ++i) {
    cout << x[i] << " " << y[i] << "\n";
  }
  return true;
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n;
  while (cin >> n, n > 0) {
    if (!solve(n)) cout << "IMPOSSIBLE\n";
  }

  return 0;
}
