#include <Kokkos_Core.hpp>
#include <cstdio>

// Create a program that does matrix addition between a 2D View and a 1D View with at least one loop of parallelism.
// For a test case:
// a = [130, 137, 115]   b = [221]
//     [224, 158, 187]       [12]
//     [ 54, 211, 120]       [157]
// Extra credit: make a function and check for correct shape/dimensions

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View and add values
  Kokkos::View<int**> a("a", 3, 3);
  Kokkos::View<int*> b("b", 3);

  // Fill View with values
  Kokkos::parallel_for(3, KOKKOS_LAMBDA(const int i) {
    for (int j = 0; j < 3; j++) {
      a(i, j) = i * 100 + j * 10;
      printf("%d ", a(i, j));
    }
    b(i) = i * 100 + 21;
  });
  Kokkos::fence();
  // Do a matrix add
  
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      a(i, j) += b(i);
    }
  }

  // Output addition 
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d ", a(i, j));
    }
    printf("\n");
  }  

  }
  Kokkos::finalize();
}
