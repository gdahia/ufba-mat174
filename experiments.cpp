#include <cassert>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "gaussian_elimination.hpp"
#include "utils.hpp"

int dfs_comps(const std::vector<std::vector<int>>& adj) {
  const int n = adj.size();
  int n_comps = 0;
  std::vector<bool> vis(n, false);
  for (int i = 0; i < n; i++)
    if (!vis[i]) {
      n_comps++;
      dfs(i, adj, vis);
    }

  return n_comps;
}

int gaussian_comps(const std::vector<std::vector<int>>& adj) {
  const int n = adj.size();
  std::vector<std::vector<long long>> lap = laplacian(adj);
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

  return lap_comps;
}

std::tuple<double, double, double, double> random_graph_experiment(
    const int n, const double p, const int trials, std::mt19937& gen) {
  std::vector<double> dfs_times, gauss_times;
  for (int trial = 0; trial < trials; trial++) {
    // adj is G(n, p) random graph
    std::vector<std::vector<int>> adj(n, std::vector<int>(n, 0));
    std::bernoulli_distribution dist(p);
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        if (dist(gen)) {
          adj[i].push_back(j);
          adj[j].push_back(i);
        }

    // find number of connected components using dfs
    std::clock_t start = std::clock();
    const int dfs_n_comps = dfs_comps(adj);
    const double dfs_time =
        1000 * (std::clock() - start) / (double)CLOCKS_PER_SEC;

    // find number of connected components using
    // nullspace of laplacian matrix
    start = std::clock();
    const int gaussian_n_comps = gaussian_comps(adj);
    const double gauss_time =
        1000 * (std::clock() - start) / (double)CLOCKS_PER_SEC;

    assert(dfs_n_comps == gaussian_n_comps);

    dfs_times.push_back(dfs_time);
    gauss_times.push_back(gauss_time);
  }

  const double mean_dfs_time =
      std::accumulate(dfs_times.begin(), dfs_times.end(), 0.0) / trials;
  const double mean_gauss_time =
      std::accumulate(gauss_times.begin(), gauss_times.end(), 0.0) / trials;

  double dfs_time_var = 0;
  double gauss_time_var = 0;
  for (int i = 0; i < trials; i++) {
    dfs_time_var += pow(mean_dfs_time - dfs_times[i], 2);
    gauss_time_var += pow(mean_gauss_time - gauss_times[i], 2);
  }
  dfs_time_var /= trials;
  gauss_time_var /= trials;
  const double dfs_time_std = sqrt(dfs_time_var);
  const double gauss_time_std = sqrt(gauss_time_var);

  return std::make_tuple(mean_dfs_time, dfs_time_std, mean_gauss_time,
                         gauss_time_std);
}

int main() {
  // remember to set seed
  std::random_device rd;
  std::mt19937 gen(rd());

  // varying graph cardinality
  std::ofstream gauss_v_file("gauss_v.txt");
  std::ofstream dfs_v_file("dfs_v.txt");
  for (int i = 10; i <= 2000; i += 20) {
    double m1, s1, m2, s2;
    std::tie(m1, s1, m2, s2) = random_graph_experiment(i, 0.5, 100, gen);

    dfs_v_file << std::fixed << std::setprecision(4) << i << " " << m1 << " "
               << s1 << std::endl;
    gauss_v_file << i << " " << m2 << " " << s2 << std::endl;
  }

  // varying graph density
  std::ofstream gauss_e_file("gauss_e.txt");
  std::ofstream dfs_e_file("dfs_e.txt");
  for (int i = 1; i < 100; i++) {
    double m1, s1, m2, s2;
    std::tie(m1, s1, m2, s2) =
        random_graph_experiment(500, i / 100.0, 100, gen);

    dfs_e_file << i << " " << m1 << " " << s1 << std::endl;
    gauss_e_file << i << " " << m2 << " " << s2 << std::endl;
  }
}
