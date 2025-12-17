#include <deque>
#include <iostream>
#include <queue>

std::deque<long long> d;
std::queue<long long> q;

void Plus(long long x) {
  if (static_cast<int>(q.size()) == 0) {
    q.push(x);
  } else if (q.size() == d.size()) {
    q.push(d.front());
    d.pop_front();
    d.push_back(x);
  } else {
    d.push_back(x);
  }
}

void Multi(long long x) {
  if (static_cast<int>(q.size()) == 0 || q.size() == d.size()) {
    q.push(x);
  } else {
    d.push_front(x);
  }
}

void Minus() {
  if (q.size() == d.size()) {
    std::cout << q.front() << '\n';
    q.pop();
    q.push(d.front());
    d.pop_front();
  } else {
    std::cout << q.front() << '\n';
    q.pop();
  }
}

int main() {
  long long n;
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
