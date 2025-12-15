#include <iostream>
#include <string>
#include <vector>

const long long cMin = -2e9 - 1;

std::vector<std::pair<long long, long long>> heap1;
std::vector<long long> ind;

long long Shift(long long x) {
  while (x > 1 && heap1[x].first < heap1[x / 2].first) {
    long long id1 = heap1[x].second;
    long long id2 = heap1[x / 2].second;
    std::swap(heap1[x], heap1[x / 2]);
    std::swap(ind[id1], ind[id2]);
    x = x / 2;
  }
  return x;
}

void ShiftDown(long long x) {
  auto n = static_cast<long long>(heap1.size()) - 1;
  while (true) {
    long long left = 2 * x;
    long long right = 2 * x + 1;
    long long smallest = x;

    if (left <= n && heap1[left].first < heap1[smallest].first) {
      smallest = left;
    }
    if (right <= n && heap1[right].first < heap1[smallest].first) {
      smallest = right;
    }

    if (smallest != x) {
      long long id1 = heap1[x].second;
      long long id2 = heap1[smallest].second;
      std::swap(heap1[x], heap1[smallest]);
      std::swap(ind[id1], ind[id2]);
      x = smallest;
    } else {
      break;
    }
  }
}

void Insert(long long x, long long query_id) {
  heap1.emplace_back(x, query_id);
  auto i = static_cast<long long>(heap1.size()) - 1;
  ind[query_id] = i;
  Shift(i);
}

long long GetMin() { return heap1[1].first; }

void Extract() {
  long long removed_id = heap1[1].second;
  ind[removed_id] = -1;

  if (heap1.size() == 2) {
    heap1.pop_back();
    return;
  }

  heap1[1] = heap1.back();
  ind[heap1[1].second] = 1;
  heap1.pop_back();

  if (heap1.size() > 1) {
    ShiftDown(1);
  }
}

void Decrease(long long i, long long d) {
  long long pos = ind[i];
  if (pos == -1) {
    return;
  }

  heap1[pos].first -= d;
  Shift(pos);
}

void Fastios() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastios();

  long long n;
  std::cin >> n;

  ind.resize(n + 2, -1);
  heap1.emplace_back(cMin, -1);

  std::string s;
  for (long long query_num = 1; query_num <= n; query_num++) {
    std::cin >> s;

    if (s == "insert") {
      long long x;
      std::cin >> x;
      Insert(x, query_num);
    } else if (s == "getMin") {
      std::cout << GetMin() << '\n';
    } else if (s == "extractMin") {
      Extract();
    } else if (s == "decreaseKey") {
      long long i;
      long long delta;
      std::cin >> i >> delta;
      Decrease(i, delta);
    }
  }
  return 0;
}
