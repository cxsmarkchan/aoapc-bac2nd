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
const double eps = 1e-8;

struct QuickRead {
  QuickRead() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
  }
} quickread;

struct Point {
  double x;
  double y;
};

double distance(const Point& p1, const Point& p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void solve(int n) {
  Point points[n];
  for (int i = 0; i < n; ++i) {
    cin >> points[i].x >> points[i].y;
  }

  // dp[i][j]: i -> (i + 1 .. n - 2) -> n - 1 -> (i + 1 .. n - 2) -> j
  double dp[n][n];
  for (int j = n - 1; j >= 0; --j) {
    dp[n - 1][j] = distance(points[n - 1], points[j]);
  }
  for (int i = n - 2; i >= 0; --i) {
    for (int j = i - 1; j >= 0; --j) {
      dp[i][j] = distance(points[i], points[i + 1]) + dp[i + 1][j];
      double return_distance = distance(points[i + 1], points[j]);
      for (int k = i + 2; k < n; ++k) {
        dp[i][j] = min(dp[i][j], distance(points[i], points[k]) + dp[k][k - 1] + return_distance);
        return_distance += distance(points[k - 1], points[k]);
      }
    }
  }
  dp[0][0] = distance(points[0], points[1]) + dp[1][0];
  double return_distance = distance(points[1], points[0]);
  for (int k = 2; k < n; ++k) {
    dp[0][0] = min(dp[0][0], distance(points[0], points[k]) + dp[k][k - 1] + return_distance);
    return_distance += distance(points[k - 1], points[k]);
  }

  printf("%.2f\n", dp[0][0] + eps);
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n;
  while (cin >> n) {
    solve(n);
  }

  return 0;
}
