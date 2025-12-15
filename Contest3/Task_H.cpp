#include <algorithm>
#include <iostream>
#include <vector>

long long num = 0;
long long n = 0;
std::vector<long long> coords;

long long Get(long long x) {
  return static_cast<long long>(
      (lower_bound(coords.begin(), coords.end(), x) - coords.begin()));
}

struct Event {
  long long x = 0;
  long long y1 = 0;
  long long y2 = 0;
  long long type = 0;

  Event() = default;
  Event(long long x, long long y1, long long y2, long long type)
      : x(x), y1(y1), y2(y2), type(type) {}
  bool operator<(Event const& other) const { return x < other.x; }
};

struct Point {
  long long count;
  long long length;
};

std::vector<Point> tree;

void Build(long long v, long long l, long long r) {
  if (r - l == 1) {
    tree[v] = {0, 0};
  } else {
    long long mid = (l + r) / 2;
    Build(2 * v, l, mid);
    Build(2 * v + 1, mid, r);
    tree[v] = {0, tree[2 * v].length + tree[2 * v + 1].length};
  }
}

void Upd(long long y1t, long long y2t, long long v, long long l, long long r,
         long long add) {
  if (r <= y1t || l >= y2t) {
    return;
  }

  if (y1t <= l && r <= y2t) {
    tree[v].count += add;
  } else {
    long long mid = (l + r) / 2;
    Upd(y1t, y2t, v * 2, l, mid, add);
    Upd(y1t, y2t, v * 2 + 1, mid, r, add);
  }

  if (tree[v].count > 0) {
    tree[v].length = coords[r] - coords[l];
  } else {
    if (r - l == 1) {
      tree[v].length = 0;
    } else {
      tree[v].length = tree[2 * v].length + tree[2 * v + 1].length;
    }
  }
}

long long Sum() { return tree[1].length; }

bool Cmp(Event a, Event b) { return a < b; }

void Fastios() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastios();
  std::cin >> num;
  std::vector<Event> events(2 * num);

  long long a;
  long long b;
  long long c;
  long long d;
  for (long long i = 0; i < num; i++) {
    std::cin >> a >> b >> c >> d;
    if (c < a) {
      std::swap(a, c);
    }
    if (d < b) {
      std::swap(b, d);
    }
    events[i] = {a, b, d, 1};
    events[num + i] = {c, b, d, -1};
    coords.push_back(b);
    coords.push_back(d);
  }

  sort(coords.begin(), coords.end());
  coords.erase(unique(coords.begin(), coords.end()), coords.end());

  n = static_cast<long long>(coords.size());
  if (n < 2) {
    std::cout << 0;
    return 0;
  }
  long long interval = n - 1;

  tree.resize(4 * n);
  Build(1, 0, interval);

  std::sort(events.begin(), events.end(), &Cmp);

  long long summa = 0;

  for (long long i = 0; i < 2 * num; i++) {
    if (i > 0 && events[i].x != events[i - 1].x) {
      summa += Sum() * (events[i].x - events[i - 1].x);
    }
    Upd(Get(events[i].y1), Get(events[i].y2), 1, 0, interval, events[i].type);
  }

  std::cout << summa;
}
