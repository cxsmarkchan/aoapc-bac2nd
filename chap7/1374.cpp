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

int min_remained_depth(int n, vector<int>& cur_set) {
  // plus
  int maximum_less_than_n = 0;
  int minimum_larger_than_n = 1000000;
  int num_larger = 0;
  for (int i = 0; i < cur_set.size(); ++i) {
    if (cur_set[i] < n && cur_set[i] > maximum_less_than_n) {
      maximum_less_than_n = cur_set[i];
    }
    if (cur_set[i] > n) {
      num_larger++;
      if (cur_set[i] < minimum_larger_than_n) {
        minimum_larger_than_n = cur_set[i];
      }
    }
  }
  
  if (num_larger > 1) return 1000;

  // minus
  int n_enlarge = 0;
  int enlarge_num = maximum_less_than_n;
  while (enlarge_num < n && enlarge_num < minimum_larger_than_n + maximum_less_than_n - n) {
    n_enlarge++;
    enlarge_num <<= 1;
  }
  return n_enlarge;
}

string to_string(const vector<int>& cur_set) {
  vector<int> vec(cur_set.begin(), cur_set.end());
  sort(vec.begin(), vec.end());
  stringstream ss;
  for (auto& item : vec) {
    ss << item << ";";
  }
  return ss.str();
}

bool dfs(int n, int max_depth, int cur_depth, vector<int>& cur_set, vector<bool>& visited) {
  if (cur_depth == max_depth) {
    return visited[n];
  }

  if (cur_depth + min_remained_depth(n, cur_set) > max_depth) return false;

  int N = cur_set.size();
  int i = N - 1;
  for (int j = i; j >= 0; --j) {
    int minus = abs(cur_set[i] - cur_set[j]);
    int plus = cur_set[i] + cur_set[j];
    if (plus <= 2 * n && !visited[plus]) {
      visited[plus] = true;
      cur_set.push_back(plus);
      if (dfs(n, max_depth, cur_depth + 1, cur_set, visited)) return true;
      cur_set.pop_back();
      visited[plus] = false;
    }

    if (minus > 0 && !visited[minus]) {
      visited[minus] = true;
      cur_set.push_back(minus);
      if (dfs(n, max_depth, cur_depth + 1, cur_set, visited)) return true;
      cur_set.pop_back();
      visited[minus] = false;
    }
    
  }

  return false;
}

int solve(int n) {
  vector<bool> visited(2 * n + 10, false);
  vector<int> cur_set;

  cur_set.push_back(1);
  visited[1] = true;

  int cur_depth = 0;
  int max_depth = cur_depth;
  for (; ; max_depth++) {
    if (dfs(n, max_depth, cur_depth, cur_set, visited)) return max_depth;
  }

  return -1;
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n;
  while (cin >> n, n > 0) {
    cout << solve(n) << "\n";
  }

  return 0;
}
