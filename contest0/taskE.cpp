#include <algorithm>
#include <iostream>
#include <vector>

void Fastios() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastios();
  int num;
  const int cLeft = 0;
  const int cMax = 1e9;
  std::cin >> num;
  std::vector<int> a1(num + 1, cMax);
  std::vector<int> b1(num + 1, cMax);
  std::vector<int> diff(num + 1, cMax);
  for (int i = 0; i < num; ++i) {
    std::cin >> a1[i];
  }
  for (int i = 0; i < num; ++i) {
    std::cin >> b1[i];
    diff[i] = a1[i] - b1[i];
  }

  int q;
  int x;
  int left = -1;
  int right = -1;
  int mid = -1;
  std::cin >> q;

  for (int i = 0; i < q; ++i) {
    left = cLeft;
    right = num;
    std::cin >> x;
    while (right - left > 1) {
      mid = left + (right - left) / 2;
      if (diff[mid] > -x) {
        right = mid;
      } else {
        left = mid;
      }
    }
    if (std::max(a1[left] + x, b1[left]) > std::max(a1[right] + x, b1[right])) {
      std::cout << right + 1 << '\n';
    } else {
      std::cout << left + 1 << '\n';
    }
  }
}
