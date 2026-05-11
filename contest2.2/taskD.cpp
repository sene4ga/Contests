#include <iostream>
#include <stack>
#include <vector>

void Fastio() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  Fastio();

  int n;
  int m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> g(n);
  std::vector<std::vector<int>> gr(n);
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    --u;
    --v;
    g[u].push_back(v);
    gr[v].push_back(u);
  }
  std::vector<bool> visited(n, false);
  std::vector<int> order;
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      std::stack<std::pair<int, int>> st;
      st.push({i, 0});
      visited[i] = true;
      while (!st.empty()) {
        int v = st.top().first;
        int& idx = st.top().second;
        if (idx < (int)g[v].size()) {
          int to = g[v][idx];
          ++idx;
          if (!visited[to]) {
            visited[to] = true;
            st.push({to, 0});
          }
        } else {
          order.push_back(v);
          st.pop();
        }
      }
    }
  }
  std::vector<int> comp(n, -1);
  int compc = 0;
  for (int i = n - 1; i >= 0; --i) {
    int v = order[i];
    if (comp[v] == -1) {
      std::stack<int> st;
      st.push(v);
      comp[v] = compc;
      while (!st.empty()) {
        int u = st.top();
        st.pop();
        for (int to : gr[u]) {
          if (comp[to] == -1) {
            comp[to] = compc;
            st.push(to);
          }
        }
      }
      ++compc;
    }
  }
  std::cout << compc << '\n';
  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << comp[i] + 1;
  }
  std::cout << '\n';
}
