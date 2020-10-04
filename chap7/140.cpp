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

const int SOURCE = 0;
const int TARGET = 1;

bool next_permutation(vector<int>& vec) {
  for (int i = vec.size() - 1; i > 0; --i) {
    if (vec[i - 1] < vec[i]) {
      for (int j = vec.size() - 1; j >= i; --j) {
        if (vec[i - 1] < vec[j]) {
          swap(vec[i - 1], vec[j]);
          sort(vec.begin() + i, vec.end());
          return true;
        }
      }
    }
  }
  return false;
}

void solve(const string& s) {
  bool adj[26][26];
  memset(adj, 0, sizeof(adj));

  int state = SOURCE;
  int source;
  unordered_set<int> nodes;
  for (auto& c : s) {
    switch (state) {
      case SOURCE:
        source = c - 'A';
        nodes.insert(source);
        state = TARGET;
        break;
      case TARGET:
        if (c == ';') state = SOURCE;
        else if (c != ':') {
          adj[source][c - 'A'] = adj[c - 'A'][source] = true;
          nodes.insert(c - 'A');
        }
        break;
      default:
        break;
    }
  }

  vector<int> result;
  int min_dist = 10000;
  vector<int> node_vec(nodes.begin(), nodes.end());
  sort(node_vec.begin(), node_vec.end());
  do {
    int cur_dist = 0;
    for (int i = 0; i < node_vec.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (adj[node_vec[i]][node_vec[j]]) cur_dist = max(cur_dist, i - j);
      }
    }
    if (min_dist > cur_dist) {
      min_dist = cur_dist;
      result = node_vec;
    }
  } while (next_permutation(node_vec));

  for (auto& v : result) {
    cout << char(v + 'A') << " ";
  }
  cout << "-> " << min_dist << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  string s;
  while (cin >> s, s[0] != '#') {
    solve(s);
  }

  return 0;
}
