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

void solve(int N) {
  int vec[N];
  while (cin >> vec[0], vec[0] > 0) {
    for (int i = 1; i < N; ++i) cin >> vec[i];

    stack<int> st;
    int pos = 0;
    for (int i = 1; i <= N; ++i) {
      st.push(i);
      while (!st.empty() && st.top() == vec[pos]) {
        st.pop();
        pos++;
      }
    }
    if (st.empty()) cout << "Yes\n";
    else cout << "No\n";
  }
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int N;
  int k = 0;
  while (cin >> N, N > 0) {
    solve(N);
    cout << "\n";
  }

  return 0;
}
