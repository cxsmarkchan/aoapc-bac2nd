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

int counterpart(int i) {
  return 51 - i;
}

int key_to_id(char key, char p) {
  if (p == '+') return key - 'A';
  else return 51 - (key - 'A');
}

bool dfs(vector<int>& state, const vector<vector<int>>& adj, int i) {
  state[i] = -1;
  for (auto& v : adj[i]) {
    if (state[v] == 1) continue;
    if (state[v] == -1) return true;
    if (dfs(state, adj, v)) return true;
  }
  state[i] = 1;
  return false;
}

bool find_loop(const vector<vector<int>>& adj) {
  int N = adj.size();
  vector<int> state(N, 0);
  for (int i = 0; i < N; ++i) {
    if (state[i] == 0) {
      if (dfs(state, adj, i)) return true;
    }
  }
  return false;
}

bool solve(int N) {
  unordered_set<int> elements[52];
  for (int i = 0; i < N; ++i) {
    string s;
    cin >> s;
    vector<int> ids;
    for (int j = 0; j < 4; ++j) {
      if (s[j * 2] == '0') continue;
      ids.push_back(key_to_id(s[j * 2], s[j * 2 + 1]));
    }
    for (int j = 0; j < ids.size(); ++j) {
      for (int k = 0; k < ids.size(); ++k) {
        if (j == k) continue;
        elements[ids[j]].insert(ids[k]);
      }
    }
  }

  vector<vector<int>> adj(52, vector<int>());
  for (int i = 0; i < 52; ++i) {
    for (int k : elements[i]) {
      adj[counterpart(i)].push_back(k);
    }
  }

  return find_loop(adj);
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int N;
  while (cin >> N) {
    if (solve(N)) cout << "unbounded\n";
    else cout << "bounded\n";
  }

  return 0;
}
