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

typedef long long ll;
const ll DENOM = 20000000000LL;

bool check_valid(ll* S, ll target, int n, int L, int* left, int* right) {
  // (DENOM, target) -> (-target, DENOM)
  vector<pair<ll, int>> st;

  int min_len = n + 1;
  for (int i = L; i <= n; ++i) {
    ll cur_value = S[i - L] * DENOM - (i - L) * target;
    while (!st.empty() && st.back().first >= cur_value) st.pop_back();
    st.push_back({cur_value, i - L});
    cur_value = S[i] * DENOM - i * target;

    int begin = -1, end = st.size();
    while (end - begin > 1) {
      int mid = (begin + end) / 2;
      if (st[mid].first <= cur_value) begin = mid;
      else end = mid;
    }
    if (begin >= 0 && i - st[begin].second < min_len) {
      *left = st[begin].second;
      *right = i;
      min_len = i - st[begin].second;
    }
  }

  return min_len <= n;
}

void solve() {
  int n, L;
  cin >> n >> L;
  string input;
  cin >> input;

  long long S[n + 1];
  S[0] = 0;
  for (int i = 0; i < n; ++i) {
    S[i + 1] = S[i] + input[i] - '0';
  }

  ll begin = -1, end = DENOM + 1;
  // begin: has valid
  // end: no valid
  int left, right;
  // check_valid(S, 8, n, L, &left, &right);
  while (end - begin > 1) {
    ll mid = (begin + end) / 2;
    if (check_valid(S, mid, n, L, &left, &right)) begin = mid;
    else end = mid;
  }

  cout << left + 1 << " " << right << "\n";
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
