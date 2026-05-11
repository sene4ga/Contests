#include <iostream>
#include <queue>
#include <vector>

int main() {
  const int cInf = 2009000999;

  int t;
  std::cin >> t;

  while (t-- > 0) {
    int n;
    int m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> graph(n);

    for (int i = 0; i < m; i++) {
      int u;
      int v;
      int c;
      std::cin >> u >> v >> c;
      graph[u].push_back(std::make_pair(v, c));
      graph[v].push_back(std::make_pair(u, c));
    }
    int s;
    std::cin >> s;

    std::vector<int> dist(n, cInf);
    dist[s] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;

    pq.push(std::make_pair(0, s));

    while (!pq.empty()) {
      std::pair<int, int> top = pq.top();
      pq.pop();

      int d = top.first;
      int v = top.second;

      if (d > dist[v]) {
        continue;
      }

      for (std::size_t i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i].first;
        int w = graph[v][i].second;

        if (dist[to] > d + w) {
          dist[to] = d + w;
          pq.push(std::make_pair(dist[to], to));
        }
      }
    }

    for (int i = 0; i < n; i++) {
      std::cout << dist[i] << " ";
    }
    std::cout << '\n';
  }
}
