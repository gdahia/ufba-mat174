#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP

#include <cmath>
#include <iostream>
#include <vector>

#include "utils.hpp"

void gaussian_elimination(std::vector<std::vector<long long>>& mat,
                          const long long mod) {
  const int n = mat.size();
  const int m = mat[0].size();

  // put in row echelon form
  int row = 0;
  int col = 0;
  while (row < n && col < m) {
    // find pivot
    int arg_max = row;
    for (int i = row + 1; i < n; i++)
      if (std::abs(mat[i][col]) > std::abs(mat[arg_max][col])) arg_max = i;

    if (!mat[arg_max][col])
      col++;
    else {
      // swap rows
      swap(mat[arg_max], mat[row]);

      // update remainder of matrix
      const long long inv_mod = pow_mod(mat[row][col], mod - 2, mod);
      for (int i = row + 1; i < n; i++) {
        const long long f = (mat[i][col] * inv_mod) % mod;

        mat[i][col] = 0;
        for (int j = col + 1; j < m; j++) {
          mat[i][j] += mod - ((mat[row][j] * f) % mod);
          mat[i][j] %= mod;
        }
      }

      row++;
      col++;
    }
  }
}

#endif
