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

using namespace std;

struct QuickRead {
  QuickRead() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
  }
} quickread;

void solve(int N, int M) {
  vector<vector<pair<int, int>>> adj(N, vector<pair<int, int>>());
  for (int i = 0; i < M; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    adj[x - 1].push_back({y - 1, z});
    adj[y - 1].push_back({x - 1, z});
  }

  vector<int> parent(N, -2);
  vector<int> parent_color(N, 0);
  queue<vector<int>> q;
  parent[0] = -1;
  q.push({0});

  while (!q.empty()) {
    auto top = q.front();
    q.pop();

    unordered_map<int, pair<int, int>> next;
    for (auto& u : top) {
      if (u == N - 1) {
        next.clear();
        break;
      }
      for (auto& v : adj[u]) {
        if (parent[v.first] != -2) continue;
        if (next.find(v.first) == next.end() || next[v.first].second > v.second) {
          next[v.first] = {u, v.second};
        }
      }
    }
    if (next.empty()) continue;

    vector<pair<int, pair<int, int>>> vec(next.begin(), next.end());
    sort(vec.begin(), vec.end(), [](const pair<int, pair<int, int>>& lhs, const pair<int, pair<int, int>>& rhs) -> bool {
        return lhs.second.second < rhs.second.second;
    });

    int current_color = vec[0].second.second;
    vector<int> next_queue;
    for (auto& item : vec) {
      parent[item.first] = item.second.first;
      parent_color[item.first] = item.second.second;
      if (item.second.second == current_color) {
        next_queue.push_back(item.first);
      } else {
        q.push(next_queue);
        current_color = item.second.second;
        next_queue = {item.first};
      }
    }
    if (!next_queue.empty()) q.push(next_queue);
  }

  stack<int> final_colors;
  int node = N - 1;
  while (node != 0) {
    final_colors.push(parent_color[node]);
    node = parent[node];
  }

  cout << final_colors.size() << "\n";
  while (!final_colors.empty()) {
    cout << final_colors.top();
    final_colors.pop();
    if (!final_colors.empty()) cout << " ";
  }
  cout << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n, m;
  while (cin >> n >> m) {
    solve(n, m);
  }

  return 0;
}
