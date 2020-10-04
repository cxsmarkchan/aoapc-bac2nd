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

struct MultiSet {
  map<int, int> map_;

  void insert(int i) {
    auto it = map_.find(i);
    if (it == map_.end()) {
      map_[i] = 1;
    } else {
      it->second++;
    }
  }

  void erase_all(int i) {
    map_.erase(i);
  }

  void erase(int i) {
    auto it = map_.find(i);
    if (it == map_.end()) return;
    it->second--;
    if (it->second == 0)
      map_.erase(it);
  }
};

void solve() {
  int N, M;
  cin >> N >> M;

  string s[N];
  for (int i = 0; i < N; ++i) {
    cin >> s[i];
  }

  int sup[M];
  for (int j = 0; j < M; ++j) sup[j] = -1;

  MultiSet result;

  for (int i = 0; i < N; ++i) {
    MultiSet eq_borders;
    vector<pair<int, int>> borders;
    for (int j = 0; j < M; ++j) {
      if (s[i][j] == '#') {
        sup[j] = i;
        borders.clear();
      } else {
        borders.push_back({sup[j], j});
        while (borders.size() >= 2) {
          auto& p2 = borders[borders.size() - 2];
          auto& p1 = borders[borders.size() - 1];
          if (p2.first < p1.first) p2.first = p1.first;
          if (p2.first + p2.second >= p1.first + p1.second) break;
          borders.pop_back();
        }
        auto& back = borders.back();
        result.insert(2 * (i + j - (back.first + back.second) + 1));
      }
    }
  }

  for (auto& item : result.map_) {
    cout << item.second << " x " << item.first << "\n";
  }
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
