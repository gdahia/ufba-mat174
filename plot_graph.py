import numpy as np
import matplotlib.pyplot as plt

names = ['Eliminacao de Gauss', 'DFS']
paths = ['gauss.txt', 'dfs.txt']
colors = [('red', 'salmon'), ('blue', 'lightblue')]

for name, path, (c, lc) in zip(names, paths, colors):
  data = np.loadtxt(path, delimiter=' ')
  x = data[:, 0]
  y = data[:, 1]
  std = data[:, 2]

  plt.plot(x, y, color=c, label=name)
  plt.fill_between(x, y - std, y + std, color=lc)

plt.legend()
plt.xlabel('Vertices')
plt.ylabel('Tempo de execucao (ms)')

plt.show()
