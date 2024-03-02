#include <Kokkos_Core.hpp>
#include <cstdio>

// Problem: Make an n ∗ m View where each index equals 1000 ∗ i ∗ j

int main(int argc, char* argv[]) {
  char buffer[BUFSIZ];
  setvbuf(stdout, buffer, _IOLBF, sizeof(buffer));
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

  Kokkos::parallel_for("PrintView", n, KOKKOS_LAMBDA (const int i) {
    for (int j = 0; j < m; j++) {
      printf("woah(%d,%d) = %d\n", i, j, woah(i,j));
    }
  });
  }
  Kokkos::finalize();
}
