#include <iostream>
#include <vector>

long long n;
long long k;
const int cX1 = 123;
const int cX2 = 45;
const int cOst = 10000000 + 4321;

void BubbleSort(std::vector<long long>& arr) {
  long long size = static_cast<long long>(arr.size());
  for (long long i = 0; i < size - 1; i++) {
    for (long long j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

long long Getmed(std::vector<long long>& pi) {
  long long r = static_cast<long long>(pi.size());
  if (r < 5) {
    std::vector<long long> temp = pi;
    BubbleSort(temp);
    long long mid_index = (r - 1) / 2;
    return temp[mid_index];
  }
  std::vector<long long> med;
  std::vector<long long> mini(5);
  for (long long i = 0; i < r; i += 5) {
    if (r - i < 5) {
      long long remaining = r - i;
      std::vector<long long> last_group(pi.begin() + i, pi.end());
      BubbleSort(last_group);
      long long mid_index = (remaining - 1) / 2;
      med.push_back(last_group[mid_index]);
    } else {
      for (long long j = 0; j < 5; j++) {
        mini[j] = pi[i + j];
      }
      BubbleSort(mini);
      med.push_back(mini[2]);
    }
  }
  return Getmed(med);
}

std::vector<long long> Pivot(std::vector<long long>& v) {
  long long mid = Getmed(v);
  long long h = static_cast<long long>(v.size());
  std::vector<long long> newmed;

  long long cless = 0;
  long long cequal = 0;
  for (long long l = 0; l < h; l++) {
    if (v[l] < mid) {
      cless++;
    }
    if (v[l] == mid) {
      cequal++;
    }
  }

  if (k < cless) {
    for (long long l = 0; l < h; l++) {
      if (v[l] < mid) {
        newmed.push_back(v[l]);
      }
    }
  } else if (k < cless + cequal) {
    return {mid};
  } else {
    for (long long l = 0; l < h; l++) {
      if (v[l] > mid) {
        newmed.push_back(v[l]);
      }
    }
    k = k - cless - cequal;
  }
  return newmed;
}

long long Quick(std::vector<long long>& h) {
  std::vector<long long> m;
  m = Pivot(h);
  if (static_cast<long long>(m.size()) == 1) {
    return m[0];
  }
  return Quick(m);
}

int main() {
  std::cin >> n >> k;
  k--;

  std::vector<long long> a(n);

  std::cin >> a[0] >> a[1];

  for (long long i = 2; i < n; i++) {
    a[i] = (cX1 * a[i - 1] + cX2 * a[i - 2]) % cOst;
  }
  std::cout << Quick(a);
  return 0;
}
