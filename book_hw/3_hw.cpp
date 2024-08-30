#include <iostream>
#include <array>


/*
"Камни"
url: https://new.contest.yandex.ru/48558/
*/


class A {
private:
	static constexpr int rows = 11;
	static constexpr int cols = 11;

	static void fill_moves(std::array<std::array<bool, cols>, rows> &results) {
		results[0][0] = false;
		for (int i = 1; i < cols; ++i) {
			if (results[0][i - 1]) {
				results[0][i] = false;
			} else {
				results[0][i] = true;
			}
		}

		for (int i = 1; i < rows; ++i) {
			if (results[i - 1][0]) {
				results[i][0] = false;
			} else {
				results[i][0] = true;
			}
		}

		for (int j = 1; j < rows; ++j) {
			for (int i = 1; i < cols; ++i) {
				if (results[j][i - 1] && results[j - 1][i - 1] && results[j - 1][i]) {
					results[j][i] = false;
				} else {
					results[j][i] = true;
				}
			}
		}
	}

public:
	static void solution() {
		std::array<std::array<bool, cols>, rows> results;
		fill_moves(results);

		int n, m;
		std::cin >> n >> m;
		std::cout << (results[n][m] ? "Win" : "Lose") << '\n';
	}
};



class B {
private:
	static constexpr int rows = 1001;
	static constexpr int cols = 1001;

	static void fill_moves(std::array<std::array<bool, cols>, rows> &results) { 
		results[0][0] = false;
		results[0][1] = true;
		for (int i = 2; i < cols; ++i) {
			results[0][i] = (!results[0][i - 2] || !results[0][i - 1]);
		}

		results[1][0] = true;
		for (int i = 2; i < rows; ++i) {
			results[i][0] = (!results[i - 2][0] || !results[i - 1][0]);
		}

		for (int j = 1; j < rows; ++j) {
			for (int i = j; i < cols; ++i) { // looking only at elements above the main diagonal
				if (i == j) {
					results[j][i] = false;
				} else if (!results[j][i - 1] || !results[j - 1][i] ||
					(i >= 2 && (!results[j][i - 2] || !results[j - 1][i - 2])) ||
					(j >= 2 && (!results[j - 2][i] || !results[j - 2][i - 1]))) {
					results[j][i] = true;
				} else {
					results[j][i] = false;
				}
			}
		}

		for (int j = 0; j < rows; ++j) { // mirroring the results
			for (int i = 0; i < j; ++i) {
				results[j][i] = results[i][j];
			}
		}
	}

public:
	static void solution() {
		std::array<std::array<bool, cols>, rows> results;
		fill_moves(results);
		int n, m;
		std::cin >> n >> m;
		std::cout << (results[n][m] ? "Win" : "Lose") << '\n';
	}
};


int main() {
	B::solution();
}
