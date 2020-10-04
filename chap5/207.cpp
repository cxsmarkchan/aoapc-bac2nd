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

const int N_FINAL = 70;
const int MAX_SCORE = 10000;
const double eps = 1e-8;


const char* FIRST_LINE = "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won";
const char* SECOND_LINE = "-----------------------------------------------------------------------";

struct Player {
  Player(const char* input) : amateur(false) {
    for (int i = 0; i < 21; ++i) {
      name[i] = input[i];
      if (name[i] == '*') amateur = true;
    }
    name[21] = 0;
    for (int i = 0; i < 4; ++i) {
      scores[i] = GetScore(input, 21 + 3 * i);
    }
  }

  static int GetScore(const char* input, int pos) {
    if (strlen(input) <= pos) return MAX_SCORE;
    if (input[pos] == 'D' || input[pos] == ' ') return MAX_SCORE;
    return (input[pos] - '0') * 10 + input[pos + 1] - '0';
  }

  int GetScore1() const {
    return scores[0] + scores[1];
  }

  int GetScore2() const {
    int total_score = 0;
    for (int i = 0; i < 4; ++i) {
      total_score += scores[i];
    }
    return total_score;
  }

  void Display() const {
    printf("%s", name);

    int total_score = GetScore2();
    if (total_score >= MAX_SCORE)
      printf("          ");
    else {
      int tmp_rank = rank;
      int digits = 0;
      while (tmp_rank > 0) {
        digits++;
        tmp_rank /= 10;
      }
      printf("%d", rank);
      if (tie) {
        printf("T");
        digits++;
      }
      for (int i = digits; i < 10; ++i) {
        printf(" ");
      }
    }

    for (int i = 0; i < 4; ++i) {
      if (scores[i] >= MAX_SCORE) {
        printf("     ");
      } else {
        printf("%-5d", scores[i]);
      }
    }
    if (total_score >= MAX_SCORE)
      printf("DQ");
    else {
      if (money >= 0)
        printf("%-9d $%9.2f", total_score, (money + eps));
      else
        printf("%-3d", total_score);
    }

    printf("\n");
  }

  char name[22];
  int scores[4];
  bool amateur;

  double money = -1;
  int rank = -1;
  bool tie = false;
};

bool PlayerCmp1(const Player& lhs, const Player& rhs) {
  return lhs.GetScore1() < rhs.GetScore1();
}

bool PlayerCmp2(const Player& lhs, const Player& rhs) {
  int lhs_score = lhs.GetScore2();
  int rhs_score = rhs.GetScore2();
  if (lhs_score < rhs_score) return true;
  if (rhs_score < lhs_score) return false;
  return strcmp(lhs.name, rhs.name) < 0;
}

void MakeTheCut(vector<Player>& players) {
  int N = players.size();
  int i = min(N, N_FINAL) - 1;
  while (players[i].GetScore1() >= MAX_SCORE) i--;
  while (i < N - 1 && players[i].GetScore1() == players[i + 1].GetScore1()) i++;
  while (players.size() > i + 1) players.pop_back();
}

void AllocateMoney(vector<Player>& players, double total_prize, double* percentage) {
  int p1 = 0, p2 = 0;
  int current_score = players[p1].GetScore2();
  int next_prize_pos = 0;
  double current_percentage = 0.0;
  int num_players = 0;

  bool has_money = true;
  for (p2 = 0; p2 < players.size(); ++p2) {
    int score = players[p2].GetScore2();

    if (score >= MAX_SCORE) break;

    if (score == current_score) {
      if (!players[p2].amateur) {
        num_players++;
        if (next_prize_pos < N_FINAL)
          current_percentage += percentage[next_prize_pos++];
      }
    } else {
      for (int i = p1; i < p2; ++i) {
        players[i].rank = p1 + 1;

        if (has_money && !players[i].amateur) {
          if (num_players > 1)
            players[i].tie = true;
          players[i].money = total_prize * current_percentage / 100 / num_players;
        }
      }

      p1 = p2;
      num_players = 0;
      current_percentage = 0.0;
      current_score = score;
      if (next_prize_pos >= N_FINAL) has_money = false;
      if (!players[p2].amateur) {
        num_players++;
        if (next_prize_pos < N_FINAL)
          current_percentage += percentage[next_prize_pos++];
      }
    }
  }

  for (int i = p1; i < p2; ++i) {
    players[i].rank = p1 + 1;
    if (players[i].amateur) continue;
    if (!has_money) continue;

    if (num_players > 1)
      players[i].tie = true;
    players[i].money = total_prize * current_percentage / 100 / num_players;
  }
}

void solve() {
  double total_prize;
  double percentage[N_FINAL];
  cin >> total_prize;
  for (int i = 0; i < N_FINAL; ++i) cin >> percentage[i];

  int num_players;
  cin >> num_players;
  vector<Player> players;
  char buf[100];
  cin.getline(buf, 99);
  for (int i = 0; i < num_players; ++i) {
    cin.getline(buf, 99);
    players.push_back(Player(buf));
  }

  sort(players.begin(), players.end(), PlayerCmp1);
  MakeTheCut(players);
  sort(players.begin(), players.end(), PlayerCmp2);

  AllocateMoney(players, total_prize, percentage);

  printf("%s\n", FIRST_LINE);
  printf("%s\n", SECOND_LINE);
  for (int i = 0; i < players.size(); ++i) {
    players[i].Display();
  }
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {
    solve();
    if (T > 0)
      printf("\n");
  }

  return 0;
}
