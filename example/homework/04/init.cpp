#include <Kokkos_Core.hpp>
#include <cstdio>

// Do simple parallel reduce to output the maximum element in a View

int main(int argc, char* argv[]) {
  int n = 50;

  Kokkos::initialize(argc, argv);
  {
  // Make View and create values
  Kokkos::View<int*> bottom_text("bottom_text", n);

  // Fill View with values
  Kokkos::parallel_for(n, KOKKOS_LAMBDA(const int i) {
    bottom_text(i) = i;
  });
  
  // Do a parallel reduction
  Kokkos::parallel_reduce(n, KOKKOS_LAMBDA(const int i, int& max) {
    if (bottom_text(i) > max) {
      max = bottom_text(i);
    }
  }, Kokkos::Max<int>(bottom_text(0)));
  }
  Kokkos::finalize();
}
