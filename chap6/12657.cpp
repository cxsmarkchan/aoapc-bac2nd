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

struct LinkedList {
  int prev;
  int next;
};

void swap(LinkedList* linked_list, int x, int y) {
  if (linked_list[x].prev == y) {
    swap(linked_list, y, x);
    return;
  }
  if (linked_list[x].next == y) {
    int prev = linked_list[x].prev;
    int next = linked_list[y].next;
    linked_list[prev].next = y;
    linked_list[y].prev = prev;
    linked_list[y].next = x;
    linked_list[x].prev = y;
    linked_list[x].next = next;
    linked_list[next].prev = x;
    return;
  }

  int x_prev = linked_list[x].prev;
  int x_next = linked_list[x].next;
  int y_prev = linked_list[y].prev;
  int y_next = linked_list[y].next;
  linked_list[x_prev].next = y;
  linked_list[y].prev = x_prev;
  linked_list[y].next = x_next;
  linked_list[x_next].prev = y;
  linked_list[y_prev].next = x;
  linked_list[x].prev = y_prev;
  linked_list[x].next = y_next;
  linked_list[y_next].prev = x;
}

long long solve(int N) {
  LinkedList linked_list[N + 2];

  for (int i = 1; i <= N; ++i) {
    linked_list[i].prev = i - 1;
    linked_list[i].next = i + 1;
  }
  linked_list[0].next = 1;
  linked_list[N + 1].prev = N;

  int M;
  cin >> M;
  bool reversed = false;
  for (int i = 0; i < M; ++i) {
    int op;
    cin >> op;
    int x, y;
    if (op < 4) cin >> x >> y;
    if (reversed && (op == 1 || op == 2)) op = 3 - op;
    switch (op) {
      case 1:
        {
          if (linked_list[x].next != y) {
            // remove x
            int x_prev = linked_list[x].prev;
            int x_next = linked_list[x].next;
            linked_list[x_prev].next = linked_list[x].next;
            linked_list[x_next].prev = linked_list[x].prev;

            // insert x
            linked_list[x].prev = linked_list[y].prev;
            linked_list[x].next = y;
            linked_list[y].prev = x;
            linked_list[linked_list[x].prev].next = x;
          }
        }
        break;
      case 2:
        {
          if (linked_list[x].prev != y) {
            // remove x
            int x_prev = linked_list[x].prev;
            int x_next = linked_list[x].next;
            linked_list[x_prev].next = linked_list[x].next;
            linked_list[x_next].prev = linked_list[x].prev;

            // insert x
            linked_list[x].next = linked_list[y].next;
            linked_list[x].prev = y;
            linked_list[y].next = x;
            linked_list[linked_list[x].next].prev = x;
          }
        }
        break;
      case 3:
        {
          swap(linked_list, x, y);
        }
        break;
      case 4:
        reversed = !reversed;
        break;
    }
  }

  long long ret = 0;
  if (!reversed) {
    int current = linked_list[0].next;
    while (current != N + 1) {
      ret += current;
      current = linked_list[current].next;
      if (current != N + 1) current = linked_list[current].next;
    }
  } else {
    int current = linked_list[N + 1].prev;
    while (current != 0) {
      ret += current;
      current = linked_list[current].prev;
      if (current != 0) current = linked_list[current].prev;
    }
  }

  return ret;
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int N;
  int case_num = 0;
  while (cin >> N) {
    cout << "Case " << ++case_num << ": " << solve(N) << "\n";
  }

  return 0;
}
