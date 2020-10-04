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


vector<int> x_vec, y_vec, z_vec;
int state[150][150][150];
bool visited[150][150][150];
int volume = 0;
int square = 0;
int Nx, Ny, Nz;

bool is_valid_1d(int i, int N) {
  return i >= 0 && i < N;
}

bool is_valid(int i, int j, int k) {
  return is_valid_1d(i, Nx) && is_valid_1d(j, Ny) && is_valid_1d(k, Nz);
}

int directions[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};

void dfs(int i, int j, int k) {
  visited[i][j][k] = true;
  volume += 1;
  for (int d = 0; d < 6; ++d) {
    int new_i = i + directions[d][0];
    int new_j = j + directions[d][1];
    int new_k = k + directions[d][2];
    if (!is_valid(new_i, new_j, new_k)) continue;
    if (visited[new_i][new_j][new_k]) continue;
    if (state[new_i][new_j][new_k] == 1) {
      square += 1;
    } else {
      dfs(new_i, new_j, new_k);
    }
  }
}

void solve() {
  int N;
  cin >> N;

  int x1[N], x2[N];
  int y1[N], y2[N];
  int z1[N], z2[N];
  unordered_set<int> x_set, y_set, z_set;

  for (int i = 0; i < N; ++i) {
    cin >> x1[i] >> y1[i] >> z1[i];
    cin >> x2[i] >> y2[i] >> z2[i];
    x2[i] += x1[i];
    y2[i] += y1[i];
    z2[i] += z1[i];
    x_set.insert(x1[i]);
    x_set.insert(x2[i]);
    y_set.insert(y1[i]);
    y_set.insert(y2[i]);
    z_set.insert(z1[i]);
    z_set.insert(z2[i]);
  }

  x_vec = vector<int>(x_set.begin(), x_set.end());
  y_vec = vector<int>(y_set.begin(), y_set.end());
  z_vec = vector<int>(z_set.begin(), z_set.end());
  sort(x_vec.begin(), x_vec.end());
  sort(y_vec.begin(), y_vec.end());
  sort(z_vec.begin(), z_vec.end());

  Nx = x_vec.back() - x_vec[0] + 2;
  Ny = y_vec.back() - y_vec[0] + 2;
  Nz = z_vec.back() - z_vec[0] + 2;

  memset(state, 0, sizeof(state));
  for (int n = 0; n < N; ++n) {
    for (int i = x1[n]; i < x2[n]; ++i) {
      for (int j = y1[n]; j < y2[n]; ++j) {
        for (int k = z1[n]; k < z2[n]; ++k) {
          state[i - x_vec[0] + 1][j - y_vec[0] + 1][k - z_vec[0] + 1] = 1;
        }
      }
    }
  }

  memset(visited, 0, sizeof(visited));
  volume = 0;
  square = 0;
  dfs(0, 0, 0);
  volume = Nx * Ny * Nz - volume;
  cout << square << " " << volume << "\n";
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
