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

void solve(vector<string>& tree, int depth, int pos) {
  cout << "(";
  if (depth + 3 < tree.size() && tree[depth + 1][pos] == '|' && tree[depth + 2][pos] == '-') {
    int p1 = pos, p2 = pos;
    int new_depth = depth + 2;
    while (p1 > 0 && tree[new_depth][p1 - 1] == '-') p1--;
    while (p2 < tree[new_depth].size() - 1 && tree[new_depth][p2 + 1] == '-') p2++;
    for (int i = p1; i <= p2 && i < tree[new_depth + 1].size(); ++i) {
      if (tree[new_depth + 1][i] == ' ') continue;
      cout << tree[new_depth + 1][i];
      solve(tree, new_depth + 1, i);
    }
  }
  cout << ")";
}

void solve() {
  char buf[256];
  vector<string> raw_tree;

  while (cin.getline(buf, 256), buf[0] != '#') {
    raw_tree.push_back(string(buf));
  }

  if (raw_tree.size() == 0) {
    cout << "()\n";
    return;
  }

  cout << "(";
  for (int i = 0; i < raw_tree[0].size(); ++i) {
    auto& c = raw_tree[0][i];
    if (c != ' ') {
      cout << c;
      solve(raw_tree, 0, i);
    }
  }
  cout << ")\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  char buf[256];
  cin.getline(buf, 256);

  while (T--) {
    solve();
  }

  return 0;
}
