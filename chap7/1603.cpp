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

struct Square {
  bool state;
  int size;
};

const int UNVISITED = 0;
const int DELETED = 1;
const int VISITED = 2;

struct Side {
  int state;
  int ids[60];
  int num_squares;

  Side() : state(UNVISITED), num_squares(0) { memset(ids, 0, sizeof(ids)); }

  void insert(int id) {
    ids[num_squares++] = id;
  }
};

bool dfs(vector<Square>& states, vector<Side>& sides, int num_remained, int cur_depth, int maxd) {
  if (cur_depth == maxd) return num_remained == 0;

  vector<pair<int, int>> num_contains;
  for (int i = 0; i < sides.size(); ++i) {
    auto& side = sides[i];
    num_contains.push_back({0, i});
    if (side.state != UNVISITED) continue;
    auto& num = num_contains.back().first;
    for (int i = 0; i < side.num_squares; ++i) {
      if (states[side.ids[i]].state) num++;
    }
  }
  sort(num_contains.begin(), num_contains.end(), greater<pair<int, int>>());

  int cur_contain = 0;
  int cur_add_depth = 0;
  for (auto& num : num_contains) {
    cur_contain += num.first;
    cur_add_depth++;
    if (cur_contain >= num_remained) break;
  }
  if (cur_depth + cur_add_depth > maxd) return false;

  int num_remained_squares[6];
  memset(num_remained_squares, 0, sizeof(num_remained_squares));
  for (auto& state : states) {
    if (state.state) num_remained_squares[state.size]++;
  }
  for (int i = 1; i <= 5; ++i) {
    if (cur_depth + int(states.back().state) + (num_remained_squares[i] + i * 2 - 1) / (i * 2) > maxd) return false;
  }

  vector<int> sides_visited;
  for (int k = 0; k < sides.size(); ++k) {
    auto& side = sides[num_contains[k].second];
    if (side.state != UNVISITED) continue;

    int corresponding_squares[60];
    int num_corresponding_squares = 0;
    for (int i = 0; i < side.num_squares; ++i) {
      int id = side.ids[i];
      if (states[id].state) corresponding_squares[num_corresponding_squares++] = id;
    }
    if (num_corresponding_squares == 0) continue;

    side.state = VISITED;
    sides_visited.push_back(num_contains[k].second);
    for (int i = 0; i < num_corresponding_squares; ++i)
      states[corresponding_squares[i]].state = false;

    if (dfs(states, sides, num_remained - num_corresponding_squares, cur_depth + 1, maxd)) return true;

    for (int i = 0; i < num_corresponding_squares; ++i)
      states[corresponding_squares[i]].state = true;
  }

  for (auto& k : sides_visited) {
    sides[k].state = UNVISITED;
  }

  return false;
}

int solve() {
  int N;
  cin >> N;

  vector<Square> states;
  vector<Side> sides(2 * N * (N + 1), Side());

  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j + i <= N; ++j) {
      for (int k = 0; k + i <= N; ++k) {
        int id = states.size();
        states.push_back({true, i});
        for (int l = 0; l < i; ++l) {
          sides[j * (2 * N + 1) + k + l].insert(id);
          sides[(j + i) * (2 * N + 1) + k + l].insert(id);
          sides[N + (j + l) * (2 * N + 1) + k].insert(id);
          sides[N + (j + l) * (2 * N + 1) + k + i].insert(id);
        }
      }
    }
  }
  
  int M;
  cin >> M;
  for (int i = 0; i < M; ++i) {
    int k;
    cin >> k;
    --k;
    sides[k].state = DELETED;
    for (int i = 0; i < sides[k].num_squares; ++i) {
      states[sides[k].ids[i]].state = false;
    }
  }

  int num_remained = 0;
  for (int i = 0; i < states.size(); ++i) {
    if (states[i].state) num_remained++;
  }

  int maxd = 0;
  auto sides_tmp = sides;
  for (;; ++maxd) {
    for (auto& side : sides) {
      if (side.state != DELETED) side.state = UNVISITED;
    }
    if (dfs(states, sides, num_remained, 0, maxd)) return maxd;
  }
  return -1;
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    cout << solve() << "\n";
  }

  return 0;
}
