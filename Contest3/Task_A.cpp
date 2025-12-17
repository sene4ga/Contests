#include <algorithm>
#include <iostream>
#include <vector>

void Fastios() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastios();
  long long n;
  long long q;
  const long long cMax = 2e9;
  std::vector<long long> vec;
  std::vector<std::vector<std::pair<long long, long long>>> sparce;
  std::cin >> n >> q;
  vec.resize(n + 1, cMax);
  std::vector<long long> deg(n + 1);

  deg[1] = 0;
  long long h = 2;
  for (long long i = 2; i < n + 1; i++) {
    if (i == h) {
      deg[i] = deg[i - 1] + 1;
      h <<= 1;
    } else {
      deg[i] = deg[i - 1];
    }
  }

  sparce.resize(deg[n] + 1);
  sparce[0].resize(n, {cMax, cMax});

  for (long long i = 0; i < n; i++) {
    std::cin >> vec[i];
  }
  for (long long i = 0; i < n; i++) {
    sparce[0][i] = {i, n};
  }

  long long k = 2;
  long long p = 1;
  while (k <= n) {
    sparce[p].resize(n - k + 1);
    for (long long i = 0; i + k <= n; i++) {
      long long j = i + (k >> 1);

      auto l = sparce[p - 1][i];
      auto r = sparce[p - 1][j];

      std::vector<long long> cand = {l.first, l.second, r.first, r.second};

      std::sort(cand.begin(), cand.end());
      cand.erase(std::unique(cand.begin(), cand.end()), cand.end());

      long long best1 = n;
      long long best2 = n;
      for (auto idx : cand) {
        if (vec[idx] < vec[best1]) {
          best2 = best1;
          best1 = idx;
        } else if (idx != best1 && vec[idx] < vec[best2]) {
          best2 = idx;
        }
      }

      sparce[p][i] = {best1, best2};
    }
    p += 1;
    k <<= 1;
  }

  long long l;
  long long r;
  for (long long i = 0; i < q; i++) {
    std::cin >> l >> r;
    l--;
    r--;
    long long otr = deg[r - l + 1];

    auto a = sparce[otr][l];
    auto b = sparce[otr][r - (1 << otr) + 1];

    std::vector<long long> cand = {a.first, a.second, b.first, b.second};
    std::sort(cand.begin(), cand.end());
    cand.erase(std::unique(cand.begin(), cand.end()), cand.end());

    long long best1 = n;
    long long best2 = n;
    for (auto idx : cand) {
      if (vec[idx] < vec[best1]) {
        best2 = best1;
        best1 = idx;
      } else if (idx != best1 && vec[idx] < vec[best2]) {
        best2 = idx;
      }
    }
    std::cout << vec[best2] << '\n';
  }
}
