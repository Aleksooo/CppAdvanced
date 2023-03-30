#include <iostream>
#include <random>
#include <future>
#include <thread>
#include <vector>
#include <array>

bool isPrime(int n)
{
    // Corner case
    if (n <= 1)
        return false;

    // Check from 2 to n-1
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;

    return true;
}

template<typename Iter, typename Func>
void for_each_parallel(Iter begin, Iter end, Func f) {
    std::vector<std::future<bool>> futures;

    auto itr = begin;
    while (itr != end) {
        futures.push_back(std::async(std::launch::async, f, *itr));
        itr++;
    }

    for (size_t i = 0; i < futures.size(); i++) {
        *std::next(begin, i) = futures[i].get();
    }
}

int main() {
    std::array<int64_t, 5> num{9428052427, 528480011, 668148709, 8671804759, 332626237};

    for (auto i : num) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for_each_parallel(std::begin(num), std::end(num), isPrime);

    for (auto i : num) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
