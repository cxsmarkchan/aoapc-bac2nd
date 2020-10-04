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

int get_volume(int i, int j, int k) {
  if (i == Nx - 1 || j == Ny - 1 || k == Nz - 1) return 0;
  return (x_vec[i + 1] - x_vec[i]) * (y_vec[j + 1] - y_vec[j]) * (z_vec[k + 1] - z_vec[k]);
}

int get_square(int i, int j, int k, const int * direction) {
  if (direction[0] != 0) {
    return (y_vec[j + 1] - y_vec[j]) * (z_vec[k + 1] - z_vec[k]);
  } else if (direction[1] != 0) {
    return (x_vec[i + 1] - x_vec[i]) * (z_vec[k + 1] - z_vec[k]);
  } else if (direction[2] != 0) {
    return (x_vec[i + 1] - x_vec[i]) * (y_vec[j + 1] - y_vec[j]);
  }
  return 0;
}

int directions[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};

void dfs(int i, int j, int k) {
  visited[i][j][k] = true;
  volume += get_volume(i, j, k);
  for (int d = 0; d < 6; ++d) {
    int new_i = i + directions[d][0];
    int new_j = j + directions[d][1];
    int new_k = k + directions[d][2];
    if (!is_valid(new_i, new_j, new_k)) continue;
    if (visited[new_i][new_j][new_k]) continue;
    if (state[new_i][new_j][new_k] == 1) {
      square += get_square(new_i, new_j, new_k, directions[d]);
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
  x_vec.push_back(0);
  y_vec.push_back(0);
  z_vec.push_back(0);
  sort(x_vec.begin(), x_vec.end());
  sort(y_vec.begin(), y_vec.end());
  sort(z_vec.begin(), z_vec.end());
  x_vec.push_back(x_vec.back());
  y_vec.push_back(y_vec.back());
  z_vec.push_back(z_vec.back());

  Nx = x_vec.size();
  Ny = y_vec.size();
  Nz = z_vec.size();

  int x_map[1005], y_map[1005], z_map[1005];
  memset(x_map, 0, sizeof(x_map));
  memset(y_map, 0, sizeof(y_map));
  memset(z_map, 0, sizeof(z_map));
  for (int i = 1; i < x_vec.size() - 1; ++i) {
    x_map[x_vec[i]] = i;
  }
  for (int i = 1; i < y_vec.size() - 1; ++i) {
    y_map[y_vec[i]] = i;
  }
  for (int i = 1; i < z_vec.size() - 1; ++i) {
    z_map[z_vec[i]] = i;
  }

  memset(state, 0, sizeof(state));
  for (int n = 0; n < N; ++n) {
    int xx1 = x_map[x1[n]], xx2 = x_map[x2[n]];
    int yy1 = y_map[y1[n]], yy2 = y_map[y2[n]];
    int zz1 = z_map[z1[n]], zz2 = z_map[z2[n]];
    for (int i = xx1; i < xx2; ++i) {
      for (int j = yy1; j < yy2; ++j) {
        for (int k = zz1; k < zz2; ++k) {
          state[i][j][k] = 1;
        }
      }
    }
  }

  memset(visited, 0, sizeof(visited));
  volume = 0;
  square = 0;
  dfs(0, 0, 0);
  volume = x_vec.back() * y_vec.back() * z_vec.back() - volume;
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
