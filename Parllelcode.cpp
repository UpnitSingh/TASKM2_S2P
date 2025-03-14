#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm> // For std::generate

using namespace std;
using namespace std::chrono;

const unsigned long SIZE = 1000000; // Use 1 million elements for online compilers
const int THREAD_COUNT = 4; // Use 4 threads

// Function to initialize vector with random values
void randomVector(vector<int>& vec) {
    generate(vec.begin(), vec.end(), []() { return rand() % 100; });
}

// Function for parallel vector addition
void parallelAddition(vector<int>& v1, vector<int>& v2, vector<int>& v3, int start, int end) {
    for (int i = start; i < end; i++) {
        v3[i] = v1[i] + v2[i];
    }
}

int main() {
    srand(time(0));

    vector<int> v1(SIZE), v2(SIZE), v3(SIZE);

    auto start = high_resolution_clock::now();

    // Fill vectors with random values
    randomVector(v1);
    randomVector(v2);

    // Create threads for parallel addition
    vector<thread> threads;
    int chunkSize = SIZE / THREAD_COUNT;

    for (int i = 0; i < THREAD_COUNT; i++) {
        int startIdx = i * chunkSize;
        int endIdx = (i == THREAD_COUNT - 1) ? SIZE : (i + 1) * chunkSize;
        threads.push_back(thread(parallelAddition, ref(v1), ref(v2), ref(v3), startIdx, endIdx));
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Time taken by parallel execution with " << THREAD_COUNT << " threads: " << duration.count() << " ms" << endl;

    return 0;
}
