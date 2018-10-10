#include <cmath>
#include <iostream>
#include <vector>

void gaussian_elimination(std::vector<std::vector<double>>& mat) {
  const int n = mat.size();
  const int m = mat[0].size();

  // put in row echelon form
  int k = 0;
  int h = 0;
  while (k < n && h < m) {
    // find pivot
    int arg_max = k;
    for (int i = k + 1; i < n; i++)
      if (std::abs(mat[i][h]) > std::abs(mat[arg_max][h])) arg_max = i;

    if (!mat[arg_max][h])
      k++;
    else {
      // swap rows
      swap(mat[arg_max], mat[k]);

      // update remainder of matrix
      for (int i = k + 1; i < n; i++) {
        const double f = mat[i][h] / mat[k][h];

        mat[i][h] = 0;
        for (int j = h + 1; j < m; j++) mat[i][j] -= mat[k][j] * f;
      }

      k++;
      h++;
    }
  }

  // put in reduced row echelon form
  for (int k = 0; k < n; k++) {
    // find leading coefficient
    int h = 0;
    while (h < m && std::fabs(mat[k][h]) <= 1e-9) h++;

    // check for zero row
    if (h < m) {
      // divide row by leading coefficient
      const double lc = mat[k][h];
      mat[k][h] = 1;
      for (int j = h + 1; j < m; j++) mat[k][j] /= lc;

      // subtract other rows by leading coefficient multiple
      for (int i = k - 1; i >= 0; i--) {
        const double f = mat[i][h];
        mat[i][h] = 0;
        for (int j = h + 1; j < m; j++) mat[i][j] -= mat[k][j] * f;
      }
    }
  }
}