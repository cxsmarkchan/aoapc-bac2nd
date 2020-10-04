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

const char* INDENT = "     ";

struct User {
  string user_name;
  string mta_addr;

  bool InitFromInput() {
    string s;
    cin >> s;
    if (s == "*") return false;

    int split = -1;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '@') {
        split = i;
        break;
      }
    }
    user_name = s.substr(0, split);
    mta_addr = s.substr(split + 1, s.size() - split - 1);
    return true;
  }
};

struct RecvUsers {
  string mta_addr;
  vector<string> users;
};

struct MTA {
  string name;
  unordered_set<string> users;

  void InitFromInput() {
    cin >> name;
    int num_users;
    cin >> num_users;
    for (int i = 0; i < num_users; ++i) {
      string user;
      cin >> user;
      users.insert(user);
    }
  }

  void Send(const string& send_user, const MTA& recv_mta, const vector<string>& recv_users, const vector<string>& data) const {
    SendHello(recv_mta);
    SendMailFrom(recv_mta, send_user);
    bool valid = false;

    unordered_set<string> checked_users;
    for (auto& user : recv_users) {
      if (checked_users.find(user) != checked_users.end())
        continue;
      checked_users.insert(user);
      valid = SendRcptTo(recv_mta, user) || valid;
    }
    if (valid)
      SendData(recv_mta, data);
    SendQuit(recv_mta);
  }

  void SendHello(const MTA& recv) const {
    cout << INDENT << "HELO " << name << "\n";
    cout << INDENT << recv.RecvHello(name) << "\n";
  }

  void SendMailFrom(const MTA& recv, const string& user_send) const {
    cout << INDENT << "MAIL FROM:<" << user_send << "@" << name << ">\n";
    cout << INDENT << recv.RecvMailFrom(name, user_send) << "\n";
  }

  bool SendRcptTo(const MTA& recv, const string& user_recv) const {
    cout << INDENT << "RCPT TO:<" << user_recv << "@" << recv.name << ">\n";
    int code = recv.RecvRcptTo(user_recv);
    cout << INDENT << code << "\n";
    return code == 250;
  }

  void SendData(const MTA& recv, const vector<string>& data) const {
    cout << INDENT << "DATA\n";
    cout << INDENT << recv.RecvDataBefore() << "\n";
    for (auto& line : data) {
      cout << INDENT << line << "\n";
    }
    cout << INDENT << ".\n";
    cout << INDENT << recv.RecvDataAfter(data) << "\n";
  }

  void SendQuit(const MTA& recv) const {
    cout << INDENT << "QUIT\n";
    cout << INDENT << recv.RecvQuit() << "\n";
  }

  int RecvHello(const string& send_mta_name) const {
    return 250;
  }

  int RecvMailFrom(const string& send_mta_name, const string& send_user_name) const {
    return 250;
  }

  int RecvRcptTo(const string& recv_user_name) const {
    auto it = users.find(recv_user_name);
    if (it == users.end()) return 550;
    else return 250;
  }

  int RecvDataBefore() const {
    return 354;
  }

  int RecvDataAfter(const vector<string>& data) const {
    return 250;
  }

  int RecvQuit() const {
    return 221;
  }
};

unordered_map<string, MTA> map_mta;

void ReadMTA() {
  string op;
  while (cin >> op, op == "MTA") {
    MTA mta;
    mta.InitFromInput();
    map_mta[mta.name] = move(mta);
  }
}

void Process() {
  while (true) {
    User send;
    vector<RecvUsers> recv_users;
    unordered_map<string, int> recv_user_map;
    if (!send.InitFromInput()) break;
    User recv_user;
    while (recv_user.InitFromInput()) {
      auto it = recv_user_map.find(recv_user.mta_addr);
      if (it == recv_user_map.end()) {
        recv_users.push_back({recv_user.mta_addr, {}});
        recv_user_map[recv_user.mta_addr] = recv_users.size() - 1;
        it = recv_user_map.find(recv_user.mta_addr);
      }
      recv_users[it->second].users.push_back(recv_user.user_name);
    }

    char buf[200];
    cin.getline(buf, 100);
    vector<string> data;
    while (true) {
      cin.getline(buf, 100);
      if (strcmp(buf, "*") == 0) break;
      data.push_back(string(buf));
    }

    for (auto& recv_info : recv_users) {
      cout << "Connection between " << send.mta_addr << " and " << recv_info.mta_addr << "\n";
      map_mta[send.mta_addr].Send(send.user_name, map_mta[recv_info.mta_addr], recv_info.users, data);
    }
  }
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  ReadMTA();
  Process();

  return 0;
}
