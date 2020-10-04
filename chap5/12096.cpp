#include <iostream>
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

struct Set {
  set<int> elems;

  int size() const {
    return elems.size();
  }

  int toId(map<set<int>, int>& set_to_id) {
    auto it = set_to_id.find(elems);
    if (it == set_to_id.end()) {
      int ret = set_to_id.size();
      set_to_id[elems] = ret;
      return ret;
    } else {
      return it->second;
    }
  }
};

struct SetStack {
  typedef function<void(void)> Operation;

  stack<Set> st;
  unordered_map<string, Operation> op_map;
  map<set<int>, int> id_set;

  SetStack() {
    op_map = {
      {"PUSH", bind(&SetStack::Push, this)},
      {"DUP", bind(&SetStack::Dup, this)},
      {"UNION", bind(&SetStack::Union, this)},
      {"INTERSECT", bind(&SetStack::Intersect, this)},
      {"ADD", bind(&SetStack::Add, this)}
    };
  }


  int Operate(const string& op) {
    auto it = op_map.find(op);
    if (it != op_map.end()) {
      it->second();
    }
    return st.top().size();
  }

  void Push() {
    st.push(Set());
  }

  void Dup() {
    st.push(st.top());
  }

  void Union() {
    auto set1 = st.top();
    st.pop();
    auto set2 = st.top();
    st.pop();
    Set set;
    for (auto& elem : set1.elems) {
      set.elems.insert(elem);
    }
    for (auto& elem : set2.elems) {
      set.elems.insert(elem);
    }
    st.push(move(set));
  }

  void Intersect() {
    auto set1 = st.top();
    st.pop();
    auto set2 = st.top();
    st.pop();
    Set set;
    for (auto& elem : set1.elems) {
      if (set2.elems.find(elem) != set2.elems.end()) {
        set.elems.insert(elem);
      }
    }
    st.push(move(set));
  }

  void Add() {
    auto set1 = st.top();
    st.pop();
    auto set2 = st.top();
    st.pop();
    set2.elems.insert(set1.toId(id_set));
    st.push(move(set2));
  }
};

void solve() {
  int N;
  cin >> N;
  SetStack st;
  for (int i = 0; i < N; ++i) {
    string op;
    cin >> op;
    cout << st.Operate(op) << "\n";
  }
  cout << "***\n";
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
