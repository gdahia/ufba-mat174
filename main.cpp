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

  // print laplacian
  std::vector<std::vector<long long>> lap = laplacian(adj);
  std::cout << "Laplacian(G):" << std::endl;
  for (const std::vector<long long>& row : lap) {
    for (const long long& cell : row) std::cout << cell << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;

  // find number of connected components using
  // nullspace of laplacian matrix
  gaussian_elimination(lap, 1000000007);
  int lap_comps = 0;
  for (int i = 0; i < n; i++) {
    bool null_row = true;
    for (int j = 0; j < n; j++)
      if (lap[i][j] != 0) {
        null_row = false;
        break;
      }
    if (null_row) lap_comps++;
  }

  // print eliminated laplacian
  std::cout << "Eliminated Laplacian(G):" << std::endl;
  for (const std::vector<long long>& row : lap) {
    for (const long long& cell : row) std::cout << cell << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << dfs_comps << std::endl;
  std::cout << lap_comps << std::endl;
}
