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

using namespace std;

typedef long long ll;
const ll MAX_VALUE = 1e16;

inline void quickread() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}



int get_digit(ll num, ll digit10) {
  return (num % (digit10 * 10)) / digit10;
}

struct Trie {
  int value = 100000000;
  Trie* next[10];

  Trie() {
    memset(next, 0, sizeof(next));
  }

  ~Trie() {
    for (int i = 0; i < 10; ++i) {
      if (next[i] != nullptr) {
        delete next[i];
      }
    }
  }

  void update(int digit, int id) {
    if (next[digit] == nullptr) {
      next[digit] = new Trie;
    }
    next[digit]->value = min(next[digit]->value, id);
  }
} trie;

struct BigInteger {
  ll* values;
  int size = 0;

  BigInteger(ll num) : size(1) {
    values = new ll[10000];
    memset(values, 0, sizeof(ll) * 10000);
    values[0] = num;
  }

  ~BigInteger() {
    delete[] values;
  }

  BigInteger& operator+=(const BigInteger& right) {
    int right_num = right.size;
    size = max(size, right_num);
    ll carry = 0;
    for (int i = max(0, right_num - 20); i < right_num; ++i) {
      values[i] += (right.values[i] + carry);
      carry = values[i] / MAX_VALUE;
      values[i] %= MAX_VALUE;
    }
    for (int i = right_num; i < size; ++i) {
      values[i] += carry;
      carry = values[i] / MAX_VALUE;
      values[i] %= MAX_VALUE;
    }
    if (carry > 0) {
      values[size++] = carry;
    }
    return *this;
  }

  void update(int id, Trie& trie) const {
    int pos1 = size - 1;
    ll mask = 1e15;
    while (get_digit(values[pos1], mask) == 0) mask /= 10;

    int prefix_size = 0;
    Trie* current_node = &trie;
    while (pos1 >= 0 && prefix_size++ < 40) {
      int digit = get_digit(values[pos1], mask);
      current_node->update(digit, id);
      current_node = current_node->next[digit];

      mask /= 10;
      if (mask == 0) {
        mask = 1e15;
        pos1--;
      }
    }
    // cout << id << ":" << size << " " << prefix << endl;
  }
};

void swap(BigInteger& lhs, BigInteger& rhs) {
  swap(lhs.values, rhs.values);
  swap(lhs.size, rhs.size);
}

void initialize() {
  BigInteger a(1);
  BigInteger b(1);
  a.update(0, trie);
  b.update(1, trie);

  for (int i = 2; i < 100000; ++i) {
    a += b;
    swap(a, b);
    b.update(i, trie);
  }
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  quickread();

  initialize();

  int T;
  cin >> T;

  for (int t = 1; t <= T; t++) {
    string prefix;
    cin >> prefix;
    Trie* current_node = &trie;
    int ans = -10000;
    for (auto& c : prefix) {
      int digit = c - '0';
      if (current_node->next[digit] == nullptr) {
        ans = -1;
        break;
      } else {
        current_node = current_node->next[digit];
      }
    }
    if (ans == -10000) {
      ans = current_node->value;
    }
    printf("Case #%d: %d\n", t, ans);
  }

  return 0;
}
