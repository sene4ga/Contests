#include <iostream>
#include <vector>

struct Node {
  int x = 0;
  int high = 1;
  int left = -1;
  int right = -1;
};

std::vector<Node> tree;
int root = -1;
const int cM = 1e9;

int Geth(int v) { return v == -1 ? 0 : tree[v].high; }

int GetB(int v) {
  if (v == -1) {
    return 0;
  }
  return Geth(tree[v].left) - Geth(tree[v].right);
}

void Updh(int v) {
  if (v == -1) {
    return;
  }
  tree[v].high = std::max(Geth(tree[v].left), Geth(tree[v].right)) + 1;
}

int RotR(int y) {
  int x = tree[y].left;
  tree[y].left = tree[x].right;
  tree[x].right = y;
  Updh(y);
  Updh(x);
  return x;
}

int RotL(int x) {
  int y = tree[x].right;
  tree[x].right = tree[y].left;
  tree[y].left = x;
  Updh(x);
  Updh(y);
  return y;
}

int BalN(int v) {
  if (v == -1) {
    return -1;
  }
  Updh(v);
  int balance = GetB(v);

  if (balance > 1 && GetB(tree[v].left) >= 0) {
    return RotR(v);
  }
  if (balance > 1 && GetB(tree[v].left) < 0) {
    tree[v].left = RotL(tree[v].left);
    return RotR(v);
  }
  if (balance < -1 && GetB(tree[v].right) <= 0) {
    return RotL(v);
  }
  if (balance < -1 && GetB(tree[v].right) > 0) {
    tree[v].right = RotR(tree[v].right);
    return RotL(v);
  }
  return v;
}

int Insert(int v, int val) {
  if (v == -1) {
    tree.push_back({val, 1, -1, -1});
    return tree.size() - 1;
  }
  if (val < tree[v].x) {
    tree[v].left = Insert(tree[v].left, val);
  } else if (val > tree[v].x) {
    tree[v].right = Insert(tree[v].right, val);
  } else {
    return v;
  }
  return BalN(v);
}

int Lower(int v, int val, int best) {
  if (v == -1) {
    return best;
  }
  if (tree[v].x >= val) {
    return Lower(tree[v].left, val, tree[v].x);
  }
  return Lower(tree[v].right, val, best);
}

void Fastios() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastios();

  int q;
  std::cin >> q;

  char type;
  int x;
  int last_answer = -1;

  for (int i = 0; i < q; ++i) {
    std::cin >> type >> x;
    if (type == '+') {
      if (i > 0 && last_answer != -1) {
        x = (x + last_answer) % cM;
      }
      root = Insert(root, x);
      last_answer = -1;
    } else {
      last_answer = Lower(root, x, -1);
      std::cout << last_answer << '\n';
    }
  }

  return 0;
}
