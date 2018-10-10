#include <iostream>
#include <vector>

#include "gaussian_elimination.hpp"
#include "utils.hpp"

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n, std::vector<int>(n, 0));
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--;
    v--;
    adj[u][v] = 1;
    adj[v][u] = 1;
  }

  // find number of connected components using dfs
  int dfs_comps = 0;
  std::vector<bool> vis(n, false);
  for (int i = 0; i < n; i++)
    if (!vis[i]) {
      dfs_comps++;
      dfs(i, adj, vis);
    }

  // find number of connected components using
  // nullspace of laplacian matrix
  std::vector<std::vector<double>> lap = laplacian(adj);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) std::cout << lap[i][j] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
  gaussian_elimination(lap);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) std::cout << lap[i][j] << " ";
    std::cout << std::endl;
  }
  int lap_comps = 0;
  for (int i = 0; i < n; i++) {
    bool null_row = true;
    for (int j = 0; j < n; j++)
      if (std::fabs(lap[i][j]) > 1e-9) {
        null_row = false;
        break;
      }
    if (null_row) lap_comps++;
  }

  std::cout << dfs_comps << std::endl;
  std::cout << lap_comps << std::endl;
}
