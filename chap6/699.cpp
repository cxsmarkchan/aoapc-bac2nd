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

template<typename T>
struct DeVec {
  vector<T> pos;
  vector<T> neg;

  T& operator[](int id) {
    if (id >= 0) return get(pos, id);
    else return get(neg, -id - 1);
  }

  T& get(vector<int>& vec, int id) {
    while (vec.size() <= id) vec.push_back(static_cast<T>(0));
    return vec[id];
  }

  void display() {
    bool flag = false;
    for (int i = neg.size() - 1; i >= 0; --i) {
      if (flag) cout << " ";
      cout << neg[i];
      flag = true;
    }
    for (int i = 0; i < pos.size(); ++i) {
      if (flag) cout << " ";
      cout << pos[i];
      flag = true;
    }
    cout << "\n";
  }
};

bool solve(int case_id) {
  int root;
  cin >> root;
  if (root == -1) return false;

  DeVec<int> devec;
  stack<pair<int, bool>> st;
  st.push({0, false});
  devec[0] += root;

  while (!st.empty()) {
    auto& top = st.top();
    int next_value;
    cin >> next_value;
    int next_pos;
    if (!top.second) {
      next_pos = top.first - 1;
      top.second = true;
    } else {
      next_pos = top.first + 1;
      st.pop();
    }
    if (next_value >= 0) {
      st.push({next_pos, false});
      devec[next_pos] += next_value;
    }
  }

  cout << "Case " << case_id << ":\n";
  devec.display();
  cout << "\n";

  return true;
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int i = 0;
  while (solve(++i));

  return 0;
}
