#include <Kokkos_Core.hpp>
#include <cstdio>

// Create a program that compares a parallel for loop and a standard for loop for summing rows of a View with Kokkos Timer.

int main(int argc, char* argv[]) {
  const int n = 1000;
  Kokkos::initialize(argc, argv);
  {
  // Make View and create values
  Kokkos::View<int*> the_rock("the_rock", n);
  // Fill View with values
  Kokkos::parallel_for(n, KOKKOS_LAMBDA(const int i) {
    the_rock(i) = i;
  });
  // sum loops

  // Serial for loop
  Kokkos::Timer timer;
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += the_rock(i);
  }
  double time_serial = timer.seconds();
  timer.reset();

  // parallel for loop
  int sum2 = 0;
  Kokkos::parallel_reduce(n, KOKKOS_LAMBDA(const int i, int& local_sum) {
    local_sum += the_rock(i);
  }, sum2);
  double time_parallel = timer.seconds();
  timer.reset();

  // Output times
  printf("Serial: %f\n", time_serial);
  printf("Parallel: %f\n", time_parallel);
  }
  Kokkos::finalize();
}
