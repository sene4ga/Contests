#include <algorithm>
#include <iostream>
#include <vector>

int n;
int size;

std::vector<std::vector<int>> tree;

void Build(std::vector<int>& v) {
  int s = static_cast<int>(v.size());
  size = 1;
  while (size < s) {
    size <<= 1;
  }
  tree.resize(2 * size);

  for (int i = 0; i < s; i++) {
    tree[i + size].push_back(v[i]);
  }

  for (int i = size - 1; i > 0; i--) {
    std::vector<int>& a = tree[2 * i];
    std::vector<int>& b = tree[2 * i + 1];
    int i1 = 0;
    int j2 = 0;
    while ((i1 < static_cast<int>(tree[2 * i].size())) &&
           (j2 < static_cast<int>(tree[2 * i + 1].size()))) {
      if (a[i1] <= b[j2]) {
        tree[i].push_back(a[i1]);
        i1++;
      } else {
        tree[i].push_back(b[j2]);
        j2++;
      }
    }

    while (i1 < static_cast<int>(tree[2 * i].size())) {
      tree[i].push_back(a[i1]);
      i1++;
    }
    while (j2 < static_cast<int>(tree[2 * i + 1].size())) {
      tree[i].push_back(b[j2]);
      j2++;
    }
  }
}

int Binsearchmin(int v, int y) {
  int l = -1;
  int r = static_cast<int>(tree[v].size());

  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (tree[v][mid] <= y) {
      l = mid;
    } else {
      r = mid;
    }
  }
  return l + 1;
}

int Countmin(int v, int l, int r, int y, int ld, int rd) {
  if (ld > r || rd < l) {
    return 0;
  }
  if (ld >= l && rd <= r) {
    return Binsearchmin(v, y);
  }
  if (ld == rd) {
    if (!tree[v].empty() && tree[v][0] <= y) {
      return 1;
    }
    return 0;
  }
  int mid = (ld + rd) / 2;
  return Countmin(v * 2, l, r, y, ld, mid) +
         Countmin(v * 2 + 1, l, r, y, mid + 1, rd);
}

int Count(int l, int r, int x, int y) {
  return Countmin(1, l, r, y, 0, size - 1) -
         Countmin(1, l, r, x - 1, 0, size - 1);
}

void Fastios() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastios();

  int q;
  std::cin >> n >> q;
  std::vector<int> otr(n);

  for (int i = 0; i < n; i++) {
    std::cin >> otr[i];
  }

  Build(otr);
  int l;
  int r;
  int x;
  int y;
  for (int i = 0; i < q; i++) {
    std::cin >> l >> r >> x >> y;
    l--;
    r--;
    std::cout << Count(l, r, x, y) << '\n';
  }
}
