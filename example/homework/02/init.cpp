#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

// Problem: Make an n ∗ m View where each index equals 1000 ∗ i ∗ j

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // set n and m, you can change these values
  int n,m = 16;
  int sum = 0;
  // Make View
  Kokkos::View<int**> woah("woah", n, m);
  // set values to 1000 * i * j;
  for(int i = 0; i < woah.extent(0); i++){
    for(int j = 0; j < woah.extent(1); j++){
      woah(i,j) = i * j;
    }
  }
  Kokkos::fence();

  Kokkos::parallel_reduce(n, KOKKOS_LAMBDA(const int i, int& local_sum) {
    for (int j = 0; j < m; j++) {
      local_sum += woah(i,j);
    }
  }, sum);
  Kokkos::fence();
  std::cout << "Sum: " << sum << std::endl;
  }
  Kokkos::finalize();
}
