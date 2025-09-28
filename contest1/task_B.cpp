#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
  int numbers1;
  int questions;
  const int cComa = 6;
  std::cin >> numbers1;
  const int cNumbers = numbers1 + 1;
  std::vector<long double> array(cNumbers - 1);
  std::vector<long double> pref_mult(cNumbers);
  std::cout << std::fixed << std::setprecision(cComa);

  for (int ind = 0; ind < cNumbers - 1; ++ind) {
    long double fast;
    std::cin >> fast;
    array[ind] = std::log2(fast);
  }

  pref_mult[0] = 1;

  for (int ind = 0; ind < cNumbers - 1; ++ind) {
    pref_mult[ind + 1] = pref_mult[ind] + array[ind];
  }

  std::cin >> questions;
  for (int ind = 0; ind < questions; ++ind) {
    int left;
    int right;
    std::cin >> left >> right;
    std::cout << std::pow(2, (pref_mult[right + 1] - pref_mult[left]) /
                             (right - left + 1))
              << std::endl;
  }
}
