#include <iostream>
#include <stack>

std::stack<std::pair<long long, long long>> in;
std::stack<std::pair<long long, long long>> out;

void Put(long long x, std::stack<std::pair<long long, long long>>& in, std::stack<std::pair<long long, long long>>& out) {
  std::cout << "ok" << '\n';
  if (in.empty()) {
    in.push({x, x});
    return;
  }
  in.push({x, std::min(in.top().second, x)});
}

void Del(std::stack<std::pair<long long, long long>>& in, std::stack<std::pair<long long, long long>>& out) {
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

void Front(std::stack<std::pair<long long, long long>>& in, std::stack<std::pair<long long, long long>>& out) {
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

void Size(std::stack<std::pair<long long, long long>>& in, std::stack<std::pair<long long, long long>>& out){
  std::cout << static_cast<int>(in.size() + out.size()) << '\n';
}

void Cl(std::stack<std::pair<long long, long long>>& in, std::stack<std::pair<long long, long long>>& out) {
  std::cout << "ok\n";
  while (!in.empty()) {
    in.pop();
  }
  while (!out.empty()) {
    out.pop();
  }
}

void Min(std::stack<std::pair<long long, long long>>& in, std::stack<std::pair<long long, long long>>& out) {
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
  std::stack<std::pair<long long, long long>> in;
  std::stack<std::pair<long long, long long>> out;
  std::cin >> n;
  std::string f;
  long long time;
  for (long long j = 0; j < n; j++) {
    std::cin >> f;
    if (f == "enqueue") {
      std::cin >> time;
      Put(time, in, out);
    } else if (f == "dequeue") {
      Del(in, out);
    } else if (f == "front") {
      Front(in, out);
    } else if (f == "size") {
      Size(in, out);
    } else if (f == "clear") {
      Cl(in, out);
    } else {
      Min(in, out);
    }
  }
}
