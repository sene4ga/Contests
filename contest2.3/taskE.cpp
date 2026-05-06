#include <algorithm>
#include <iostream>
#include <vector>

const int cInf = 100000;

void Solve() {
  int n;
  if (!(std::cin >> n)) {
    return;
  }

  std::vector<std::vector<int>> adj(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> adj[i][j];
    }
  }

  std::vector<long long> dist(n, 0);
  std::vector<int> parent(n, -1);
  int last_v;
  last_v = -1;

  for (int i = 0; i < n; ++i) {
    last_v = -1;
    for (int u = 0; u < n; ++u) {
      for (int v = 0; v < n; ++v) {
        if (adj[u][v] != cInf) {
          if (dist[v] > dist[u] + adj[u][v]) {
            dist[v] = dist[u] + adj[u][v];
            parent[v] = u;
            last_v = v;
          }
        }
      }
    }
  }

  if (last_v == -1) {
    std::cout << "NO" << std::endl;
  } else {
    int curr;
    curr = last_v;
    for (int i = 0; i < n; ++i) {
      curr = parent[curr];
    }

    std::vector<int> cycle;
    int start_node;
    start_node = curr;
    cycle.push_back(start_node);

    int next_node;
    next_node = parent[start_node];
    while (next_node != start_node) {
      cycle.push_back(next_node);
      next_node = parent[next_node];
    }
    cycle.push_back(start_node);

    std::reverse(cycle.begin(), cycle.end());

    std::cout << "YES" << std::endl;
    std::cout << cycle.size() << std::endl;
    for (size_t i = 0; i < cycle.size(); ++i) {
      std::cout << cycle[i] + 1 << (i == cycle.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
  }
}

int main() { Solve(); }
