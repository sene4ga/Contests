#include <iostream>
#include <string>
#include <vector>

struct Dann {
  const long long cMin = -2e9 - 1;
  std::vector<std::pair<long long, long long>> heap1;
  std::vector<long long> ind;
}

long long Shift(long long x, Dann& t) {
  while (x > 1 && t.heap1[x].first < t.heap1[x / 2].first) {
    long long id1 = t.heap1[x].second;
    long long id2 = t.heap1[x / 2].second;
    std::swap(t.heap1[x], t.heap1[x / 2]);
    std::swap(t.ind[id1], t.ind[id2]);
    x = x / 2;
  }
  return x;
}

void ShiftDown(long long x, Dann& t) {
  auto n = static_cast<long long>(t.heap1.size()) - 1;
  while (true) {
    long long left = 2 * x;
    long long right = 2 * x + 1;
    long long smallest = x;

    if (left <= n && t.heap1[left].first < t.heap1[smallest].first) {
      smallest = left;
    }
    if (right <= n && t.heap1[right].first < t.heap1[smallest].first) {
      smallest = right;
    }

    if (smallest != x) {
      long long id1 = t.heap1[x].second;
      long long id2 = t.heap1[smallest].second;
      std::swap(t.heap1[x], t.heap1[smallest]);
      std::swap(t.ind[id1], t.ind[id2]);
      x = smallest;
    } else {
      break;
    }
  }
}

void Insert(long long x, long long query_id, Dann& t) {
  t.heap1.emplace_back(x, query_id);
  auto i = static_cast<long long>(t.heap1.size()) - 1;
  t.ind[query_id] = i;
  Shift(i, t);
}

long long GetMin(Dann t) { return t.heap1[1].first; }

void Extract(Dann& t) {
  long long removed_id = t.heap1[1].second;
  t.ind[removed_id] = -1;

  if (t.heap1.size() == 2) {
    t.heap1.pop_back();
    return;
  }

  t.heap1[1] = t.heap1.back();
  t.ind[t.heap1[1].second] = 1;
  t.heap1.pop_back();

  if (t.heap1.size() > 1) {
    ShiftDown(1, t);
  }
}

void Decrease(long long i, long long d, Dann& t) {
  long long pos = t.ind[i];
  if (pos == -1) {
    return;
  }

  t.heap1[pos].first -= d;
  Shift(pos, t);
}

void Fastios() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastios();

  long long n;
  std::cin >> n;
  Dann t;

  t.ind.resize(n + 2, -1);
  t.heap1.emplace_back(t.cMin, -1);

  std::string s;
  for (long long query_num = 1; query_num <= n; query_num++) {
    std::cin >> s;

    if (s == "insert") {
      long long x;
      std::cin >> x;
      Insert(x, query_num, t);
    } else if (s == "getMin") {
      std::cout << GetMin(t) << '\n';
    } else if (s == "extractMin") {
      Extract(t);
    } else if (s == "decreaseKey") {
      long long i;
      long long delta;
      std::cin >> i >> delta;
      Decrease(i, delta, t);
    }
  }
  return 0;
}
