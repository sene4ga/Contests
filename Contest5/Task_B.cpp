#include <cstdint>
#include <iostream>
#include <vector>

struct Hash {
  static const int cTab = 6000007;
  static const uint64_t cH1 = 239017;
  static const uint64_t cH2 = 123457;

  std::vector<int64_t> key;
  std::vector<int> cnt;

  Hash() : key(cTab, -1), cnt(cTab, 0) {}

  static int Hash1(int64_t x) {
    return (static_cast<uint64_t>(x) * cH1) % cTab;
  }

  static int Hash2(int64_t x) {
    return 1 + (static_cast<uint64_t>(x) * cH2) % (cTab - 1);
  }

  void Insert(int64_t x) {
    int h1 = Hash1(x);
    int h2 = Hash2(x);
    int ind = h1;

    for (int i = 0;; ++i) {
      if (key[ind] == -1) {
        key[ind] = x;
        cnt[ind] = 1;
        return;
      }
      if (key[ind] == x) {
        ++cnt[ind];
        return;
      }
      ind = (h1 + i * h2) % cTab;
    }
  }

  bool Take(int64_t x) {
    int h1 = Hash1(x);
    int h2 = Hash2(x);
    int ind = h1;

    for (int i = 0; key[ind] != -1; ++i) {
      if (key[ind] == x && cnt[ind] > 0) {
        --cnt[ind];
        return true;
      }
      ind = (h1 + i * h2) % cTab;
    }
    return false;
  }
};

void Fastios() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastios();

  int n;
  std::cin >> n;

  Hash h;
  int64_t x;
  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    h.Insert(x);
  }
  int m;
  std::cin >> m;

  std::vector<int64_t> ans;
  ans.reserve(std::min(n, m));

  for (int i = 0; i < m; ++i) {
    std::cin >> x;
    if (h.Take(x)) {
      ans.push_back(x);
    }
  }

  std::cout << ans.size() << '\n';
  for (auto e : ans) {
    std::cout << e << ' ';
  }
  std::cout << '\n';
}
