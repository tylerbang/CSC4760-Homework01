#include <Kokkos_Core.hpp>
#include <cstdio>

// Problem: Make an n ∗ m View where each index equals 1000 ∗ i ∗ j

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // set n and m, you can change these values
  int n,m = 16;
  // Make View
  Kokkos::View<int**> woah("woah", n, m);
  // set values to 1000 * i * j;
  Kokkos::parallel_for(n, KOKKOS_LAMBDA (const int i) {
    Kokkos::parallel_for(m, KOKKOS_LAMBDA (const int j) {
      woah(i,j) = 1000 * i * j;
    });
  });
  Kokkos::fence();

  printf("woah(2,4) = %d\n", woah(2,4));
  }
  Kokkos::finalize();
}
