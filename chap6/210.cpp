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

const int ASSIGNMENT = 0;
const int PRINT = 1;
const int LOCK = 2;
const int UNLOCK = 3;
const int END = 4;

struct Statement {
  int type;
  int variable;
  int value;

  Statement(const vector<string>& terms) {
    static unordered_map<string, int> key_to_type = {
      {"lock", LOCK},
      {"unlock", UNLOCK},
      {"end", END}
    };
    if (terms.size() == 3) {
      type = ASSIGNMENT;
      variable = terms[0][0] - 'a';
      stringstream ss;
      ss << terms[2];
      ss >> value;
    } else if (terms.size() == 2) {
      type = PRINT;
      variable = terms[1][0] - 'a';
    } else {
      type = key_to_type[terms[0]];
    }
  }
};

struct Program {
  vector<Statement> statements;
  int pos;

  Program() : pos(0) {}

  void InitFromInput() {
    char buf[256];
    while (true) {
      cin.getline(buf, 256);
      stringstream ss;
      ss << buf;
      vector<string> terms;
      string tmp;
      while (ss >> tmp) {
        terms.push_back(tmp);
      }

      statements.push_back(Statement(terms));
      auto& statement = statements.back();
      if (statement.type == END) break;
    }
  }
};

struct System {
  int variables[26];
  vector<Program> programs;
  bool lock_state;
  deque<int> ready_queue;
  queue<int> block_queue;

  int execution[5];
  int quantum;

  System(int n_program, int* execution_, int quantum_) : lock_state(false), quantum(quantum_) {
    memset(variables, 0, sizeof(variables));
    memcpy(execution, execution_, sizeof(execution));

    for (int i = 0; i < n_program; ++i) {
      AddProgram();
    }
  }

  void AddProgram() {
    programs.push_back(Program());
    auto& program = programs.back();
    program.InitFromInput();
  }

  void Execute() {
    for (int i = 0; i < programs.size(); ++i) ready_queue.push_back(i);

    while (!ready_queue.empty()) {
      int id = ready_queue.front();
      ready_queue.pop_front();

      auto& program = programs[id];
      bool flag = false;
      for (int t = 0; t < quantum;) {
        auto& statement = program.statements[program.pos];
        switch (statement.type) {
          case ASSIGNMENT:
            variables[statement.variable] = statement.value;
            break;
          case PRINT:
            cout << id + 1 << ": " << variables[statement.variable] << "\n";
            // printf("%d: %d\n", id + 1, variables[statement.variable]);
            break;
          case LOCK:
            if (lock_state) {
              block_queue.push(id);
              flag = true;
            } else {
              lock_state = true;
            }
            break;
          case UNLOCK:
            lock_state = false;
            if (!block_queue.empty()) {
              int wait_id = block_queue.front();
              block_queue.pop();
              ready_queue.push_front(wait_id);
            }
            break;
          case END:
            flag = true;
            break;
          default:
            break;
        }
        if (flag) break;
        program.pos++;
        t += execution[statement.type];
      }
      if (!flag) ready_queue.push_back(id);
    }
  }
};

void solve() {
  int n_program;
  int execution[5];
  int quantum;
  cin >> n_program;
  for (int i = 0; i < 5; ++i) {
    cin >> execution[i];
  }
  cin >> quantum;

  char buf[256];
  cin.getline(buf, 255);

  System system(n_program, execution, quantum);
  // system.Display();
  system.Execute();
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    solve();
    if (T > 0) cout << "\n";
  }

  return 0;
}
