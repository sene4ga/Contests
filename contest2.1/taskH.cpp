#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  long long ans = 0;

  for (int a = 1; a <= n; ++a) {
    int max_val = 2 * a - 1;
    std::vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for (int x = a + 1; x <= max_val && x <= n; ++x) {
      for (int s = n; s >= x; --s) {
        dp[s] += dp[s - x];
      }
    }
    if (n - a >= 0) {
      ans += dp[n - a];
    }
  }
  std::cout << ans << '\n';
}
