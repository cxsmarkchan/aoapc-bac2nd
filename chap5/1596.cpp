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

bool is_array_name(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

bool is_positive_digit(char c) {
  return c >= '1' && c <= '9';
}

unordered_map<char, int> size_map;
unordered_map<char, unordered_map<int, int>> value_map;

bool get_expression(const char* buf, int& pos, int& expression);
bool get_array_and_pos(const char* buf, int& pos, char& array_name, int& array_pos);

void get_number(const char* buf, int& pos, int& number) {
  number = 0;
  while (buf[pos] != 0 && is_digit(buf[pos])) {
    number *= 10;
    number += (buf[pos++] - '0');
  }
}

bool get_expression(const char* buf, int& pos, int& number) {
  if (is_digit(buf[pos])) {
    get_number(buf, pos, number);
  } else {
    char array_name;
    int array_pos;
    if (!get_array_and_pos(buf, pos, array_name, array_pos)) return false;
    auto& array = value_map[array_name];
    auto it_pos = array.find(array_pos);
    if (it_pos == array.end())  return false;
    number = it_pos->second;
  }
  return true;
}

bool get_array_and_pos(const char* buf, int& pos, char& array_name, int& array_pos) {
  if (!is_array_name(buf[pos])) return false;

  array_name = buf[pos++];
  if (buf[pos++] != '[') return false;
  if (!get_expression(buf, pos, array_pos)) return false;
  if (buf[pos++] != ']') return false;

  return true;
}

int solve() {
  size_map.clear();
  value_map.clear();

  char buf[255];

  int line = 0;
  int bug_line = 0;
  while (cin.getline(buf, 255), buf[0] != '.') {
    line++;
    if (bug_line > 0) continue;
    char array_name;
    int array_pos;
    int pos = 0;
    if (!get_array_and_pos(buf, pos, array_name, array_pos)) {
      bug_line = line;
      continue;
    }

    if (buf[pos++] != '=') {
      size_map[array_name] = array_pos;
    } else {
      if (array_pos >= size_map[array_name]) {
        bug_line = line;
        continue;
      }
      int number;
      if (!get_expression(buf, pos, number)) {
        bug_line = line;
        continue;
      }
      value_map[array_name][array_pos] = number;
    }
  }
  return line > 0 ? bug_line : -1;
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int line = 0;
  while (line = solve(), line >= 0) {
    cout << line << "\n";
  }
  return 0;
}
