#include <iostream>
#include <vector>
#include <algorithm>

class A {
private:
	using ull = unsigned long long int;
public:
	static void solution() {
		ull max = 0, amount_max = 0, cur;
		while (std::cin >> cur) {
			if (cur == 0) {
				break;
			}
			if (cur == max) {
				++amount_max;
			} else if (cur > max) {
				max = cur;
				amount_max = 1;
			}
		}

		std::cout << amount_max << '\n';
	}
};


class B {
private:
	inline static constexpr int OFFICE = 0, HOME = 1, SHOP = 2;

public:
	static void solution() {
		std::vector<int> street;
		street.reserve(10);
		int i;
		while (std::cin >> i) {
			street.push_back(i);
		}

		int last_shop = -1;
		int max_d = 0, min_d = 11, d;

		for (i = 0; i < 10; ++i) {
			if (street[i] == OFFICE) {
				continue;
			}

			if (street[i] == HOME) {
				int j = i;
				min_d = (last_shop != -1) ? (i - last_shop) : 11;
				while (j < 10 && street[j] != SHOP) {
					++j;
				}
				if (j < 10) {
					d = j - i;
					min_d = (min_d < d) ? min_d : d;
				}
				max_d = (max_d < min_d) ? min_d : max_d;
			}

			if (street[i] == SHOP) {
				last_shop = i;
			}

		}
		std::cout << max_d << '\n';
	}
};


class C {
public:
	static void solution() {
		std::string str;
		std::cin >> str;

		if (str.length() == 1) {
			std::cout << 0 << '\n';
			return;
		}
		
		uint l, r;
		if (str.length() % 2 == 0) {
			l = str.length() / 2 - 1;
			r = l + 1;
		} else {
			l = str.length() / 2 - 1;
			r = l + 2;
		}

		int result = 0;
		for (; l >= 0 && r < str.length(); --l, ++r) {
			if (str[l] != str[r]) {
				++result;
			}
		}

		std::cout << result << '\n';
	}
};


class D {
public:
	static void solution() {
		uint l, k, d;
		std::cin >> l >> k;

		bool can_be_centered = (l % 2 != 0);
		uint last_left = 0, first_right = 0;
		for (uint i = 0; i < k; ++i) {
			std::cin >> d;
			if (d == l / 2 && can_be_centered) {
				std::cout << d << '\n';
				return;
			} else if (d < l / 2) {
				last_left = d;
			} else if (d >= l / 2) {
				first_right = d;
				break;
			}
		}
		std::cout << last_left << ' ' << first_right << '\n';
	}
};


class E {
public:
	static void solution() {
		int n, a;
		std::vector<int> folders;
		std::cin >> n;

		folders.reserve(n);
		for (int i = 0; ++i <= n;) {
			std::cin >> a;
			folders.push_back(a);
		}
		std::sort(folders.begin(), folders.end());

		int result = 0;
		for (int i = 0; i < n - 1; ++i) {
			result += folders[i];
		}

		std::cout << result << '\n';
	}
};


int main() {
	E::solution();
}