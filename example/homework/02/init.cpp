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
    for (int j = 0; j < m; j++) {
      woah(i,j) = 1000 * i * j;
    }
  });

  auto woah_h = Kokkos::create_mirror_view(woah);
  Kokkos::deep_copy(woah_h, woah);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", woah_h(i,j));
    }
    printf("\n");
  }
  }

  Kokkos::finalize();
}
