#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

bool reach_end(int cur_time, int* a, int* b, int n) {
  return cur_time >= 10000;
  if (cur_time == 0) return false;

  for (int i = 0; i < n; ++i) {
    if (cur_time % (a[i] + b[i]) != 0) return false;
  }
  return true;
}

int solve(int n) {
  int cur_time = 0;
  int min_awake_time = 0;

  int a[n], b[n], c[n];
  bool is_awake[n];
  int switch_time[n];
  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> b[i] >> c[i];
    is_awake[i] = (c[i] <= a[i]);
    switch_time[i] = (a[i] + ((c[i] <= a[i]) ? 0 : b[i])) - c[i] + 1;

    if (!is_awake[i])
      min_awake_time = max(min_awake_time, switch_time[i]);
  }

  while (!reach_end(cur_time, a, b, n)) {
    int min_switch = switch_time[0];
    for (int i = 1; i < n; ++i) {
      min_switch = min(min_switch, switch_time[i]);
    }
    cur_time = min_switch;

    int num_asleep = 0;
    for (int i = 0; i < n; ++i) {
      if (is_awake[i]) {
        if (switch_time[i] == min_switch) {
          is_awake[i] = false;
          switch_time[i] += b[i];
        }
      } else {
        if (switch_time[i] == min_switch) {
          is_awake[i] = true;
          switch_time[i] += a[i];
        }
        num_asleep++;
      }
    }

    if (2 * (num_asleep) <= n) {
      return min_awake_time + 1;
    } else {
      for (int i = 0; i < n; ++i) {
        if (!is_awake[i]) {
          min_awake_time = max(min_awake_time, switch_time[i]);
        }
      }
    }
  }
  return -1;
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif
  int n;
  int case_number = 0;
  while (cin >> n, n > 0) {
    int last_time = solve(n);
    cout << "Case " << ++case_number << ": " << last_time << "\n";
  }
  return 0;
}
