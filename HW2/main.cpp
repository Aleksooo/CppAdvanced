#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <iterator>

#define range(container) std::begin(container), std::end(container)

std::ostream& operator<<(std::ostream& os, std::vector<int> v1) {
    std::copy(range(v1), std::ostream_iterator<int>(os, " "));

    return os;
}

std::istream& operator>>(std::istream& is, std::vector<int>& v1) {
    std::copy(std::istream_iterator<int>(is), std::istream_iterator<int>(), std::back_inserter(v1));

    return is;
}

int main() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> dist(-20, 20);


    std::vector<int> v1(10);

    // №1
    std::iota(range(v1), 1);
    std::cout << "Задание №1:\n" << "П1: " << v1 << std::endl << std::endl;

    // №2
    std::cin >> v1;
    std::cout << "Задание №2:\n" << "П1: " << v1 << std::endl << std::endl;

    // №3
    std::shuffle(range(v1), g);
    std::cout << "Задание №3:\n" << "П1: " << v1 << std::endl << std::endl;

    // №4
    auto end = std::end(v1);
    for (auto itr = std::begin(v1); itr < end; itr++) {
        end = std::remove(itr+1, end, *itr);
    }
    v1.erase(end, std::end(v1));
    std::cout << "Задание №4:\n" << "П1: " << v1 << std::endl << std::endl;

    // №5
    std::cout << "Задание №5:\n" << "Количество нечетных чисел: " << std::accumulate(range(v1), 0, [](auto lhs, auto rhs){ return lhs + rhs % 2; }) << std::endl << std::endl;

    // №6
    std::cout << "Задание №6:\n" << "Максимальное значение: " << *std::max_element(range(v1)) << std::endl;
    std::cout << "Минимальное значение: " << *std::min_element(range(v1)) << std::endl << std::endl;

    // №7
    auto is_prime = [](int val) {
        if (std::abs(val) == 1) return 1;
        if (val == 0) return 0;

        for (int i = 2; i <= std::sqrt(val); i++) {
            if (val % i == 0) return 0;
        }
        return 1;
    };
    std::cout << "Задание №7:" << std::endl;
    std::cout << "Простое значение: " << *std::find_if(range(v1), is_prime) << std::endl << std::endl;

    // №8
    std::transform(range(v1), std::begin(v1), [](auto val){ return val * val; });
    std::cout << "Задание №8:\n" << "П1: " << v1 << std::endl << std::endl;

    // №9
    std::vector<int> v2(v1.size());
    auto gen = [&dist, &g](){ return dist(g); };
    std::generate(range(v2), gen);
    std::cout << "Задание №9:\n" << "П2: " << v2 << std::endl << std::endl;

    // №10
    std::cout << "Задание №10:\n" << "Cумма: " << std::accumulate(range(v2), 0) << std::endl << std::endl;

    // №11
    size_t k = 3;
    std::fill(std::begin(v2), std::begin(v2)+k, 1);
    std::cout << "Задание №11:\n" << "П2: " << v2 << std::endl << std::endl;

    // №12
    std::vector<int> v3(v2.size());
    std::transform(range(v1), std::begin(v2), std::begin(v3), std::minus<int>());
    std::cout << "Задание №12:\n" << "П3: " << v3 << std::endl << std::endl;

    // №13
    std::transform(range(v3), std::begin(v3), [](auto item){ return item < 0? 0: item; });
    std::cout << "Задание №13:\n" << "П3: " << v3 << std::endl << std::endl;

    // №14
    auto remove_from = std::remove(range(v3), 0);
    v3.erase(remove_from, std::end(v3));
    std::cout << "Задание №14:\n" << "П3: " << v3 << std::endl << std::endl;

    // №15
    std::reverse(range(v3));
    std::cout << "Задание №15:\n" << "П3: " << v3 << std::endl << std::endl;

    // №16
    std::nth_element(std::begin(v3), std::begin(v3)+2, std::end(v3), std::greater{});
    std::cout << "Задание №16:\n" << "Три максимальных: " << v3[0] << " " << v3[1] << " " << v3[2] << std::endl << std::endl;

    // №17
    std::sort(range(v1));
    std::sort(range(v2));
    std::cout << "Задание №17:\n" << "П1: " << v1 << "\nП2: " << v2 << std::endl << std::endl;

    // №18
    std::vector<int> v4(v1.size() + v2.size());
    std::merge(range(v1), range(v2), std::begin(v4));
    std::cout << "Задание №18:\n" << "П4: " << v4 << std::endl << std::endl;

    // №19
    auto p = std::equal_range(range(v4), 1);
    std::cout << "Задание №19:\nДиапозон единичек: ";
    for (auto itr = p.first; itr != p.second; itr++) {
        std::cout << *itr << " ";
    }
    std::cout << std::endl << std::endl;

    // №20
    std::cout << "Задание №20:\nП1: " << v1 << "\nП2: " << v2 << "\nП3: " << v3 << std::endl;
}
