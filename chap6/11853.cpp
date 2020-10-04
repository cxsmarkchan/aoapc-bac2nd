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

const int UP_BORDER = 0;
const int BOTTOM_BORDER = 1;
const int BASE = 2;

double x[1006], y[1006], radius[1006];

bool overlap(int i, int j) {
  if (i == UP_BORDER) {
    return y[j] + radius[j] >= 1000;
  } else if (i == BOTTOM_BORDER) {
    return y[j] - radius[j] <= 0;
  } else {
    return (y[i] - y[j]) * (y[i] - y[j]) + (x[i] - x[j]) * (x[i] - x[j]) <= (radius[i] + radius[j]) * (radius[i] + radius[j]);
  }
}

bool update_overlap_left(int i, double *pos) {
  if (x[i] - radius[i] > 0) return false;
  double diff = sqrt(radius[i] * radius[i] - x[i] * x[i]);
  *pos = min(*pos, y[i] - diff);
  return true;
}

bool update_overlap_right(int i, double *pos) {
  if (x[i] + radius[i] < 1000) return false;
  double diff = sqrt(radius[i] * radius[i] - (1000 - x[i]) * (1000 - x[i]));
  *pos = min(*pos, y[i] - diff);
  return true;
}

void solve(int N) {
  vector<vector<int>> adj(N + 2, vector<int>());
  for (int i = 0; i < N; ++i) {
    cin >> x[BASE + i] >> y[BASE + i] >> radius[BASE + i];
    for (int j = 0; j < BASE + i; ++j) {
      if (overlap(j, BASE + i)) {
        adj[BASE + i].push_back(j);
        adj[j].push_back(BASE + i);
      }
    }
  }

  vector<bool> visited(N + 2, false);
  stack<int> st;
  st.push(UP_BORDER);
  double left = 1000.0, right = 1000.0;
  bool possible = true;
  while (!st.empty()) {
    int top = st.top();
    visited[top] = true;
    st.pop();
    if (top == BOTTOM_BORDER) {
      possible = false;
      break;
    }
    if (top != UP_BORDER) {
      update_overlap_left(top, &left);
      update_overlap_right(top, &right);
    }

    for (auto& v : adj[top]) {
      if (visited[v]) continue;
      st.push(v);
    }
  }

  if (!possible) printf("IMPOSSIBLE\n");
  else printf("%.2f %.2f %.2f %.2f\n", 0.0, left + eps, 1000.0, right + eps);
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int N;
  while (cin >> N) {
    solve(N);
  }

  return 0;
}
