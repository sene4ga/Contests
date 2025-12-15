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
int root = -1;

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

void Rotr(int y) {
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

void Rotl(int x) {
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

int Splay(int v) {
  if (v == -1) {
    return -1;
  }

  while (tree[v].par != -1) {
    int p = tree[v].par;
    int g = tree[p].par;

    if (g == -1) {
      if (tree[p].left == v) {
        Rotr(p);
      } else {
        Rotl(p);
      }
    } else {
      if (tree[p].left == v && tree[g].left == p) {
        Rotr(g);
        Rotr(p);
      } else if (tree[p].right == v && tree[g].right == p) {
        Rotl(g);
        Rotl(p);
      } else if (tree[p].left == v && tree[g].right == p) {
        Rotr(p);
        Rotl(g);
      } else {
        Rotl(p);
        Rotr(g);
      }
    }
  }
  return v;
}

int Find(int v, int val) {
  int cur = v;
  int last = -1;

  while (cur != -1) {
    last = cur;
    if (tree[cur].x == val) {
      return Splay(cur);
    }
    if (val < tree[cur].x) {
      cur = tree[cur].left;
    } else {
      cur = tree[cur].right;
    }
  }

  if (last != -1) {
    root = Splay(last);
  }
  return root;
}

int Insert(int v, int val) {
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
      root = Splay(cur);
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
  return Splay(new_n);
}

int Delete(int val) {
  if (root == -1) {
    return -1;
  }

  root = Find(root, val);

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

    root = Splay(max_left);

    tree[root].right = r;
    tree[r].par = root;
    Updsz(root);
  }

  return root;
}

bool Exists(int val) {
  if (root == -1) {
    return false;
  }
  root = Find(root, val);
  return (root != -1 && tree[root].x == val);
}

int Next(int val) {
  if (root == -1) {
    return -1;
  }

  root = Find(root, val);

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

int Prev(int val) {
  if (root == -1) {
    return -1;
  }

  root = Find(root, val);

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

int Kth(int v, int k) {
  if (v == -1) {
    return -1;
  }

  int left_size = (tree[v].left != -1) ? tree[tree[v].left].sz : 0;

  if (k < left_size) {
    return Kth(tree[v].left, k);
  }
  if (k == left_size) {
    root = Splay(v);
    return tree[v].x;
  }
  return Kth(tree[v].right, k - left_size - 1);
}

int main() {
  std::string command;
  int x;

  while (std::cin >> command >> x) {
    if (command == "insert") {
      if (!Exists(x)) {
        root = Insert(root, x);
      }
    } else if (command == "delete") {
      if (Exists(x)) {
        root = Delete(x);
      }
    } else if (command == "exists") {
      if (Exists(x)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    } else if (command == "next") {
      int res = Next(x);
      if (res == -1) {
        std::cout << "none\n";
      } else {
        std::cout << res << "\n";
      }
    } else if (command == "prev") {
      int res = Prev(x);
      if (res == -1) {
        std::cout << "none\n";
      } else {
        std::cout << res << "\n";
      }
    } else if (command == "kth") {
      if (root == -1 || x < 0 || x >= tree[root].sz) {
        std::cout << "none\n";
      } else {
        int res = Kth(root, x);
        if (res == -1) {
          std::cout << "none\n";
        } else {
          std::cout << res << "\n";
        }
      }
    }
  }
}
