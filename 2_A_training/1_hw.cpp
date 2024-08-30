#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <utility>
#include <algorithm>


class A {
public:
	static void solution() {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;

		if ((c == 0 && d == 0) || (a == 0 && b != 0)) {
			std::cout << "NO\n";
			return;
		} 

		if (a == 0) {
			std::cout << "INF\n";
			return;
		}
		if (b % a != 0) {
			std::cout << "NO\n";
			return;
		}

		int x = (-1) * b / a;
		if (c != 0 && x == (-1) * d / c) {
			std::cout << "NO\n";
		} else {
			std::cout << x << '\n';
		}
	}
};


class B {
public:
	static void solution() {
		int n, x, y;
		std::cin >> n;
		for (int i = 0; ++i <= n;) {
			std::vector<std::pair<int, int>> points;
			std::map<std::pair<float, float>, int> middles;
			for (int j = 0; j < 4; ++j) {
				std::cin >> x >> y;
				for (const auto &[x_1, y_1] : points) {
					std::pair<float, float> point;
					point.first = (x_1 + x) / 2.0;
					point.second = (y_1 + y) / 2.0;
					if (!middles.contains(point)) {
						middles.insert({ point, 0 });
					}
					++middles[point];
				}
				points.push_back({ x, y });
			}

			int matches_count = 0;
			bool more_than_two_matches = false;
			for (const auto &[point, matches] : middles) {
				if (matches == 2) {
					++matches_count;
				} else if (matches > 2) {
					more_than_two_matches = true;
					break;
				}
			}
			if (matches_count != 1 || more_than_two_matches) {
				std::cout << "NO\n";
			} else if (matches_count == 1) {
				std::cout << "YES\n";
			}
		}
	}
};


class C {
public:
	static void solution() {
		std::array<std::array<int, 3>, 3> area;
		int first_count = 0, second_count = 0;
		for (int move, row_i = 0; row_i < 3; ++row_i) {
			for (int col_i = 0; col_i < 3; ++col_i) {
				std::cin >> move;
				first_count += (move == 1);
				second_count += (move == 2);
				area[row_i][col_i] = move;
			}
		}

		if (first_count < second_count || first_count - second_count > 1) {
			std::cout << "NO\n";
			return;
		}

		bool win_first = 0, win_second = 0;
		const auto set_winner = [&](const int &move) {
			if (move == 1) {
				win_first = 1;
			} else if (move == 2) {
				win_second = 1;
			} 
		};
		for (int row_i = 0; row_i < 3; ++row_i) {
			if (area[row_i][0] == area[row_i][1] && area[row_i][1] == area[row_i][2]) {
				set_winner(area[row_i][0]);
			}
		}
		for (int col_i = 0; col_i < 3; ++col_i) {
			if (area[0][col_i] == area[1][col_i] && area[1][col_i] == area[2][col_i]) {
				set_winner(area[0][col_i]);
			}
		}
		if (area[0][0] == area[1][1] && area[1][1] == area[2][2]) {
			set_winner(area[1][1]);
		}
		if (area[0][2] == area[1][1] && area[1][1] == area[2][0]) {
			set_winner(area[1][1]);
		}

		if ((win_first && win_second) || 
			(win_first && first_count + second_count < 9 && second_count == first_count) ||
			(win_second && first_count != second_count)) {
			std::cout << "NO\n";
		} else {
			std::cout << "YES\n";
		}
	}
};


// Futurama theorem (Keeler's theroem)
class D {
private:
	static inline std::map<int, int> bodies; // body-mind pairs

	static int swap(const int body_1, const int body_2, bool to_print = true) { 
		int temp = bodies[body_1];
		bodies[body_1] = bodies[body_2];
		bodies[body_2] = temp;

		if (to_print) {
			std::cout << body_1 << ' ' << body_2 << '\n';
		}

		return bodies[body_2];
	}

	static void print_bodies() {
		std::cout << '\n';
		for (const auto &[body, mind] : bodies) {
			std::cout << body << ": " << mind << '\n';
		}
		std::cout << '\n';
	}

public:
	static void solution() { // from the lecture
		int bodies_number, switches_number;
		std::cin >> bodies_number >> switches_number;

		// initialize map
		for (int i = 1; i < bodies_number + 1; ++i) {
			bodies.insert({ i, i });
		}

		for (int body_1, body_2, sw_i = 0; sw_i < switches_number; ++sw_i) {
			std::cin >> body_1 >> body_2;
			swap(body_1, body_2, false);
		}

		const int &sweet_clyde = bodies_number - 1;
		const int &bubblegum = bodies_number;

		for (int body = 1; body < sweet_clyde; ++body) {
			if (bodies[body] == body) {
				continue;
			}
			int current_body = body;
			while (bodies[current_body] != body) {
				current_body = swap(current_body, sweet_clyde);
			}
			current_body = swap(current_body, bubblegum);
			swap(current_body, bubblegum);
			swap(bodies[sweet_clyde], sweet_clyde);
		}

		if (bodies[sweet_clyde] == bubblegum) {
			swap(sweet_clyde, bubblegum);
		}
	}
};


class E {
public:
	static void solution() {
		unsigned long int p;
		std::cin >> p;
		
		unsigned long int a, b, c;
		a = p / 3;
		b = (p - a) / 2;
		c = p - a - b;

		if (a + b <= c) {
			std::cout << -1 << '\n';
		} else {
			std::cout << a << ' ' << b << ' ' << c << '\n';
			unsigned long int d = (p - 1) / 2;
			if (p % 2 != 0) {
				std::cout << 1 << ' ';
			} else {
				std::cout << 2 << ' ';
			}
			std::cout << d << ' ' << d << '\n';
		}
	}
};


int main() {
	D::solution();
}