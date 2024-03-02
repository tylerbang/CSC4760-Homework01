#include <Kokkos_Core.hpp>
#include <cstdio>

// Problem: Make an n ∗ m View where each index equals 1000 ∗ i ∗ j

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // set n and m, you can change these values
  int n,m = 16;
  // Make View
  Kokkos::View<double**> woah("woah", n, m);
  // set values to 1000 * i * j;
  Kokkos::parallel_for(n, KOKKOS_LAMBDA (const int i) {
    for (int j = 0; j < m; j++) {
      woah(i,j) = 1000 * i * j;
    }
  });

  // print for confirmation
  for (int x = 0; x < n; x++) {
    for (int d = 0; d < m; d++) {
      printf("%f ", woah(x,d));
    }
    printf("\n");
  }
  Kokkos::finalize();
}
