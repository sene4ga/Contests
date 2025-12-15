#include <iostream>
#include <vector>

bool Func(std::string& strreal, std::string& pstr, std::vector<int>& index,
          int mid) {
  std::string str = strreal;
  int i = 0;
  int j = 0;
  int sz1 = static_cast<int>(str.size());
  int psz1 = static_cast<int>(pstr.size());
  while (j < psz1) {
    if (index[i] <= mid) {
      str[i] = '0';
    }
    if (i == sz1 && j != psz1) {
      return false;
    }
    if (i == sz1 && j == psz1) {
      return str[i] == pstr[j];
    }
    if (str[i] == pstr[j]) {
      i++;
      j++;
    } else if (str[i] != pstr[j]) {
      i++;
    }
  }
  return true;
}

int main() {
  std::string s1;
  std::string t2;
  std::getline(std::cin, s1);
  std::getline(std::cin, t2);
  int num = static_cast<int>(std::size(s1));
  std::vector<int> pere(num + 1, 0);
  int fire;

  for (int i = 0; i < num; i++) {
    std::cin >> fire;
    pere[fire - 1] = i + 1;
  }

  int left = 0;
  int right = num + 1;
  int mid = -1;
  while (right - left > 1) {
    mid = left + (right - left) / 2;
    if (Func(s1, t2, pere, mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }
  std::cout << left << std::endl;
}
