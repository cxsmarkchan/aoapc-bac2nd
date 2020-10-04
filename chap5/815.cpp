#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef long long ll;

const double unit_area = 10.0 * 10.0;

void solve(int M, int N) {
  int elevations[M][N];
  int max_elevation = 0;
  int min_elevation = 0;
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> elevations[i][j];
      max_elevation = max(elevations[i][j], max_elevation);
      min_elevation = min(elevations[i][j], min_elevation);
    }
  }

  int volume;
  cin >> volume;

  double lo = min_elevation;
  double hi = (volume / (unit_area * M * N)) + max_elevation;
  double percentage = 0.0;
  while (hi - lo > 1e-6) {
    double mid = (lo + hi) / 2;
    // get_volume
    double total_volume = 0.0;
    double flooded = 0.0;
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        if (elevations[i][j] < mid) {
          total_volume += unit_area * (mid - elevations[i][j]);
          flooded += 1.0;
        }
      }
    }

    if (total_volume <= volume) {
      lo = mid;
      percentage = flooded / (M * N) * 100;
    } else hi = mid;
  }

  printf("Water level is %.2f meters.\n", hi);
  printf("%.2f percent of the region is under water.\n", percentage);
  printf("\n");
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif
  int M, N;
  int case_number = 0;
  while ((cin >> M >> N) && M > 0 && N > 0) {
    printf("Region %d\n", ++case_number);
    solve(M, N);
  }
  return 0;
}
