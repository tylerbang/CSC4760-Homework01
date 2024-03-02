#include <Kokkos_Core.hpp>
#include <cstdio>

// Create a program that compares a parallel for loop and a standard for loop for summing rows of a View with Kokkos Timer.

int main(int argc, char* argv[]) {
  const int n = 1000;
  const int m = 1000;
  const int p = 1000;
  Kokkos::initialize(argc, argv);
  {
  // Make View and create values
  Kokkos::View<int***> the_rock("the_rock", n, m, p);
  // Fill View with values
  Kokkos::parallel_for(n, KOKKOS_LAMBDA(const int i) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < p; k++) {
        the_rock(i,j,k) = i + j + k;
      }
    }
  });
  // sum loops

  // Serial for loop
  Kokkos::Timer timer;
  int sum = 0;
  for (int a = 0; a < n; a++) {
    for (int b = 0; b < m; b++) {
      for (int c = 0; c < p; c++) {
        sum += the_rock(a,b,c);
      }
    }
  }
  double time_serial = timer.seconds();

  // parallel for loop
  Kokkos::Timer timer2;
  int sum2 = 0;
  Kokkos::parallel_reduce(n, KOKKOS_LAMBDA(const int i, int& local_sum) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < p; k++) {
        local_sum += the_rock(i,j,k);
      }
    }
  }, sum2);
  double time_parallel = timer2.seconds();
  // Output times
  printf("Serial: %f\n", time_serial);
  printf("Parallel: %f\n", time_parallel);
  }
  Kokkos::finalize();
}
