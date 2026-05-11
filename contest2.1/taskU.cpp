#include <iostream>
#include <string>
#include <vector>

bool Podmn(long long i, long long x) { return (i & x) == i; }

int main() {
  long long n;
  std::cin >> n;
  long long n1 = n / 2;
  long long n2 = n - n1;
  std::vector<long long> neigbours(n);
  std::vector<bool> clique(1LL << n1);
  std::vector<int> subclique(1LL << n2);
  std::vector<int> corr(1LL << n1);

  for (int i = 0; i < n; i++) {
    long long mask = 0;
    std::string row;
    std::cin >> row;
    for (int j = 0; j < n; j++) {
      if (row[j] == '1') {
        mask |= (1LL << j);
      }
    }
    neigbours[i] = mask;
  }

  subclique[0] = 1;
  long long v = 1;
  int st = 1;
  for (long long i = 1; i < (1LL << n2); i++) {
    if (i == (1LL << st)) {
      v = (1LL << st++);
    }
    long long neigh_b = (neigbours[n1 + (st - 1)] >> n1);
    if (subclique[i - v] == 1 && Podmn(i - v, neigh_b)) {
      subclique[i] = 1;
    } else {
      subclique[i] = 0;
    }
  }

  for (int j = 0; j < n2; j++) {
    for (long long i = 0; i < (1LL << n2); i++) {
      if ((i & (1LL << j)) != 0) {
        subclique[i] += subclique[i ^ (1LL << j)];
      }
    }
  }

  clique[0] = true;
  corr[0] = (1LL << n2) - 1;
  long long ans = subclique[corr[0]];
  v = 1;
  st = 1;
  for (long long i = 1; i < (1LL << n1); i++) {
    if (i == (1LL << st)) {
      v = (1LL << st++);
    }
    long long neigh_a = (neigbours[st - 1] & ((1LL << n1) - 1));
    long long neigh_b = (neigbours[st - 1] >> n1);
    if (clique[i - v] && Podmn(i - v, neigh_a)) {
      clique[i] = true;
      corr[i] = corr[i - v] & neigh_b;
      ans += subclique[corr[i]];
    } else {
      clique[i] = false;
    }
  }
  std::cout << ans << std::endl;
}
