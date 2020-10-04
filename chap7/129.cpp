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

bool is_valid(const string& s) {
  int N = s.size();
  int j;
  for (int i = N - 1; (j = 2 * i - N) >= 0; --i) {
    bool flag = true;
    for (int k = 0; k < (N - i); ++k) {
      if (s[i + k] != s[j + k]) {
        flag = false;
        break;
      }
    }
    if (flag) return false;
  }
  return true;
}

int solve(int n, int L, string* current) {
  for (int i = 0; i < L; ++i) {
    current->push_back('A' + i);

    if (is_valid(*current)) {
      n--;
      if (n == 0) return 0;
      n = solve(n, L, current);
      if (n == 0) return 0;
    }

    current->pop_back();
  }

  return n;
}

void print(const string& s) {
  int i = 0;
  int num_group = 0;
  for (auto& c : s) {
    if (i > 0 && i % 4 == 0) {
      num_group++;
      if (num_group % 16 == 0) cout << "\n";
      else cout << " ";
    }
    cout << c;
    i++;
  }
  cout << "\n";
}

void solve(int n, int L) {
  string current;
  solve(n, L, &current);
  // cout << current << "\n";
  print(current);
  cout << current.size() << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n, L;
  while (cin >> n >> L && n > 0 && L > 0) {
    solve(n, L);
  }

  return 0;
}
