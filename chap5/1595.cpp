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

using namespace std;

struct Point {
  int x;
  int y;
};

bool solve() {
  int N;
  cin >> N;
  Point points[N];
  for (int i = 0; i < N; ++i) {
    cin >> points[i].x >> points[i].y;
  }
  sort(points, points + N, [](const Point& lhs, const Point& rhs) -> bool {
    return lhs.x < rhs.x;
  });
  int mid_plus_2 = (N & 1) ? points[N / 2].x * 2 : points[N / 2 - 1].x + points[N / 2].x;
  int left = (N & 1) ? N / 2 : N / 2 - 1, right = N / 2;
  while (left >= 0 && points[left].x * 2 == mid_plus_2) left--;
  while (right <= N - 1 && points[right].x * 2 == mid_plus_2) right++;

  if (left + 1 != N - right) return false;

  sort(points, points + left + 1, [](const Point& lhs, const Point& rhs) -> bool {
    if (lhs.x < rhs.x) return true;
    if (lhs.x > rhs.x) return false;
    return lhs.y < rhs.y;
  });

  sort(points + right, points + N, [](const Point& lhs, const Point& rhs) -> bool {
    if (lhs.x < rhs.x) return true;
    if (lhs.x > rhs.x) return false;
    return lhs.y > rhs.y;
  });

  for (int i = 0; i <= left; ++i) {
    int j = N - 1 - i;
    if (points[i].x + points[j].x != mid_plus_2
        || points[i].y != points[j].y)
      return false;
  }

  return true;
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    if (solve()) cout << "YES\n";
    else cout << "NO\n";
  }

  return 0;
}
