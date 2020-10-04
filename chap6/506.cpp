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

const string prefix = "   ";

struct Property {
  int timestamp;
  bool is_explicit;
};

struct System {
  int timestamp = 0;
  unordered_map<string, vector<string>> dependency;
  unordered_map<string, Property> installation;
  unordered_map<string, unordered_set<string>> dependents;

  void add_dependency(const string& program, const string& depend) {
    dependency[program].push_back(depend);
  }

  void install(const string& program, bool is_explicit) {
    if (installation.find(program) != installation.end()) {
      if (is_explicit)
        cout << prefix << program << " is already installed.\n";
      return;
    }

    for (auto& depend : dependency[program]) {
      dependents[depend].insert(program);
      if (installation.find(depend) == installation.end()) {
        install(depend, false);
      }
    }

    cout << prefix << "Installing " << program << "\n";
    installation[program].timestamp = timestamp++;
    installation[program].is_explicit = is_explicit;
  }

  void remove(const string& program, bool is_explicit) {
    if (!dependents[program].empty()) {
      if (is_explicit) {
        cout << prefix << program << " is still needed.\n";
      }
      return;
    }
    if (installation.find(program) == installation.end()) {
      if (is_explicit)
        cout << prefix << program << " is not installed.\n";
      return;
    }
    if (!is_explicit && installation[program].is_explicit) return;

    installation.erase(program);
    cout << prefix << "Removing " << program << "\n";
    for (auto& depend : dependency[program]) {
      dependents[depend].erase(program);
      remove(depend, false);
    }
  }

  void list(bool debug = false) {
    vector<pair<int, string>> installation_by_time;
    for (auto& item : installation) {
      installation_by_time.push_back({item.second.timestamp, item.first});
    }
    sort(installation_by_time.begin(), installation_by_time.end());
    for (auto& item : installation_by_time) {
      cout << prefix;
      if (debug) cout << "DEBUG ";
      cout << item.second << "\n";
    }
  }
};

bool solve() {
  System system;
  char buf[256];
  if (!(cin.getline(buf, 256))) return false;
  if (strlen(buf) == 0) return false;

  do {
    cout << buf << "\n";
    stringstream ss;
    ss << buf;
    switch (buf[0]) {
      case 'D':
        {
          string program;
          ss >> program;
          ss >> program;
          string depend;
          while (ss >> depend) {
            system.add_dependency(program, depend);
          }
        }
        break;
      case 'I':
        {
          string program;
          ss >> program;
          ss >> program;
          system.install(program, true);
          // system.list(true);
        }
        break;
      case 'R':
        {
          string program;
          ss >> program;
          ss >> program;
          system.remove(program, true);
          // system.list(true);
        }
        break;
      case 'L':
        system.list();
        break;
      default:
        break;
    }
  } while (cin.getline(buf, 256) && strcmp(buf, "END") != 0);
  cout << "END\n";

  return true;
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  while (solve());

  return 0;
}
