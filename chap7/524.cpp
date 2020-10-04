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

bool is_prime[40];

void initialize() {
  memset(is_prime, 0, sizeof(is_prime));
  int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  int num_primes = sizeof(primes) / sizeof(int);
  for (int i = 0; i < num_primes; ++i) {
    is_prime[primes[i]] = true;
  }
}

bool visited[16];
int ring[16];

void dfs(const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& ret, int remain) {
  if (remain == 0) {
    if (ret.size() == 1 || is_prime[ret.back() + ret[0]]) {
      for (int i = 0; i < ret.size(); ++i) {
        if (i > 0) cout << " ";
        cout << ret[i];
      }
      cout << "\n";
    }
    return;
  }

  int current_node = ret.back();
  for (auto& v : adj[current_node]) {
    if (visited[v]) continue;
    visited[v] = true;
    ret.push_back(v);
    
    dfs(adj, visited, ret, remain - 1);

    ret.pop_back();
    visited[v] = false;
  }
}

void solve(int n) {
  vector<vector<int>> adj(n + 1, vector<int>());
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i == j) continue;
      if (is_prime[i + j]) {
        adj[i].push_back(j);
      }
    }
  }

  vector<bool> visited(n, false);
  visited[1] = true;
  vector<int> ret(1, 1);

  dfs(adj, visited, ret, n - 1);
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  initialize();

  int n;
  int i = 0;
  while (cin >> n) {
    if (i > 0) cout << "\n";
    cout << "Case " << ++i << ":\n";
    solve(n);
  }

  return 0;
}
