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

void solve(int n) {
  vector<unordered_set<int>> beat(n);

  string s[n];
  bool available[n];

  for (int i = 0; i < n; ++i) {
    cin >> s[i];
    available[i] = true;
  }

  for (int j = 1; j < n; ++j) {
    if (s[0][j] == '1') beat[0].insert(j);
  }
  for (int i = 1; i < n; ++i) {
    if (beat[0].find(i) == beat[0].end()) continue;
    for (int j = 1; j < n; ++j) {
      if (s[i][j] == '1' && beat[0].find(j) == beat[0].end()) beat[i].insert(j);
    }
  }

  int K = 0;
  while ((1 << K) < n) K++;

  for (int i = 0; i < K; ++i) {
    bool status[n];
    memcpy(status, available, sizeof(status));

    for (auto& item : beat[0]) {
      for (auto& beat_item : beat[item]) {
        if (!status[beat_item]) continue;
        cout << item + 1 << " ";
        status[item] = false;
        cout << beat_item + 1 << "\n";
        available[beat_item] = false;
        status[beat_item] = false;
        break;
      }
    }

    cout << "1 ";
    status[0] = false;
    for (int i = 1; i < n; ++i) {
      if (!status[i]) continue;
      if (beat[0].find(i) != beat[0].end()) {
        cout << i + 1 << "\n";
        status[i] = false;
        available[i] = false;
        break;
      }
    }

    int prev = -1;
    for (int i = 0; i < n; ++i) {
      if (!status[i]) continue;
      if (beat[0].find(i) != beat[0].end()) continue;
      if (prev == -1) {
        cout << i + 1 << " ";
        status[i] = false;
        prev = i;
      } else {
        cout << i + 1 << "\n";
        status[i] = false;
        if (s[i][prev] == '1') available[prev] = false;
        else available[i] = false;
        prev = -1;
      }
    }

    for (int i = 0; i < n; ++i) {
      if (!status[i]) continue;
      if (prev == -1) {
        cout << i + 1 << " ";
        status[i] = false;
        prev = i;
      } else {
        cout << i + 1 << "\n";
        status[i] = false;
        if (s[i][prev] == '1') available[prev] = false;
        else available[i] = false;
        prev = -1;
      }
    }

    for (int i = 0; i < n; ++i) {
      unordered_set<int> cur_beat;
      for (auto& item : beat[i]) {
        if (available[item]) cur_beat.insert(item);
      }
      beat[i] = move(cur_beat);
    }
  }
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n;
  while (cin >> n) {
    solve(n);
  }

  return 0;
}
