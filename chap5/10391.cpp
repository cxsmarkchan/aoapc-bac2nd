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

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  vector<string> word_vec;
  unordered_set<string> word_dict;
  string buf;
  while (cin >> buf && buf.size() > 0) {
    word_dict.insert(buf);
    word_vec.push_back(buf);
  }

  vector<string> ret;
  for (auto& word : word_vec) {
    int size = word.size();
    for (int i = 1; i <= size - 1; ++i) {
      if (word_dict.find(word.substr(0, i)) != word_dict.end()
          && word_dict.find(word.substr(i, size - i)) != word_dict.end()) {
        ret.push_back(word);
        break;
      }
    }
  }

  for (auto& word : ret) {
    cout << word << "\n";
  }

  return 0;
}
