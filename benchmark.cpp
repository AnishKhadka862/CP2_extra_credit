//
// (C) 2022, E. Wes Bethel
// benchmark-* harness for running different versions of the sum study
//    over different problem sizes
//
// usage: no command line arguments
// set problem sizes, block sizes in the code below

//
// (C) 2022, E. Wes Bethel
// benchmark-* harness for running different versions of the sum study
//    over different problem sizes
//
// usage: no command line arguments
// set problem sizes, block sizes in the code below

//Anish Khadka
//CSC 656 extra credit Coding Project 

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <string.h>

extern void setup(int64_t N, uint64_t A[]);
extern int64_t sum(int64_t N, uint64_t A[]);

int main(int argc, char** argv) {
  std::cout << std::fixed << std::setprecision(5);

  const int64_t N_SMALL = 1000000;
  const int64_t N_LARGE = 256000000;

  std::vector<int64_t> problem_sizes{N_SMALL, N_LARGE};

  std::vector<uint64_t> A(N_LARGE);

  int64_t t;
  int n_problems = problem_sizes.size();

  // Run for at least 30 seconds
  double elapsed_time = 0.0;
  int64_t num_sum_calls = 0;
  auto start_time = std::chrono::high_resolution_clock::now();
  while (elapsed_time < 30.0) {
    for (int64_t n : problem_sizes) {
      // invoke user code to set up the problem
      setup(n, &A[0]);

      // invoke method to perform the sum
      t = sum(n, &A[0]);
      num_sum_calls++;

      if (num_sum_calls % 10 == 0) {
        auto end_time = std::chrono::high_resolution_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();
        if (elapsed_time >= 30.0) {
          break;
        }
      }
    }
  }

  // Print results
  std::cout << "Total sum calls: " << num_sum_calls << std::endl;
  std::cout << "Elapsed time: " << elapsed_time << " s" << std::endl;
  std::cout << "Number of times each problem size was executed: " << std::endl ;
}

