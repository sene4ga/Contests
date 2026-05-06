#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  long long n;
  std::cin >> n;
  std::vector<long long> v(n);
  for (long long i = 0; i < n; i++) {
    std::cin >> v[i];
  }

  const long long cInf = 1e9;
  std::vector<long long> dp(n + 1, -cInf);
  std::vector<long long> pos(n + 1, -1);
  std::vector<long long> parent(n, -1);
  long long len = 0;

  for (long long i = 0; i < n; i++) {
    long long l = 1;
    long long r = len;
    long long pl = len + 1;
    while (l <= r) {
      long long m = (l + r) / 2;
      if (dp[m] >= v[i]) {
        l = m + 1;
      } else {
        pl = m;
        r = m - 1;
      }
    }
    dp[pl] = v[i];
    pos[pl] = i;

    if (pl > 1) {
      parent[i] = pos[pl - 1];
    }
    len = std::max(len, pl);
  }

  std::vector<long long> ans;
  long long cur = pos[len];

  while (cur != -1) {
    ans.push_back(cur);
    cur = parent[cur];
  }

  std::reverse(ans.begin(), ans.end());

  std::cout << len << "\n";
  for (long long i : ans) {
    std::cout << i + 1 << " ";
  }
}
