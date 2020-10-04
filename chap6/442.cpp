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

pair<int, int> matrix[26];


pair<int, int> Multiply(const pair<int, int>& matrix1, const pair<int, int>& matrix2, int& num_op) {
  if (matrix1.first == -1) return matrix2;
  if (matrix2.first == -1) return matrix1;

  if (matrix1.first == 0 || matrix1.second == 0) return {0, 0};
  if (matrix2.first == 0 || matrix2.second == 0) return {0, 0};

  if (matrix1.second != matrix2.first) return {0, 0};
  num_op += matrix1.first * matrix1.second * matrix2.second;
  return {matrix1.first, matrix2.second};
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  memset(matrix, 0, sizeof(matrix));

  int n_matrix;
  cin >> n_matrix;

  for (int i = 0; i < n_matrix; ++i) {
    char c;
    cin >> c;
    cin >> matrix[c - 'A'].first >> matrix[c - 'A'].second;
  }

  string s;
  while (cin >> s) {
    int num_op = 0;
    stack<pair<int, int>> st;
    st.push({-1, -1});
    for (auto& c : s) {
      switch (c) {
        case '(':
          st.push({-1, -1});
          break;
        case ')':
          {
            auto matrix2 = st.top();
            st.pop();
            auto matrix1 = st.top();
            st.pop();
            auto matrix3 = Multiply(matrix1, matrix2, num_op);
            st.push(matrix3);
          }
          break;
        default:
          {
            auto matrix1 = st.top();
            st.pop();
            auto& matrix2 = matrix[c - 'A'];
            auto matrix3 = Multiply(matrix1, matrix2, num_op);
            st.push(matrix3);
          }
      }
    }
    if (st.top().first == 0) {
      cout << "error\n";
    } else {
      cout << num_op << "\n";
    }
  }

  return 0;
}
