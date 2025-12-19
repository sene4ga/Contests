#include <iostream>
#include <vector>

struct Node {
  int x = 0;
  int high = 1;
  int left = -1;
  int right = -1;
};

int Geth(int v, std::vector<Node>& tree) { return v == -1 ? 0 : tree[v].high; }

int GetB(int v, std::vector<Node>& tree) {
  if (v == -1) {
    return 0;
  }
  return Geth(tree[v].left, tree) - Geth(tree[v].right, tree);
}

void Updh(int v, std::vector<Node>& tree) {
  if (v == -1) {
    return;
  }
  tree[v].high = std::max(Geth(tree[v].left, tree), Geth(tree[v].right, tree)) + 1;
}

int RotR(int y, std::vector<Node>& tree) {
  int x = tree[y].left;
  tree[y].left = tree[x].right;
  tree[x].right = y;
  Updh(y, tree);
  Updh(x, tree);
  return x;
}

int RotL(int x, std::vector<Node>& tree) {
  int y = tree[x].right;
  tree[x].right = tree[y].left;
  tree[y].left = x;
  Updh(x, tree);
  Updh(y, tree);
  return y;
}

int BalN(int v, std::vector<Node>& tree) {
  if (v == -1) {
    return -1;
  }
  Updh(v, tree);
  int balance = GetB(v, tree);

  if (balance > 1 && GetB(tree[v].left, tree) >= 0) {
    return RotR(v, tree);
  }
  if (balance > 1 && GetB(tree[v].left, tree) < 0) {
    tree[v].left = RotL(tree[v].left, tree);
    return RotR(v, tree);
  }
  if (balance < -1 && GetB(tree[v].right, tree) <= 0) {
    return RotL(v, tree);
  }
  if (balance < -1 && GetB(tree[v].right, tree) > 0) {
    tree[v].right = RotR(tree[v].right, tree);
    return RotL(v, tree);
  }
  return v;
}

int Insert(int v, int val, std::vector<Node>& tree) {
  if (v == -1) {
    tree.push_back({val, 1, -1, -1});
    return tree.size() - 1;
  }
  if (val < tree[v].x) {
    tree[v].left = Insert(tree[v].left, val, tree);
  } else if (val > tree[v].x) {
    tree[v].right = Insert(tree[v].right, val, tree);
  } else {
    return v;
  }
  return BalN(v, tree);
}

int Lower(int v, int val, int best, std::vector<Node>& tree) {
  if (v == -1) {
    return best;
  }
  if (tree[v].x >= val) {
    return Lower(tree[v].left, val, tree[v].x, tree);
  }
  return Lower(tree[v].right, val, best, tree);
}

void Fastios() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastios();

  int q;
  const int cM = 1e9;
  int root = -1;
  std::cin >> q;
  std::vector<Node> tree;

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
      last_answer = Lower(root, x, -1, tree);
      std::cout << last_answer << '\n';
    }
  }

  return 0;
}
