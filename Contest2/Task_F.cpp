#include <iostream>
#include <stack>

std::stack<std::pair<long long, long long>> in;
std::stack<std::pair<long long, long long>> out;

void Put(long long x) {
  std::cout << "ok" << '\n';
  if (in.empty()) {
    in.push({x, x});
    return;
  }
  in.push({x, std::min(in.top().second, x)});
}

void Del() {
  if (in.empty() && out.empty()) {
    std::cout << "error" << '\n';
    return;
  }
  if (out.empty()) {
    while (!in.empty()) {
      if (out.empty()) {
        out.push({in.top().first, in.top().first});
      } else {
        out.push({in.top().first, std::min(out.top().second, in.top().first)});
      }
      in.pop();
    }
  }
  std::cout << out.top().first << '\n';
  out.pop();
}

void Front() {
  if (in.empty() && out.empty()) {
    std::cout << "error" << '\n';
    return;
  }
  if (out.empty()) {
    while (!in.empty()) {
      if (out.empty()) {
        out.push({in.top().first, in.top().first});
      } else {
        out.push({in.top().first, std::min(out.top().second, in.top().first)});
      }
      in.pop();
    }
  }
  std::cout << out.top().first << '\n';
}

void Size() { std::cout << static_cast<int>(in.size() + out.size()) << '\n'; }

void Cl() {
  std::cout << "ok\n";
  while (!in.empty()) {
    in.pop();
  }
  while (!out.empty()) {
    out.pop();
  }
}

void Min() {
  if (in.empty() && out.empty()) {
    std::cout << "error" << '\n';
    return;
  }
  if (out.empty()) {
    std::cout << in.top().second << '\n';
  } else if (in.empty()) {
    std::cout << out.top().second << '\n';
  } else {
    std::cout << std::min(out.top().second, in.top().second) << '\n';
  }
}

int main() {
  long long n;
  std::cin >> n;
  std::string f;
  long long time;
  for (long long j = 0; j < n; j++) {
    std::cin >> f;
    if (f == "enqueue") {
      std::cin >> time;
      Put(time);
    } else if (f == "dequeue") {
      Del();
    } else if (f == "front") {
      Front();
    } else if (f == "size") {
      Size();
    } else if (f == "clear") {
      Cl();
    } else {
      Min();
    }
  }
}
