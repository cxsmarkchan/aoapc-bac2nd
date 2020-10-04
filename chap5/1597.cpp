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

vector<int> to_array(const unordered_set<int>& input) {
  vector<int> ret(input.begin(), input.end());
  sort(ret.begin(), ret.end());
  return ret;
}

struct Document {
  vector<string> lines;
  unordered_map<string, unordered_set<int>> line_inverted;

  void display(const unordered_set<int>& line_ids) const {
    vector<int> line_display = to_array(line_ids);
    for (auto& line_id : line_display) {
      cout << lines[line_id] << "\n";
    }
  }

  void display(const string& term) const {
    auto it = line_inverted.find(term);
    if (it == line_inverted.end()) return;
    display(it->second);
  }

  void display(const string& term1, const string& term2) const {
    unordered_set<int> line_ids;
    auto it1 = line_inverted.find(term1);
    if (it1 != line_inverted.end()) {
      for (auto& line_id : it1->second) {
        line_ids.insert(line_id);
      }
    }
    auto it2 = line_inverted.find(term2);
    if (it2 != line_inverted.end()) {
      for (auto& line_id : it2->second) {
        line_ids.insert(line_id);
      }
    }
    display(line_ids);
  }

  void display_all() const {
    for (auto& line : lines) {
      cout << line << "\n";
    }
  }
};

vector<Document> docs;
unordered_map<string, unordered_set<int>> doc_inverted;

char to_letter(char c) {
  if (c >= 'a' && c <= 'z') return c;
  if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
  return 0;
}

void add_doc() {
  char buf[256];

  docs.push_back(Document());
  auto& doc = docs.back();
  int doc_id = docs.size() - 1;

  while (cin.getline(buf, 255), strcmp(buf, "**********") != 0) {
    doc.lines.push_back(string(buf));
    int line_id = doc.lines.size() - 1;

    string word;
    for (int i = 0; buf[i] != 0; ++i) {
      char c = to_letter(buf[i]);
      if (c != 0) {
        word.push_back(c);
      } else {
        if (word.size() > 0) {
          doc.line_inverted[word].insert(line_id);
          doc_inverted[word].insert(doc_id);
        }
        word.clear();
      }
    }
    if (word.size() > 0) {
      doc.line_inverted[word].insert(line_id);
      doc_inverted[word].insert(doc_id);
    }
  }
}

unordered_set<int> process_one_term(const string& term) {
  auto it = doc_inverted.find(term);
  if (it == doc_inverted.end()) return {};
  return it->second;
}

unordered_set<int> process_and(const string& term1, const string& term2) {
  auto doc_set1 = process_one_term(term1);
  auto doc_set2 = process_one_term(term2);
  unordered_set<int> ret;
  for (auto& doc : doc_set1) {
    if (doc_set2.find(doc) != doc_set2.end()) {
      ret.insert(doc);
    }
  }
  return ret;
}

unordered_set<int> process_or(const string& term1, const string& term2) {
  auto doc_set1 = process_one_term(term1);
  auto doc_set2 = process_one_term(term2);
  for (auto& doc : doc_set2) {
    doc_set1.insert(doc);
  }
  return doc_set1;
}

unordered_set<int> process_not(const string& term) {
  auto doc_set = process_one_term(term);
  unordered_set<int> ret;
  for (int i = 0; i < docs.size(); ++i) {
    if (doc_set.find(i) == doc_set.end()) ret.insert(i);
  }
  return ret;
}

void display_fail() {
  cout << "Sorry, I found nothing.\n";
}

void process_query() {
  char buf[256];
  cin.getline(buf, 255);
  vector<string> terms;
  stringstream ss;
  ss << buf;
  string tmp;
  while (ss >> tmp) {
    terms.push_back(tmp);
  }
  switch (terms.size()) {
    case 1:
      {
        auto doc_ids = to_array(process_one_term(terms[0]));
        if (doc_ids.empty()) display_fail();
        for (int i = 0; i < doc_ids.size(); ++i) {
          if (i > 0) cout << "----------\n";
          docs[doc_ids[i]].display(terms[0]);
        }
      }
      break;
    case 2:
      {
        auto doc_ids = to_array(process_not(terms[1]));
        if (doc_ids.empty()) display_fail();
        for (int i = 0; i < doc_ids.size(); ++i) {
          if (i > 0) cout << "----------\n";
          docs[doc_ids[i]].display_all();
        }
      }
      break;
    case 3:
      {
        auto func = terms[1] == "AND" ? process_and : process_or;
        auto doc_ids = to_array(func(terms[0], terms[2]));
        if (doc_ids.empty()) display_fail();
        for (int i = 0; i < doc_ids.size(); ++i) {
          if (i > 0) cout << "----------\n";
          docs[doc_ids[i]].display(terms[0], terms[2]);
        }
      }
      break;
  }
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  char buf[256];

  int n_docs;
  int n_queries;

  cin >> n_docs;
  cin.getline(buf, 256);

  for (int i = 0; i < n_docs; ++i) {
    add_doc();
  }

  cin >> n_queries;
  cin.getline(buf, 256);
  for (int i = 0; i < n_queries; ++i) {
    process_query();
    cout << "==========\n";
  }

  return 0;
}
