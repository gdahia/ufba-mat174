#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>

std::vector<std::vector<long long>> laplacian(
    const std::vector<std::vector<int>>& adj) {
  const int n = adj.size();

  std::vector<std::vector<long long>> lap(n, std::vector<long long>(n));
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

long long pow_mod(const long long base, const long long pow,
                  const long long mod) {
  if (pow == 0) return 1;
  const long long semi_ret = pow_mod(base, pow / 2, mod);
  const long long ret = (semi_ret * semi_ret) % mod;
  if (pow % 2 == 1) return (ret * base) % mod;
  return ret;
}

#endif
