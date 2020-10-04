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

struct Result {
  int weight;
  vector<double> left;
  vector<double> right;
};

int mask_to_id[32];

void initialize() {
  memset(mask_to_id, 0, sizeof(mask_to_id));
  for (int i = 0; i < 6; ++i) {
    mask_to_id[1 << i] = i;
  }
}

Result solveSubProblem(int* weights, int mask) {
  if ((mask & (mask - 1)) == 0) return {weights[mask_to_id[mask]], {0.0}, {0.0}};
  Result result;
  for (int i = 1; i < mask; ++i) {
    if ((mask | i) != mask) continue;
    Result left = solveSubProblem(weights, i);
    Result right = solveSubProblem(weights, mask ^ i);
    result.weight = left.weight + right.weight;
    int N_left = left.left.size();
    int N_right = right.left.size();

    // a * x = b * (1 - x) = b - bx; (a+b)x= b; x = b / (a + b)
    double left_bias = - 1 / (1 + (double(left.weight) / right.weight));
    double right_bias = 1 / (1 + (double(right.weight) / left.weight));
    for (int j = 0; j < N_left; ++j) {
      for (int k = 0; k < N_right; ++k) {
        result.left.push_back(min(left_bias + left.left[j], right_bias + right.left[k]));
        result.right.push_back(max(left_bias + left.right[j], right_bias + right.right[k]));
      }
    }
  }

  return result;
}

void solve() {
  double r;
  int s;
  cin >> r >> s;
  int weights[s];
  for (int i = 0; i < s; ++i) {
    cin >> weights[i];
  }

  int mask = (1 << s) - 1;
  Result result = solveSubProblem(weights, mask);
  double width = -1;
  for (int i = 0; i < result.left.size(); ++i) {
    if (result.right[i] - result.left[i] > r) continue;
    width = max(width, result.right[i] - result.left[i]);
  }
  if (width < 0) cout << "-1\n";
  else cout << width << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  initialize();
  cout.precision(10);
  cout.setf(std::ios::fixed, std::ios::floatfield );

  int N;
  cin >> N;
  while (N--) {
    solve();
  }

  return 0;
}
