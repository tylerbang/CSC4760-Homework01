#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

// Problem: Make an n ∗ m View where each index equals 1000 ∗ i ∗ j

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // set n and m, you can change these values
  int n = 16, m = 16;
  // Make View
  Kokkos::View<int**> woah("woah", n, m);
  // set values to 1000 * i * j;
  for(int i = 0; i < woah.extent(0); i++){
    for(int j = 0; j < woah.extent(1); j++){
      woah(i,j) = 1000 * i * j;
    }
  }
  Kokkos::fence();
  
  // print out the values
  std::cout << woah(4, 4) << std::endl;
  }
  Kokkos::finalize();
}
