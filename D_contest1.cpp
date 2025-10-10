#include <cstdint>
#include <iostream>
#include <vector>

const uint64_t cBytes = 64 * 8;
const uint64_t cBits = 8;
const uint64_t cRad = 1 << 8;
const uint64_t cMask = cRad - 1;

void LSD(std::vector<uint64_t>& vec) {
  uint64_t n = static_cast<uint64_t>(vec.size());
  if (n == 0) {
    return;
  }
  std::vector<uint64_t> ans(n);

  for (uint64_t exp = 0; exp < cBytes; exp += cBits) {
    std::vector<uint64_t> count(cRad, 0);
    for (uint64_t i = 0; i < n; i++) {
      uint64_t bit = (vec[i] >> exp) & cMask;
      count[bit]++;
    }

    for (uint64_t i = 1; i < cRad; i++) {
      count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
      uint64_t bit = (vec[i] >> exp) & cMask;
      ans[count[bit] - 1] = vec[i];
      count[bit]--;
    }
    vec = ans;
  }
}

int main() {
  uint64_t n;
  std::cin >> n;
  std::vector<uint64_t> arr(n);

  for (uint64_t i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  LSD(arr);

  for (uint64_t i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
}
