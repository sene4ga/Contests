#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int u;
  int v;
  int w;
};

int Find(int v, std::vector<int>& parent) {
  if (v == parent[v]) {
    return v;
  }
  parent[v] = Find(parent[v], parent);
  return parent[v];
}

bool Union(int a, int b, std::vector<int>& parent, std::vector<int>& rank) {
  a = Find(a, parent);
  b = Find(b, parent);

  if (a == b) {
    return false;
  }

  if (rank[a] < rank[b]) {
    parent[a] = b;
  } else {
    parent[b] = a;
    if (rank[a] == rank[b]) {
      rank[a]++;
    }
  }

  return true;
}

bool Cmp(const Edge& a, const Edge& b) { return a.w < b.w; }

int main() {
  int n;
  int m;

  std::cin >> n >> m;

  std::vector<Edge> edges;
  edges.resize(m);

  int i;
  for (i = 0; i < m; i++) {
    int u;
    int v;
    int w;

    std::cin >> u >> v >> w;

    edges[i].u = u - 1;
    edges[i].v = v - 1;
    edges[i].w = w;
  }

  std::sort(edges.begin(), edges.end(), Cmp);

  std::vector<int> parent;
  std::vector<int> rank;

  parent.resize(n);
  rank.resize(n);

  for (i = 0; i < n; i++) {
    parent[i] = i;
    rank[i] = 0;
  }

  long long mst_weight;
  mst_weight = 0;

  for (i = 0; i < m; i++) {
    int u;
    int v;
    int w;

    u = edges[i].u;
    v = edges[i].v;
    w = edges[i].w;

    if (Union(u, v, parent, rank)) {
      mst_weight += w;
    }
  }

  std::cout << mst_weight << std::endl;
}
