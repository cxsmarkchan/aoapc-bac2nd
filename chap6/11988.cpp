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

struct ListNode {
  char value;
  ListNode* next;
  ListNode(char value_, ListNode* next_ = nullptr) : value(value_), next(next_) {}
};

void solve(const string& s) {
  ListNode* head = new ListNode(0);
  ListNode* back = head;

  ListNode* current = head;

  for (auto& c : s) {
    switch (c) {
      case '[':
        current = head;
        break;
      case ']':
        current = back;
        break;
      default:
        current->next = new ListNode(c, current->next);
        if (current == back) {
          back = current->next;
        }
        current = current->next;
        break;
    }
  }

  current = head;
  while (current->next != nullptr) {
    cout << current->next->value;
    ListNode* tmp = current;
    current = current->next;
    delete tmp;
  }
  delete current;
  cout << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  string s;
  while (cin >> s) {
    solve(s);
  }

  return 0;
}
