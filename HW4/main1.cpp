#include <thread>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <functional>


// Timer class from first homework
typedef std::chrono::seconds s;
typedef std::chrono::milliseconds ms;
typedef std::chrono::microseconds mus;

#define get_name(var) #var

template <typename TD = std::chrono::milliseconds>
class Timer {
public:
	Timer(): point(std::chrono::steady_clock::now()), val(0) {}

	void start() {
		point = std::chrono::steady_clock::now();
	}

	void stop() {
		val += std::chrono::duration_cast<TD>(std::chrono::steady_clock::now() - point);
	}

	void reset() {
		val.zero();
	}

	auto get_time() {
		return val.count();
	}

	~Timer() {
	}
private:
	std::chrono::steady_clock::time_point point;
	TD val;
};



template<typename Iter, typename T>
void accumulate_block(Iter begin, Iter end, T init, T& result) {
	result = std::accumulate(begin, end, init);
}

template<typename Iter, typename T>
T parallel_accumulate(Iter begin, Iter end, T init, size_t num_threads) {
	auto real_threads = std::thread::hardware_concurrency();
	if (num_threads > real_threads) {
		exit(-1);
	}

	std::vector<std::thread> threads;
	std::vector<T> results(num_threads - 1);
	auto block_size = std::distance(begin, end) / num_threads;
	for (auto i = 0u; i + 1 < num_threads; i++) {
		threads.push_back(std::thread(
			accumulate_block<Iter, T>,
			std::next(begin, i * block_size),
			std::next(begin, (i + 1) * block_size),
			0,
			std::ref(results[i]))
		);
	}
	T last_result;
	accumulate_block(std::next(begin, (num_threads - 1) * block_size),
			end, init, last_result);
	std::for_each(std::begin(threads), std::end(threads), std::mem_fn(&std::thread::join));
	return std::accumulate(std::begin(results), std::end(results), last_result);
}

int main() {
	auto size = 0u;
	auto rep = 1u;
	std::cin >> size >> rep;
	std::vector<int> numbers(size);
	// std::iota(std::begin(numbers), std::end(numbers), 1);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution d(1, 10);

	auto real_threads = std::thread::hardware_concurrency();
	for (size_t tr = 1; tr <= real_threads; tr++) {
		std::generate_n(std::back_inserter(numbers), size, [&gen, &d](){return d(gen);});
		std::vector<size_t> res;
		for (size_t r = 0; r < rep; r++) {
			Timer<mus> timer;
			auto sum = parallel_accumulate(std::begin(numbers), std::end(numbers), 0, tr);
			timer.stop();
			res.push_back(timer.get_time());
			// std::cout << "threads: " << tr <<";\ttime" << r << ": " << timer.get_time()  << " ms" << std::endl;
		}

		// std::cout << "threads: " << tr <<";\ttime: " << std::accumulate(std::begin(res), std::end(res), 0) / rep << std::endl;
		std::cout << tr << "\t" << std::accumulate(std::begin(res), std::end(res), 0) / rep << std::endl;
	}



	// std::random_device rd;
	// std::mt19937 gen(rd());
	// std::uniform_int_distribution d(1, 10);

	// std::cin >> size;
	// std::vector<int> randoms;
	// std::generate_n(std::back_inserter(randoms), size, [&gen, &d](){return d(gen);});
	// {
	// 	Timer<std::chrono::milliseconds> t("Parallel");
	// 	auto result = parallel_accumulate(randoms.begin(), randoms.end(), 0);

	// }
	// {
	// 	Timer<std::chrono::milliseconds> t("Sequential");
	// 	auto result = std::accumulate(randoms.begin(), randoms.end(), 0);
	// }
}
