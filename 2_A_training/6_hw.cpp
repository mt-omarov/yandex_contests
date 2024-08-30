#include <iostream>

// url: https://contest.yandex.ru/contest/29189/enter/

class A {
private:
	using ull = unsigned long long int;
	static constexpr ull max = 1'000'000'000;

	static ull print_ans(const ull &x, const ull &y) {
		std::cout << x << ' ' << y << '\n';
		std::cout.flush();
		int a;
		std::cin >> a;
		return a;
	}

	static ull find_x(ull min, ull max) {
		while (min != max) {
			print_ans(min, 0);
			if (print_ans(max, 0) == 1) {
				min = (min + max) / 2 + 1;
			} else {
				max = (min + max) / 2;
			}
		}
		return min;
	}

	static ull find_y(ull min, ull max, const ull &x) {
		while (min != max) {
			print_ans(x, min);
			if (print_ans(x, max) == 1) {
				min = (min + max) / 2 + 1;
			} else {
				max = (min + max) / 2;
			}
		}
		return min;
	} 

public:
	static void solution() {
		int x = find_x(0, max);
		int y = find_y(0, max, x);	

		std::cout << "A " << x << ' ' << y << '\n';
	}
};


class B {
private:
	using ull = unsigned long long int;

	static bool check(const ull &a, const ull &b, const ull &c, const ull &value, const ull &x, const ull &k) {
		ull cost = value;
		if (cost >= a && cost <= b) {
			cost += value * c / 100;
		}
		return (cost * k <= x);
	}

	static ull bin_search(const ull &min, const ull &max, const ull &a, const ull &b, const ull &c, const ull &x, const ull &k) {
		ull l = min, r = max;
		while (r > l + 1) {
			ull m = (l + r) / 2;
			if (check(a, b, c, m, x, k)) {
				l = m;
			} else {
				r = m;
			}
		}
		return l;
	}


public:
	static void solution() {
		ull a, b, c, x, k;
		std::cin >> a >> b >> c >> x >> k;
		a *= 100;
		b *= 100;
		x *= 100;

		constexpr ull max = 1'000'000'000'000;
		ull result = bin_search(0, b, a, b, c, x, k);
		ull right_result = bin_search(b, max, a, b, c, x, k);

		if (check(a, b, c, right_result, x, k)) {
			result = right_result;
		}

		std::cout << result / 100 << '\n';
	}
};


int main() {
	B::solution();
}