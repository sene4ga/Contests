#include <iostream>
#include <vector>

struct Hash {
  static const int cTab = 1000003;
  std::vector<int> tab;
  std::vector<bool> eras;
  int cou;

  static int Hash1(int key) { return key % cTab; }
  static int Hash2(int key) { return 1 + (key % (cTab - 1)); }

  Hash() : tab(cTab, -1), eras(cTab, false), cou(0) {}

  bool Insert(int key) {
    int h1 = Hash1(key);
    int h2 = Hash2(key);
    int ind = h1;
    int dind = -1;

    for (int i = 0; i < cTab; i++) {
      if (tab[ind] == -1) {
        if (dind != -1) {
          tab[dind] = key;
          eras[dind] = false;
        } else {
          tab[ind] = key;
        }
        cou++;
        return true;
      }
      if (tab[ind] == key && !eras[ind]) {
        return false;
      }
      if (eras[ind] && dind == -1) {
        dind = ind;
      }
      ind = (h1 + (i + 1) * h2) % cTab;
    }
    return false;
  }

  bool Erase(int key) {
    int h1 = Hash1(key);
    int h2 = Hash2(key);
    int ind = h1;

    for (int i = 0; i < cTab && tab[ind] != -1; i++) {
      if (tab[ind] == key && !eras[ind]) {
        eras[ind] = true;
        cou--;
        return true;
      }
      ind = (h1 + (i + 1) * h2) % cTab;
    }
    return false;
  }

  bool Contain(int key) const {
    int h1 = Hash1(key);
    int h2 = Hash2(key);
    int ind = h1;

    for (int i = 0; i < cTab && tab[ind] != -1; i++) {
      if (tab[ind] == key && !eras[ind]) {
        return true;
      }
      ind = (h1 + (i + 1) * h2) % cTab;
    }
    return false;
  }
};

int main() {
  int q;
  std::cin >> q;
  Hash set;

  char op;
  int x;
  while (q > 0) {
    q--;
    std::cin >> op >> x;

    if (op == '+') {
      set.Insert(x);
    } else if (op == '-') {
      set.Erase(x);
    } else if (op == '?') {
      if (set.Contain(x)) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
  }
}
