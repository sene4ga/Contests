#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int cInf = 1e9;

int main() {
  std::string u;
  std::string v;
  std::getline(std::cin, u);
  std::getline(std::cin, v);
  int k;
  std::cin >> k;

  int n = u.size();
  int m = v.size();
  if (std::abs(n - m) > k) {
    std::cout << -1;
    return 0;
  }

  std::vector dp(n + 1, std::vector(m + 1, std::vector<int>(k + 1, cInf)));

  dp[0][0][0] = 0;

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      for (int t = 0; t <= k; ++t) {
        if (dp[i][j][t] == cInf) {
          continue;
        }
        int cur = dp[i][j][t];

        if (i < n && t + 1 <= k) {
          dp[i + 1][j][t + 1] = std::min(dp[i + 1][j][t + 1], cur);
        }

        if (j < m && t + 1 <= k) {
          dp[i][j + 1][t + 1] = std::min(dp[i][j + 1][t + 1], cur);
        }

        if (i < n && j < m) {
          if (u[i] == v[j]) {
            dp[i + 1][j + 1][t] = std::min(dp[i + 1][j + 1][t], cur);
          } else {
            dp[i + 1][j + 1][t] = std::min(dp[i + 1][j + 1][t], cur + 1);

            if (t + 1 <= k) {
              dp[i + 1][j + 1][t + 1] = std::min(dp[i + 1][j + 1][t + 1], cur);
            }
          }
        }
      }
    }
  }

  int answer = cInf;

  for (int t = 0; t <= k; ++t) {
    answer = std::min(answer, dp[n][m][t]);
  }

  if (answer == cInf) {
    std::cout << -1;
  } else {
    std::cout << answer;
  }
}
