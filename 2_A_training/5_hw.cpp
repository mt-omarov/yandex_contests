#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

// url: https://contest.yandex.ru/contest/29072/enter/

class A {
private:
	static void input_n(std::vector<int> &n) {
		int n_size;
		std::cin >> n_size;
		n.resize(n_size);
		for (int i = 0; i < n_size; ++i) {
			std::cin >> n[i];
		}
		std::ranges::sort(n);
	}

	static void while_element_not_change(const std::vector<int> &n, const int min, int &i) {
		while (i < std::ssize(n) && n[i] == min) {
			++i;
		}
	}

public:
	static void solution() {
		std::vector<int> n_1, n_2, n_3, n_4;
		input_n(n_1);
		input_n(n_2);
		input_n(n_3);
		input_n(n_4);

		int min = std::min({n_1[0], n_2[0], n_3[0], n_4[0]});
		int max = std::max({n_1[0], n_2[0], n_3[0], n_4[0]});
		int diff = max - min;
		int best_i_1 = 0, best_i_2 = 0, best_i_3 = 0, best_i_4 = 0;

		for (
			int i_1 = 0, i_2 = 0, i_3 = 0, i_4 = 0;
			i_1 < std::ssize(n_1) && i_2 < std::ssize(n_2) && 
			i_3 < std::ssize(n_3) && i_4 < std::ssize(n_4);
		) {
			min = std::min({n_1[i_1], n_2[i_2], n_3[i_3], n_4[i_4]});	
			max = std::max({n_1[i_1], n_2[i_2], n_3[i_3], n_4[i_4]});
			int cur_diff = max - min;

			if (cur_diff < diff) {
				diff = cur_diff;
				best_i_1 = i_1;
				best_i_2 = i_2;
				best_i_3 = i_3;
				best_i_4 = i_4;
			}

			while_element_not_change(n_1, min, i_1);
			while_element_not_change(n_2, min, i_2);
			while_element_not_change(n_3, min, i_3);
			while_element_not_change(n_4, min, i_4);
		}
		std::cout << n_1[best_i_1] << ' ' << n_2[best_i_2] << ' '
			<< n_3[best_i_3] << ' ' << n_4[best_i_4] << '\n';
	}
};


class C {
private:
	using ull = unsigned long long int;

	static inline std::vector<ull> pipes;
	static inline std::vector<ull> squares;

	/* for dummy solution
	static bool is_triangle(const int a, const int b, const int c) {
		return (pipes[a] + pipes[b] > pipes[c]);
	}

	static bool is_obtuse(const int a, const int b, const int c) {
		return (squares[a] + squares[b] < squares[c]);
	}
	*/

	// upper_bound
	static int find_min(int min, int max, ull target, const std::vector<ull> &v) {
		int l = min, r = max;
		while (l != r) {
			int m = (l + r) / 2;
			if (v[m] <= target) {
				l = m + 1;
			} else {
				r = m;
			}
		}
		if (v[l] <= target) {
			return -1;
		}
		return l;
	}

	// lower_bound
	static int find_max(int min, int max, ull target, const std::vector<ull> &v) {
		int l = min, r = max;
		while (l != r) {
			int m = (l + r + 1) / 2;
			if (v[m] >= target) {
				r = m - 1;
			} else {
				l = m;
			}
		}
		if (v[l] >= target) {
			return -1;
		}
		return l;
	}


public:
	static void solution() {
		int n;
		std::cin >> n;
		if (n < 3) {
			std::cout << 0 << '\n';
			return;
		}

		pipes.resize(n);
		squares.resize(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> pipes[i];
			squares[i] = pipes[i] * pipes[i];
		}
		std::ranges::sort(pipes);
		std::ranges::sort(squares);

		ull result = 0;
		for (int c = 2; c < n; ++c) {
			int a_min = find_min(0, c - 1, pipes[c] - pipes[c - 1], pipes); // find min a that (a, c - 1, c) is triangle
			if (a_min == -1) {
				continue;
			}
			for (int a = a_min; a <= c - 2; ++a) {
				int b_min = find_min(a + 1, c - 1, pipes[c] - pipes[a], pipes); // find min b that (a, b, c) is triangle
				if (b_min == -1) {
					continue;
				}
				int b_max = find_max(b_min, c - 1, squares[c] - squares[a], squares); // find max b that (a, b, c) is obtuse
				if (b_max == -1) {
					continue;
				}
				result += (b_max - b_min + 1);
			}
		}
		std::cout << result << '\n';
	}

	static void stl_solution() { // copied from cepxuozab (github)
		size_t n;
		std::cin >> n;
		if (n < 3) {
			std::cout << 0 << '\n';
			return;
		}

		std::vector<ull> squares;
		squares.resize(n);
		pipes.resize(n);
		for (size_t i = 0; i < n; ++i) {
			std::cin >> pipes[i];
			squares[i] = pipes[i] * pipes[i];
		}
		std::ranges::sort(pipes);
		std::ranges::sort(squares);

		ull result = 0;
		for (size_t c = 2; c < n; ++c) {
			for (size_t a = 0; a < c - 1; ++a) {
				auto b_min = std::upper_bound(pipes.begin() + a + 1, pipes.begin() + c, pipes[c] - pipes[a]);
				if (b_min == pipes.begin() + c) {
					continue;
				}
				auto b_max = std::lower_bound(squares.begin() + a + 1, squares.begin() + c, squares[c] - squares[a]);
				if (b_max == squares.begin() + a + 1) {
					continue;
				}
				result += std::distance(squares.begin(), std::prev(b_max)) - std::distance(pipes.begin(), b_min) + 1;
			}
		}
		std::cout << result << '\n';
	}

	/* for debug
	static void dummy_solution() {
		int n;
		std::cin >> n;
		if (n < 3) {
			std::cout << 0 << '\n';
			return;
		}

		pipes.resize(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> pipes[i];
			squares[pipes[i]] = pipes[i] * pipes[i];
		}
		std::ranges::sort(pipes);

		int result = 0;
		for (int a = 0; a < n - 2; ++a) {
			for (int b = a + 1; b < n - 1; ++b) {
				for (int c = b + 1; c < n; ++c) {
					if (is_triangle(a, b, c) && is_obtuse(a, b, c)) {
						// std::cout << pipes[a] << ' ' << pipes[b] << ' ' << pipes[c] << '\n';
						++result;
					}
				}
			}
		}
		std::cout << result << '\n';
	}
	*/
};


int main() {
	C::solution();
}