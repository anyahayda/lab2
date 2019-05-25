#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include "parallel.h"
#include <cmath>
#include <fstream>


inline std::chrono::high_resolution_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

void results(unsigned long from, unsigned long to, std::atomic<unsigned> &result) {
    int n = 500;
    for (int x = from; x <= to; x++) {
        for (int y = 1; y <= n * n * 2; y++) {
            if (((x * y) / (x + y)) > n) {
                break;
            }
            if ((x * y) % (x + y) == 0 && (x * y) / (x + y) == n) {
                result++;
            }
        }
    }
}


int main(int argc, char *argv[]) {
    char *p;
    int thread_num = (int) strtol(argv[1], &p, 10);
    int from = 1;
    int to = 500000;
    int part = (to) / thread_num;
    std::vector<std::thread> thread_list;
    thread_list.reserve(thread_num);
    std::atomic<unsigned> result{0};
    auto start = get_current_time_fenced();
    for (int i = 0; i < thread_num - 1; ++i) {
        thread_list.emplace_back(results, from + i * part, from + (i + 1) * part, std::ref(result));
    }
    thread_list.emplace_back(results, from + (thread_num - 1) * part, to, std::ref(result));
    for (auto &v: thread_list) { v.join(); }
    auto finish = get_current_time_fenced();
    std::cout << to_us(finish-start) << std::endl << result;
    return 0;

}