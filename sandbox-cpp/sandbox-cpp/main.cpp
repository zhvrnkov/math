//
//  main.cpp
//  sandbox-cpp
//
//  Created by Zhavoronkov Vlad on 7/6/22.
//

#include <iostream>
#include <numeric>
#include <vector>
#include <chrono>

int64_t biggest_sum_sliding_window(std::vector<int64_t> arr,
                                   size_t window_length)
{
    size_t iters = arr.size() - window_length + 1;
    int64_t minimum, output, current, ml, mr;
    minimum = std::numeric_limits<int64_t>::min();
    output = minimum;
    current = minimum;
    
    for (size_t i = 0; i < iters; i++) {
        ml = i;
        mr = i + window_length;
        if (current == minimum) {
            current = std::accumulate(&arr[ml], &arr[mr], 0);
        }
        else {
            current -= arr[ml - 1];
            current += arr[mr - 1];
        }
        output = std::max(current, output);
    }
    
    return output;
}

int64_t biggest_sum_brute_force(std::vector<int64_t> arr,
                                size_t window_length)
{
    size_t iters = arr.size() - window_length + 1;
    int64_t minimum, output, current, ml, mr;
    minimum = std::numeric_limits<int64_t>::min();
    output = minimum;
    current = minimum;
    
    for (size_t i = 0; i < iters; i++) {
        ml = i;
        mr = i + window_length;
        current = std::accumulate(&arr[ml], &arr[mr], 0);
        output = std::max(current, output);
    }
    
    return output;
}

void measure(std::function<void()> action) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;

    auto t1 = high_resolution_clock::now();
    action();
    auto t2 = high_resolution_clock::now();
    duration<double> time = t2 - t1;
    std::cout << time.count() << " ms" << std::endl;
}

int main(int argc, const char * argv[]) {
    
    size_t count = 50000000;
    std::vector<int64_t> input(count);
    std::generate(input.begin(), input.end(), [n = 1] () mutable { return n++; });
    
    measure([input] (void) {
        auto output1 = biggest_sum_sliding_window(input, 5);
        std::cout << output1 << std::endl;
    });
    
    measure([input] (void) {
        auto output1 = biggest_sum_brute_force(input, 5);
        std::cout << output1 << std::endl;
    });


    return 0;
}
