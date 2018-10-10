#include <vector>

std::vector<std::vector<double>> laplacian(
    const std::vector<std::vector<int>>& adj) {
  const int n = adj.size();

  std::vector<std::vector<double>> lap(n, std::vector<double>(n));
  for (int i = 0; i < n; i++) {
    // compute degree for row vertex
    int deg = 0;
    for (int j = 0; j < n; j++) deg += adj[i][j];

    // compute laplacian
    lap[i][i] = deg;
    for (int j = i + 1; j < n; j++) {
      lap[i][j] = -adj[i][j];
      lap[j][i] = -adj[j][i];
    }
  }

  return lap;
}

void dfs(const int source, const std::vector<std::vector<int>>& adj,
         std::vector<bool>& vis) {
  vis[source] = true;
  for (int target = 0; target < adj.size(); target++)
    if (adj[source][target] && !vis[target]) dfs(target, adj, vis);
}
