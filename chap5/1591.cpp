#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef long long ll;

bool is_valid(ll P, ll Q, ll A, ll B) {
  return ((1LL << A) + 1LL) * P >= (Q << B);
}

ll getK(ll N, ll P, ll Q, ll A, ll B) {
  return ((N - 1) * P * (1LL + (1LL << A)) >> B) + Q;
}

void solve(ll N, ll P, ll Q) {
  ll minK = -1;
  ll minA = -1;
  ll minB = -1;
  for (ll B = 0; B <= 32; ++B) {
    ll A = 0;
    while (!is_valid(P, Q, A, B)) A++;
    ll K = getK(N, P, Q, A, B);
    // cout << "debug: " << A << " " << B << " " << K << endl;
    if (minK < 0 || minK > K || (minK == K && minA > A)) {
      minK = K;
      minA = A;
      minB = B;
    }
  }
  printf("%lld %lld %lld\n", minK, minA, minB);
}

int main() {
#ifdef CXS_DEBUG
  freopen("test.in", "r", stdin);
#endif
  int N, P, Q;
  while (cin >> N >> P >> Q) {
    solve(N, P, Q);
  }
  return 0;
}
