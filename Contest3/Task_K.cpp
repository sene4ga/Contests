#include <algorithm>
#include <iostream>
#include <vector>

long long Get(long long x, std::vector<long long>& coords;) {
  return static_cast<long long>(
      (upper_bound(coords.begin(), coords.end(), x) - coords.begin()));
};

struct Fenwick {
 private:
  std::vector<long long> v_;
  long long n_;
 
 public:
  Fenwick() : n_(0) {}
  Fenwick(long long n) : v_(n + 1), n_(n) {}
  void Change(long long x, long long val) {
    for (long long i = x; i <= n_; i += i & -i) {
      v_[i] += val;
    }
  }

  long long Sum(long long x) {
    long long s = 0;
    for (long long i = x; i > 0; i -= i & -i) {
      s += v_[i];
    }
    return s;
  }

  long long& operator[](long long i) { return v_[i]; }
};

struct Fenwickfenwick {
 private:
  std::vector<Fenwick> vec_;
  std::vector<std::vector<long long>> ys_;
  long long ni_;

 public:
  Fenwickfenwick(long long n) : vec_(n + 1), ys_(n + 1), ni_(n) {}

  void Build(
      std::vector<std::pair<std::pair<long long, long long>, long long>>& seg) {
    for (auto& p : seg) {
      long long xi = Get(p.first.first);
      long long yv = Get(p.first.second);
      for (long long j = xi; j <= ni_; j += j & -j) {
        ys_[j].push_back(yv);
      }
    }
    for (long long j = 1; j <= ni_; ++j) {
      sort(ys_[j].begin(), ys_[j].end());
      ys_[j].erase(unique(ys_[j].begin(), ys_[j].end()), ys_[j].end());
      vec_[j] = Fenwick(static_cast<long long>(ys_[j].size()));
    }
  }

  void Change(long long x, long long y, long long val) {
    for (long long i = x; i <= ni_; i += i & -i) {
      long long pos =
          static_cast<long long>(lower_bound(ys_[i].begin(), ys_[i].end(), y) -
                                 ys_[i].begin()) +
          1;
      vec_[i].Change(pos, val);
    }
  }

  long long Sum(long long x1, long long y1) {
    long long s = 0;
    for (long long i = x1; i > 0; i -= i & -i) {
      long long pos = static_cast<long long>(
          upper_bound(ys_[i].begin(), ys_[i].end(), y1) - ys_[i].begin());
      s += vec_[i].Sum(pos);
    }
    return s;
  }
};

void Fastios() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastios();

  long long q;
  long long num = 0;
  
  std::cin >> num;
  std::vector<std::pair<std::pair<long long, long long>, long long>> otr(num);
  std::vector<long long> coords;

  for (long long i = 0; i < num; i++) {
    std::cin >> otr[i].first.first >> otr[i].first.second >> otr[i].second;
  }

  for (const auto& seg : otr) {
    coords.push_back(seg.first.first);
    coords.push_back(seg.first.second);
  }
  sort(coords.begin(), coords.end());
  coords.erase(unique(coords.begin(), coords.end()), coords.end());

  Fenwickfenwick fenw(static_cast<long long>(coords.size()));
  fenw.Build(otr);
  for (auto& p : otr) {
    fenw.Change(Get(p.first.first), Get(p.first.second), p.second);
  }

  std::cin >> q;

  std::string s;
  long long x;
  long long y;
  long long ind;
  long long w;
  for (long long i = 0; i < q; i++) {
    std::cin >> s;
    if (s == "get") {
      std::cin >> x >> y;
      std::cout << fenw.Sum(Get(x), Get(y)) << '\n';
    } else {
      std::cin >> ind >> w;
      ind--;
      fenw.Change(Get(otr[ind].first.first), Get(otr[ind].first.second),
                  w - otr[ind].second);
      otr[ind].second = w;
    }
  }
}
