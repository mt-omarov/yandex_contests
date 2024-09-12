#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>


// "21. Три единицы подряд"
class A {
private:
	static constexpr uint n_max = 35;
public:
	static void solution() {
		std::array<uint, n_max + 1> arr;
		std::array<uint, n_max + 1> two_units_count; // the number of elements with two significant units
		arr[1] = 2;
		arr[2] = 4;
		arr[3] = 7;
		two_units_count[3] = 1;

		for (uint i = 4; i <= n_max; ++i) {
			arr[i] = arr[i - 1] * 2 - two_units_count[i - 1];
			two_units_count[i] = arr[i - 1] - arr[i - 2] - two_units_count[i - 1];
		}
		/* e.g.:
		{5, 4 == 1} = arr[4] - arr[3] - {4, 3 == 1} = 13 - 7 - 2 = 4;
		arr[6] = 48 - 4 = 44;
		*/

		uint n;
		std::cin >> n;
		std::cout << arr[n] << '\n';
	}
};


// "22. Кузнечик"
class B {
public:
	static void solution() {
		int n, k;
		std::cin >> n >> k;
		std::vector<int> prev(n + 1, 0);
		prev[1] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int j = k; j > 0; --j) {
				if (i - j > 0) {
					prev[i] += prev[i - j];
				}
			}
		}

		std::cout << prev[n] << '\n';
	}
};


// "23. Калькулятор"
class C {
public:
	static void solution() {
		int n;
		std::cin >> n;
		std::vector<int> operations_count(n + 1, 0);
		std::vector<int> history(n + 1, 0);

		history[1] = 1;
		for (int i = 2; i <= n; ++i) {
			operations_count[i] = operations_count[i - 1];
			history[i] = i - 1;
			for (int j = 3; j >= 2; --j) {
				if (i % j == 0 && operations_count[i] >= operations_count[i / j]) {
					operations_count[i] = operations_count[i / j];
					history[i] = i / j;
				}
			}
			++operations_count[i];
		}

		std::cout << operations_count[n] << '\n';
		std::vector result(1, n);
		for (int i = n; i != 1;) {
			result.push_back(history[i]);
			i = history[i];
		}
		for (int i = std::ssize(result) - 1; i >= 0; --i) {
			std::cout << result[i] << ' ';
		}
		std::cout << '\n';
	}
};


// "24. Покупка билетов"
class D {
public:
	static void solution() {
		int n;
		std::cin >> n;
		std::vector<int> times(n, 0);
		std::vector<std::tuple<int, int, int>> prev_buyers;

		for (int i = 0, a, b, c; i < 3 && i < n; ++i) {
			std::cin >> a >> b >> c;
			prev_buyers.push_back({a, b, c});
		}

		times[0] = std::get<0>(prev_buyers[0]);
		times[1] = std::min(
			std::get<0>(prev_buyers[1]) + times[0],
			std::get<1>(prev_buyers[0])
		);
		times[2] = std::min({
			std::get<0>(prev_buyers[2]) + times[1],
			std::get<1>(prev_buyers[1]) + times[0],
			std::get<2>(prev_buyers[0])
		});

		for (int i = 3, a, b, c; i < n; ++i) {
			std::cin >> a >> b >> c;

			times[i] = std::min({
				a + times[i - 1],
				std::get<1>(prev_buyers[2]) + times[i - 2],
				std::get<2>(prev_buyers[1]) + times[i - 3]
			});

			prev_buyers[0] = prev_buyers[1];
			prev_buyers[1] = prev_buyers[2];
			prev_buyers[2] = {a, b, c};
		}

		std::cout << times[n - 1] << '\n';
	}
};


// "25. Гвоздики"
class E {
public:
	static void solution() {
		int n;
		std::cin >> n;
		std::vector<int> studs(n, 0);
		std::vector<int> moves(n, 0);

		for (int i = 0; i < n; ++i) {
			std::cin >> studs[i];
		}
		std::ranges::sort(studs);

		moves[0] = 0;
		moves[1] = studs[1] - studs[0];
		moves[2] = moves[1] + studs[2] - studs[1];
		for (int i = 3; i < n; ++i) {
			moves[i] = std::min(
				moves[i - 1],
				moves[i - 2]
			);
			moves[i] += studs[i] - studs[i - 1];
		}

		std::cout << moves[n - 1] << '\n';
	}
};


int main() {
	E::solution();
}