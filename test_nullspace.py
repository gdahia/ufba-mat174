import numpy as np


def laplacian(adj):
  return np.diag(np.sum(adj, axis=0)) - adj


def nullspace_dims(mat):
  vals, _ = np.linalg.eig(mat)
  return np.sum(np.isclose(vals, 0))


def dfs(source, vis, adj):
  vis[source] = True
  for target, has_edge in enumerate(adj[source]):
    if has_edge and not vis[target]:
      dfs(target, vis, adj)


def main(adj):
  # compute laplacian matrix
  lap = laplacian(adj)

  # number of connected components via nullspace
  # of laplacian matrix of graph
  alg_comps = nullspace_dims(lap)
  print(alg_comps)

  # number of connected components via dfs
  n = len(adj)
  dfs_comps = 0
  vis = np.zeros(n, dtype=np.bool)
  for source in range(n):
    if not vis[source]:
      dfs_comps += 1
      dfs(source, vis, adj)

  print(dfs_comps)


if __name__ == '__main__':
  n, m = [int(x) for x in input().split()]

  adj = np.zeros((n, n), dtype=np.int32)
  for _ in range(m):
    u, v = [int(x) for x in input().split()]
    adj[u, v] = 1
    adj[v, u] = 1

  main(adj)
