#include <iostream>
#include <vector>
#include <stack>


// "26. Самый дешевый путь"
class A {
private:
	static constexpr int max_cost = 100;
	static inline int n, m;

	static bool check(int start_capital, const std::vector<std::vector<int>> &matrix) {
		std::vector<std::vector<int>> moves(n + 1, std::vector<int>(m + 1, 0));
		moves[1][1] = start_capital;
		for (int row = 1; row <= n; ++row) {
			for (int col = 1; col <= m; ++col) {
				moves[row][col] += std::max(
					moves[row][col - 1],
					moves[row - 1][col]
				);
				moves[row][col] -= matrix[row][col];
			}
		}
		return (moves[n][m] >= 0);
	}

public:
	static void solution() {
		std::cin >> n >> m;
		std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(m + 1, 0));
		for (int row = 1; row <= n; ++row) {
			for (int col = 1; col <= m; ++col) {
				std::cin >> matrix[row][col];
			}
		}

		int min_start_capital = 0, max_start_capital = (n + m) * max_cost;
		int l = min_start_capital, r = max_start_capital;
		while (r > l + 1) {
			int m = (r + l) / 2;
			if (check(m, matrix)) {
				r = m;
			} else {
				l = m;
			}
		}
		if (check(l, matrix)) {
			std::cout << l << '\n';
		} else {
			std::cout << r << '\n';
		}
	}
};


// "27. Вывести маршрут максимальной стоимости"
class B {
public:
	static void solution() {
		int n, m;
		std::cin >> n >> m;
		std::vector<std::vector<std::pair<int, char>>> moves(n + 1, std::vector<std::pair<int, char>>(m + 1, {0, ' '}));
		
		const auto set_max = [&](int row, int col) {
			if (moves[row - 1][col].first >= moves[row][col - 1].first) {
				moves[row][col].first = moves[row - 1][col].first;
				moves[row][col].second = 'U';
			} else {
				moves[row][col].first = moves[row][col - 1].first;
				moves[row][col].second = 'L';
			}
		};

		for (int value, row = 1; row <= n; ++row) {
			for (int col = 1; col <= m; ++col) {
				std::cin >> value;
				set_max(row, col);
				moves[row][col].first += value;
			}
		}

		std::string history;
		for (int row = n, col = m; row > 1 || col > 1;) {
			if (moves[row][col].second == 'L') {
				history += 'R';
				--col;
			} else {
				history += 'D';
				--row;
			}
		}

		std::cout << moves[n][m].first << '\n';
		for (auto it = history.crbegin(); it != history.crend(); ++it) {
			std::cout << *it << ' ';
		}
		std::cout << '\n';
	}
};


// "28. Ход конём"
class C {
public:
	static void solution() {
		int n, m;
		std::cin >> n >> m;
		std::vector<std::vector<int>> moves(n, std::vector<int>(m, 0));

		moves[0][0] = 1;
		for (int row = 0; row < n; ++row) {
			for (int col = 0; col < m; ++col) {
				int left_row = row - 1;
				int left_col = col - 2;
				int upper_row = row - 2;
				int upper_col = col - 1;

				if (left_row >= 0 && left_col >= 0) {
					moves[row][col] += moves[left_row][left_col];
				}
				if (upper_row >= 0 && upper_col >= 0) {
					moves[row][col] += moves[upper_row][upper_col];
				}
			}
		}
		std::cout << moves[n - 1][m - 1] << '\n';
	}
};


// "30. НОП с восстановлением ответа"
class E {
public:
	static void solution() {
		int n, m;
		std::cin >> n;
		std::vector first(n, 0);
		for (int i = 0; i < n; ++i) {
			std::cin >> first[i];
		}
		std::cin >> m;
		std::vector second(m, 0);
		for (int i = 0; i < m; ++i) {
			std::cin >> second[i];
		}

		std::vector<std::vector<int>> moves(n + 1, std::vector<int>(m + 1, 0));

		for (int row = 1; row <= n; ++row) {
			for (int col = 1; col <= m; ++col) {
				if (first[row - 1] == second[col - 1]) {
					moves[row][col] += moves[row - 1][col - 1] + 1;
				} else if (moves[row - 1][col] > moves[row][col - 1]) {
					moves[row][col] += moves[row - 1][col];
				} else {
					moves[row][col] += moves[row][col - 1];
				}
			}
		}

		std::stack<int> nop;
		for (int row = n, col = m; row > 0 && col > 0;) {
			if (moves[row][col] == moves[row - 1][col]) {
				--row;
			} else if (moves[row][col] == moves[row][col - 1]) {
				-- col;
			} else {
				nop.push(first[row - 1]);
				--row;
				--col;
			}
		}

		while (!nop.empty()) {
			std::cout << nop.top() << ' ';
			nop.pop();
		}
		std::cout << '\n';
	}
};


int main() {
	E::solution();
}