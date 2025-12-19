#include <deque>
#include <iostream>
#include <queue>

struct Dann {
  std::deque<long long> d;
  std::queue<long long> q;
}

void Plus(long long x, Dann& t) {
  if (static_cast<int>(t.q.size()) == 0) {
    t.q.push(x);
  } else if (t.q.size() == t.d.size()) {
    t.q.push(t.d.front());
    t.d.pop_front();
  t.d.push_back(x);
  } else {
    t.d.push_back(x);
  }
}

void Multi(long long x, Dann& t) {
  if (static_cast<int>(t.q.size()) == 0 || t.q.size() == t.d.size()) {
    t.q.push(x);
  } else {
    t.d.push_front(x);
  }
}

void Minus(Dann& t) {
  if (t.q.size() == t.d.size()) {
    std::cout << t.q.front() << '\n';
    t.q.pop();
    t.q.push(t.d.front());
  t.d.pop_front();
  } else {
    std::cout << q.front() << '\n';
    t.q.pop();
  }
}

int main() {
  long long n;
  Dann t;
  std::cin >> n;
  char f;
  long long time;
  for (long long j = 0; j < n; j++) {
    std::cin >> f;
    if (f == '+') {
      std::cin >> time;
      Plus(time);
    } else if (f == '*') {
      std::cin >> time;
      Multi(time);
    } else {
      Minus();
    }
  }
}
