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

int num_bits[1024];

void initialize() {
  memset(num_bits, 0, sizeof(num_bits));
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 1024; ++j) {
      if (j & (1 << i)) num_bits[j]++;
    }
  }
}

int row_left(int w, const vector<int>& masks) {
  int total_mask = 0;
  for (int i = 0; i < masks.size(); ++i) {
    total_mask |= masks[i];
  }
  return w - num_bits[total_mask];
}

vector<int> rotate90(int w, const vector<int>& masks) {
  vector<int> new_mask(w, 0);
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < w; ++j) {
      int bit = (masks[j] & (1 << (w - 1 - i))) > 0;
      new_mask[i] |= (bit << j);
    }
  }
  return new_mask;
}

vector<int> rotate180(int w, int h, const vector<int>& masks) {
  vector<int> new_mask(h, 0);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      int bit = (masks[h - 1 - i] & (1 << (w - 1 - j))) > 0;
      new_mask[i] |= (bit << j);
    }
  }
  return new_mask;
}

void dfs_continuous(int w, int h, vector<int>& masks, int i, int j) {
  masks[i] ^= (1 << j);
  if (i > 0 && (masks[i - 1] & (1 << j))) dfs_continuous(w, h, masks, i - 1, j);
  if (i < h - 1 && (masks[i + 1] & (1 << j))) dfs_continuous(w, h, masks, i + 1, j);
  if (j > 0 && (masks[i] & (1 << (j - 1)))) dfs_continuous(w, h, masks, i, j - 1);
  if (j < w - 1 && (masks[i] & (1 << (j + 1)))) dfs_continuous(w, h, masks, i, j + 1);
}

bool is_continuous(int w, int h, const vector<int>& masks) {
  vector<int> tmp_masks = masks;
  for (int j = 0; j < w; ++j) {
    if (tmp_masks[0] & (1 << j)) {
      dfs_continuous(w, h, tmp_masks, 0, j);
      break;
    }
  }
  for (int i = 0; i < h; ++i) {
    if (tmp_masks[i] > 0) return false;
  }
  return true;
}

bool is_continuous_last_line(int w, int h, const vector<int>& masks) {
  vector<int> tmp_masks = masks;
  for (int j = 0; j < w; ++j) {
    if (tmp_masks[h - 1] & (1 << j)) {
      dfs_continuous(w, h - 1, tmp_masks, h - 1, j);
    }
  }
  for (int i = 0; i <= h - 1; ++i) {
    if (tmp_masks[i] > 0) return false;
  }
  return true;
}

bool symmetry_insert(int w, int h, const vector<int>& masks, set<vector<int>>& all_masks) {
  if (row_left(w, masks) > 0) return false;
  if (masks.size() < h) return false;
  if (all_masks.find(masks) != all_masks.end()) return false;
  if (!is_continuous(w, h, masks)) return false;

  if (w == h) {
    vector<int> current = masks;
    for (int i = 0; i < 4; ++i) {
      current = rotate90(w, current);
      all_masks.insert(current);
    }
    reverse(current.begin(), current.end());
    for (int i = 0; i < 4; ++i) {
      current = rotate90(w, current);
      all_masks.insert(current);
    }
  } else {
    vector<int> current = masks;
    for (int i = 0; i < 2; ++i) {
      current = rotate180(w, h, current);
      all_masks.insert(current);
    }
    reverse(current.begin(), current.end());
    for (int i = 0; i < 2; ++i) {
      current = rotate180(w, h, current);
      all_masks.insert(current);
    }
  }

  return true;
}

int dfs(int n, int w, int h, int cur_h, vector<int>& masks, set<vector<int>>& all_masks) {
  if (n == 0) {
    if (symmetry_insert(w, h, masks, all_masks)) return 1;
  }

  if (cur_h >= h) return 0;

  if (row_left(w, masks) > n) return 0;
  if (h - masks.size() > n) return 0;

  int num = 0;

  int mask = 1 << w;
  for (int i = 1; i < mask; ++i) {
    if (num_bits[i] > n) continue;
    masks.push_back(i);
    if (!is_continuous_last_line(w, masks.size(), masks)) {
      masks.pop_back();
      continue;
    }
    num += dfs(n - num_bits[i], w, h, cur_h + 1, masks, all_masks);
    masks.pop_back();
  }

  return num;
}

int solve_compact(int n, int w, int h) {
  if (w + h - 1 > n) {
    return 0;
  }
  if (w * h < n) {
    return 0;
  }

  set<vector<int>> all_masks;
  int num = 0;
  // w <= h
  int mask = 1 << w;
  vector<int> masks;
  for (int i = 1; i < mask; ++i) {
    if (num_bits[i] > n) continue;
    masks.push_back(i);
    num += dfs(n - num_bits[i], w, h, 1, masks, all_masks);
    masks.pop_back();
  }

  return num;
}

int solve(int n, int w, int h) {
  if (w > h) {
    swap(w, h);
  }

  int num = 0;
  for (int i = 1; i <= w; ++i) {
    for (int j = i; j <= h; ++j) {
      int tmp = solve_compact(n, i, j);
      num += tmp;
    }
  }

  return num;
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  initialize();

  int n, w, h;
  while (cin >> n >> w >> h) {
    cout << solve(n, w, h) << "\n";
  }

  return 0;
}
