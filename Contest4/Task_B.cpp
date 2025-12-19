#include <iostream>
#include <string>
#include <vector>

struct Node {
  int x = 0;
  int par = -1;
  int sz = 1;
  int left = -1;
  int right = -1;
};

std::vector<Node> tree;

void Updsz(int v) {
  if (v == -1) {
    return;
  }
  tree[v].sz = 1;
  if (tree[v].left != -1) {
    tree[v].sz += tree[tree[v].left].sz;
  }
  if (tree[v].right != -1) {
    tree[v].sz += tree[tree[v].right].sz;
  }
}

void Rotr(int y, int root) {
  int x = tree[y].left;
  if (x == -1) {
    return;
  }
  int p = tree[y].par;

  tree[y].left = tree[x].right;
  if (tree[x].right != -1) {
    tree[tree[x].right].par = y;
  }
  tree[x].right = y;
  tree[y].par = x;
  tree[x].par = p;

  if (p != -1) {
    if (tree[p].left == y) {
      tree[p].left = x;
    } else {
      tree[p].right = x;
    }
  } else {
    root = x;
  }

  Updsz(y);
  Updsz(x);
}

void Rotl(int x, int root) {
  int y = tree[x].right;
  if (y == -1) {
    return;
  }

  int p = tree[x].par;

  tree[x].right = tree[y].left;
  if (tree[y].left != -1) {
    tree[tree[y].left].par = x;
  }

  tree[y].left = x;
  tree[x].par = y;
  tree[y].par = p;

  if (p != -1) {
    if (tree[p].left == x) {
      tree[p].left = y;
    } else {
      tree[p].right = y;
    }
  } else {
    root = y;
  }

  Updsz(x);
  Updsz(y);
}

int Splay(int v, int root) {
  if (v == -1) {
    return -1;
  }

  while (tree[v].par != -1) {
    int p = tree[v].par;
    int g = tree[p].par;

    if (g == -1) {
      if (tree[p].left == v) {
        Rotr(p, root);
      } else {
        Rotl(p, root);
      }
    } else {
      if (tree[p].left == v && tree[g].left == p) {
        Rotr(g, root);
        Rotr(p, root);
      } else if (tree[p].right == v && tree[g].right == p) {
        Rotl(g, root);
        Rotl(p, root);
      } else if (tree[p].left == v && tree[g].right == p) {
        Rotr(p, root);
        Rotl(g, root);
      } else {
        Rotl(p, root);
        Rotr(g, root);
      }
    }
  }
  return v;
}

int Find(int v, int val, int root) {
  int cur = v;
  int last = -1;

  while (cur != -1) {
    last = cur;
    if (tree[cur].x == val) {
      return Splay(cur, root);
    }
    if (val < tree[cur].x) {
      cur = tree[cur].left;
    } else {
      cur = tree[cur].right;
    }
  }

  if (last != -1) {
    root = Splay(last, root);
  }
  return root;
}

int Insert(int v, int val, int root) {
  if (v == -1) {
    tree.push_back({val, -1, 1, -1, -1});
    root = static_cast<int>(tree.size()) - 1;
    return root;
  }
  int cur = v;
  int par = -1;

  while (cur != -1) {
    par = cur;
    if (tree[cur].x == val) {
      root = Splay(cur, root);
      return root;
    }
    if (val < tree[cur].x) {
      cur = tree[cur].left;
    } else {
      cur = tree[cur].right;
    }
  }
  tree.push_back({val, par, 1, -1, -1});
  int new_n = static_cast<int>(tree.size()) - 1;

  if (par != -1) {
    if (val < tree[par].x) {
      tree[par].left = new_n;
    } else {
      tree[par].right = new_n;
    }
    Updsz(par);
  }
  return Splay(new_n, root);
}

int Delete(int val, int root) {
  if (root == -1) {
    return -1;
  }

  root = Find(root, val, root);

  if (tree[root].x != val) {
    return root;
  }

  int l = tree[root].left;
  int r = tree[root].right;

  if (l != -1) {
    tree[l].par = -1;
  }
  if (r != -1) {
    tree[r].par = -1;
  }

  if (l == -1) {
    root = r;
  } else if (r == -1) {
    root = l;
  } else {
    int max_left = l;
    while (tree[max_left].right != -1) {
      max_left = tree[max_left].right;
    }

    root = Splay(max_left, root);

    tree[root].right = r;
    tree[r].par = root;
    Updsz(root);
  }

  return root;
}

bool Exists(int val, int root) {
  if (root == -1) {
    return false;
  }
  root = Find(root, val, root);
  return (root != -1 && tree[root].x == val);
}

int Next(int val, int root) {
  if (root == -1) {
    return -1;
  }

  root = Find(root, val, root);

  if (tree[root].x > val) {
    return tree[root].x;
  }

  int cur = tree[root].right;
  if (cur == -1) {
    return -1;
  }

  while (tree[cur].left != -1) {
    cur = tree[cur].left;
  }
  return tree[cur].x;
}

int Prev(int val, int root) {
  if (root == -1) {
    return -1;
  }

  root = Find(root, val, root);

  if (tree[root].x < val) {
    return tree[root].x;
  }

  int cur = tree[root].left;
  if (cur == -1) {
    return -1;
  }

  while (tree[cur].right != -1) {
    cur = tree[cur].right;
  }
  return tree[cur].x;
}

int Kth(int v, int k, int root) {
  if (v == -1) {
    return -1;
  }

  int left_size = (tree[v].left != -1) ? tree[tree[v].left].sz : 0;

  if (k < left_size) {
    return Kth(tree[v].left, k, root);
  }
  if (k == left_size) {
    root = Splay(v, root);
    return tree[v].x;
  }
  return Kth(tree[v].right, k - left_size - 1, root);
}

int main() {
  std::string command;
  int root = -1;
  int x;

  while (std::cin >> command >> x) {
    if (command == "insert") {
      if (!Exists(x, root)) {
        root = Insert(root, x, root);
      }
    } else if (command == "delete") {
      if (Exists(x, root)) {
        root = Delete(x, root);
      }
    } else if (command == "exists") {
      if (Exists(x, root)) {
        std::cout << "true" << '\n';
      } else {
        std::cout << "false" << '\n';
      }
    } else if (command == "next") {
      int res = Next(x, root);
      if (res == -1) {
        std::cout << "none" << '\n';
      } else {
        std::cout << res << '\n';
      }
    } else if (command == "prev") {
      int res = Prev(x, root);
      if (res == -1) {
        std::cout << "none" << '\n';
      } else {
        std::cout << res << '\n';
      }
    } else if (command == "kth") {
      if (root == -1 || x < 0 || x >= tree[root].sz) {
        std::cout << "none" << '\n';
      } else {
        int res = Kth(root, x, root);
        if (res == -1) {
          std::cout << "none" << '\n';
        } else {
          std::cout << res << '\n';
        }
      }
    }
  }
}
