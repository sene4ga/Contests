#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

void Dfs(int v, int parid, std::vector<std::vector<std::pair<int, int>>>& g,
         std::vector<int>& tin, std::vector<int>& low, std::vector<bool>& visited,
         std::vector<bool>& is_bridge, std::vector<int>& mult, int& timer;) {
  visited[v] = true;
  tin[v] = timer++;
  low[v] = timer;

  for (const auto& [to, id] : g[v]) {
    if (id == parid) {
      continue;
    }

    if (visited[to]) {
      low[v] = std::min(low[v], tin[to]);
    } else {
      Dfs(to, id, g, tin, low, visited, is_bridge, mult, timer);
      low[v] = std::min(low[v], low[to]);
      if (low[to] > tin[v] && mult[id] == 1) {
        is_bridge[id] = true;
      }
    }
  }
}

int main() {
  int n;
  int m;
  std::vector<std::vector<std::pair<int, int>>> g;
  std::vector<int> tin;
  std::vector<int> low;
  std::vector<bool> visited;
  std::vector<bool> is_bridge;
  std::vector<int> mult;
  int timer;
  std::cin >> n >> m;
  g.resize(n + 1);
  std::vector<int> u(m);
  std::vector<int> v(m);
  std::map<std::pair<int, int>, int> edge_count;
  for (int i = 0; i < m; ++i) {
    std::cin >> u[i] >> v[i];
    if (u[i] != v[i]) {
      int a = u[i];
      int b = v[i];
      if (a > b) {
        std::swap(a, b);
      }
      edge_count[{a, b}]++;
    }
  }
  mult.resize(m, 1);
  for (int i = 0; i < m; ++i) {
    if (u[i] != v[i]) {
      int a = u[i];
      int b = v[i];
      if (a > b) {
        std::swap(a, b);
      }
      int cnt = edge_count[{a, b}];
      mult[i] = cnt;
      g[u[i]].emplace_back(v[i], i);
      g[v[i]].emplace_back(u[i], i);
    }
  }

  tin.assign(n + 1, 0);
  low.assign(n + 1, 0);
  visited.assign(n + 1, false);
  is_bridge.assign(m, false);
  timer = 0;
  for (int v = 1; v <= n; ++v) {
    if (!visited[v]) {
      Dfs(v, -1, g, tin, low, visited, is_bridge, mult, timer);
    }
  }

  int cnt = 0;
  for (int i = 0; i < m; ++i) {
    if (is_bridge[i]) {
      cnt++;
    }
  }
  std::cout << cnt << std::endl;
  for (int i = 0; i < m; ++i) {
    if (is_bridge[i]) {
      std::cout << i + 1 << '\n';
    }
  }
}
