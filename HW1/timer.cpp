#include <iostream>
#include <chrono>
#include <cmath>

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


int main() {
	double count = 0;

	Timer<ms> t;
	std::cout << "cos of double angle in process..." << std::endl;

	t.start();
	for (auto i = 0; i < 10'000'000; i++) {
		count += std::cos(i) * std::cos(i) - std::sin(i) * std::sin(i);
	}
	t.stop();
	std::cout << "Time passed: " <<  t.get_time() << get_name(ms) << std::endl << std::endl;

	count = 0;

	std::cout << "sin of double angle in process..." << std::endl;
	t.reset();
	t.start();
	for (auto i = 0; i < 10'000'000; i++) {
		count += 2 * std::sin(i) * std::cos(i);
	}
	t.stop();
	std::cout << "Time passed: " <<  t.get_time() << get_name(ms) << std::endl << std::endl;

	return 0;
}
