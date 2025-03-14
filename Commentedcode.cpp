#include <chrono>   // For measuring execution time
#include <cstdlib>  // For rand() and malloc()
#include <iostream> // For input/output
#include <time.h>   // For seeding random values

using namespace std::chrono;
using namespace std;

// Function to populate a vector with random values
void randomVector(int vector[], int size) {
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 100; // Assign a random number between 0 and 99
  }
}

int main() {
  unsigned long size = 100000000; // Size of vectors (100 million elements)
  srand(time(0)); // Seed the random number generator

  int *v1, *v2, *v3; // Declare pointers for vectors

  // Start measuring execution time
  auto start = high_resolution_clock::now();

  // Allocate memory for vectors
  v1 = (int *)malloc(size * sizeof(int));
  v2 = (int *)malloc(size * sizeof(int));
  v3 = (int *)malloc(size * sizeof(int));

  // Initialize vectors with random values
  randomVector(v1, size);
  randomVector(v2, size);

  // Perform vector addition
  for (int i = 0; i < size; i++) {
    v3[i] = v1[i] + v2[i];
  }

  // Stop measuring execution time
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);

  // Print execution time
  cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

  // Free allocated memory
  free(v1);
  free(v2);
  free(v3);

  return 0;
}
