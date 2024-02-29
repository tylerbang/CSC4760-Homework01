#include <Kokkos_Core.hpp>
#include <cstdio>

// Declare a 5 ∗ 7 ∗ 12 ∗ n View

int main(int argc, char* argv[]) {
  int n = 24; // APR hehe

  Kokkos::initialize(argc, argv);
  {
  // Make View
  Kokkos::View<double****> who_dat("who_dat", 5, 7, 12, n);
  // print name
  printf("name: %s\n", who_dat.label().data());
  }
  Kokkos::finalize();
}
