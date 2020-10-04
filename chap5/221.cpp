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

struct Building {
  int id;
  double x;
  double y;
  double width;
  double depth;
  double height;
};

const double eps = 1e-8;

void solve(int N) {
  unordered_map<int, Building> building_map;
  unordered_map<double, unordered_set<int>> in_map;
  unordered_map<double, unordered_set<int>> out_map;
  unordered_set<double> coordinate_set;
  for (int i = 0; i < N; ++i) {
    Building building;
    building.id = i + 1;
    cin >> building.x >> building.y >> building.width >> building.depth >> building.height;
    building_map[building.id] = building;
    in_map[building.x].insert(building.id);
    out_map[building.x + building.width].insert(building.id);
    coordinate_set.insert(building.x);
    coordinate_set.insert(building.x + building.width);
  }

  vector<double> coordinate_vec(coordinate_set.begin(), coordinate_set.end());
  sort(coordinate_vec.begin(), coordinate_vec.end());

  vector<int> current_buildings;
  unordered_set<int> valid_buildings;

  for (auto& coord : coordinate_vec) {
    auto it_out = out_map.find(coord);
    if (it_out != out_map.end()) {
      auto& out_ids = it_out->second;
      int p1 = 0;
      for (int p2 = 0; p2 < current_buildings.size(); ++p2) {
        if (out_ids.find(current_buildings[p2]) == out_ids.end()) {
          current_buildings[p1++] = current_buildings[p2];
        }
      }
      while (current_buildings.size() > p1) current_buildings.pop_back();
    }

    auto it_in = in_map.find(coord);
    if (it_in != in_map.end()) {
      for (auto& id : it_in->second) {
        current_buildings.push_back(id);
      }
    }

    auto cmp_func = [&building_map](int lhs, int rhs) -> bool {
      return building_map[lhs].y < building_map[rhs].y;
    };
    sort(current_buildings.begin(), current_buildings.end(), cmp_func);

    double current_height = 0;
    for (auto& id : current_buildings) {
      if (building_map[id].height > current_height + eps) {
        valid_buildings.insert(id);
      }
      current_height = max(current_height, building_map[id].height);
    }
  }

  vector<int> valid_buildings_vec(valid_buildings.begin(), valid_buildings.end());

  auto display_cmp = [&building_map](int lhs, int rhs) -> bool {
    if (building_map[lhs].x < building_map[rhs].x) return true;
    if (building_map[lhs].x > building_map[rhs].x) return false;

    if (building_map[lhs].y < building_map[rhs].y) return true;
    if (building_map[lhs].y > building_map[rhs].y) return false;

    return lhs < rhs;
  };
  sort(valid_buildings_vec.begin(), valid_buildings_vec.end(), display_cmp);

  for (int i = 0; i < valid_buildings_vec.size(); ++i) {
    if (i > 0) cout << " ";
    cout << valid_buildings_vec[i];
  }
  cout << "\n";
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int N;
  int id = 0;
  while (cin >> N, N > 0) {
    if (id > 0) cout << "\n";
    printf("For map #%d, the visible buildings are numbered as follows:\n", ++id);
    solve(N);
  }

  return 0;
}
