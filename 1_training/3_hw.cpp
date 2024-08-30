#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <set>
#include <vector>
#include <algorithm>
#include <tuple>
#include <unordered_map>


// "Количество различных тел"
class A {
public:
	static void solution() {
		std::unordered_set<int> set;
		int num;
		while (std::cin >> num)
			set.insert(num);

		std::cout << set.size();
	}
}


// "Пересечение множеств"
class B {
public:	
	template<typename T> 
	static void input_set(T &set) {
		std::string line;
		std::getline(std::cin, line);
		std::stringstream ss(line);
		while (std::getline(ss, line, ' ')) {
			set.insert(std::stoi(line));
		}
	}

	static void sorted_set_solution() {
		std::set<int> set_A, set_B;
		std::vector<int> result;
		input_set(set_A);
		input_set(set_B);

		std::set_intersection(
			set_A.cbegin(), set_A.cend(),
			set_B.cbegin(), set_B.cend(),
			std::back_inserter(result)
		);

		for (const int &i : result) {
			std::cout << i << ' ';
		}
	}

	// better
	static void std_sort_solution() {
		std::unordered_set<int> set_A, set_B;
		std::vector<int> result;
		input_set(set_A);
		input_set(set_B);

		for (const int &i : set_A) {
			if (set_B.contains(i)) {
				result.push_back(i);
			}
		}
		std::sort(result.begin(), result.end());
		for (const int &i : result) {
			std::cout << i << ' ';
		}
	}
};


// "Кубики"
class C {
private:
	template<typename T> 
	static void input_color(T &v, int n) {
		std::size_t color;
		for (int i = 0; i < n; ++i) {
			std::cin >> color;
			v.insert(color);
		}
	}

	template<typename T>
	static void output_container(T &v) {
		std::cout << v.size() << '\n';
		for (const std::size_t &i : v) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
	}

public:
	static void solution() {
		int n, m;
		std::cin >> n >> m;

		std::unordered_set<std::size_t> a, b;
		input_color(a, n);
		input_color(b, m);

		std::vector<std::size_t> left, right;
		std::set<std::size_t> inner;

		for (const std::size_t &i : a) {
			if (b.contains(i)) {
				inner.insert(i);
			} else {
				left.push_back(i);
			}
		}

		for (const std::size_t &i : b) {
			if (!inner.contains(i)) {
				right.push_back(i);
			}
		}

		std::sort(left.begin(), left.end());
		std::sort(right.begin(), right.end());

		output_container(inner);
		output_container(left);
		output_container(right);
	}
};


// "Количество слов в тексте"
class D {
public:
	static void solution() {
		std::ifstream cin("input.txt");
		std::unordered_set<std::string> results;

		std::string line, subline;
		while (std::getline(cin, line)) {
			std::stringstream ss(line);
			while (std::getline(ss, subline, ' ')) {
				results.insert(subline);
			}
		}
		std::cout << results.size();
	}
};


// "OpenCalculator"
class E {
public:
	static void solution() {
		int x, y, z, n;
		std::cin >> x >> y >> z;
		std::cin >> n;
		std::unordered_set<int> result;

		int num;
		while (n > 0) {
			num = n % 10;
			n = n / 10;
			if ((num == x) || (num == y) || (num == z))
				continue;
			result.insert(num);
		}
		std::cout << result.size();
	}
};


// "Инопланетный геном"
class F {
public:
	static void input(std::multiset<std::string> &set) {
		std::string line;
		std::getline(std::cin, line);
		
		for (int i = 0; i + 1 < line.size(); ++i) {
			set.insert(line.substr(i, 2));
		}
	}

	static void solution() {
		std::multiset<std::string> a, b;
		input(a);
		input(b);
		int result = 0;

		for (const auto &i : a) {
			if (b.contains(i)) {
				++result;
			}
		}
		std::cout << result;
	}
};


// "Черепахи"
class G {
public:
	static void solution() {
		int n, a, b;
		std::set<std::tuple<int, int>> results;

		std::cin >> n;
		for (int i = 0; i < n; ++i) {
			std::cin >> a >> b;
			if ((a < 0) || (b < 0) || (a + b + 1 != n)) {
				continue;
			}
			results.insert(std::tuple<int, int>{a, b});
		}
		std::cout << results.size();
	}
};


// "Злые свинки"
class H {
public:
	static void solution() {
		std::size_t n, x, y;
		std::unordered_set<std::size_t> results;

		std::cin >> n;
		for (int i = 0; i < n; ++i) {
			std::cin >> x >> y;
			results.insert(x);
		}
		std::cout << results.size();
	}
};


// "Полиглоты"
class I {
public:
	static void output_ans(const std::vector<std::string> &ans) {
		std::cout << ans.size() << '\n';
		for (const auto &lang : ans) {
			std::cout << lang << '\n';
		}
	}

	static void solution() {
		uint n, m;
		std::cin >> n;
		std::unordered_map<std::string, uint> langs;
		langs.reserve(n);
		uint i = 0, j = 0;
		std::string lang;
		while (++i <= n) {
			std::cin >> m;
			j = 0;
			while (++j <= m) {
				std::cin >> lang;
				if (!langs.contains(lang)) {
					langs.insert({lang, 0});
				}
				++langs[lang];
			}
		}

		std::vector<std::string> first_ans, second_ans;
		for (const auto &lang : langs) {
			if (lang.second == n) {
				first_ans.push_back(lang.first);
			}
			second_ans.push_back(lang.first);
		}
		output_ans(first_ans);
		output_ans(second_ans);
	}
};


// "Пробежки по Манхэттену"
class J {
public:
	struct Diag {
	public:
		int subtruct;
		int sum;

		Diag(const int &x, const int &y)
			: subtruct(x - y)
			, sum(x + y)
		{}

		Diag(): Diag(0, 0) {}

		void intersection_min(const Diag &diag) {
			subtruct = std::min(subtruct, diag.subtruct);
			sum = std::min(sum, diag.sum);
		}

		void intersection_max(const Diag &diag) {
			subtruct = std::max(subtruct, diag.subtruct);
			sum = std::max(sum, diag.sum);
		}
	};

	struct Rect {
	public:
		Diag min_diag, max_diag;

		Rect(): min_diag(0, 0), max_diag(0, 0) {}

		Rect(const int &x, const int &y, const int &d) {
			update(x, y, d);
		}

		void expand(const int &d) {
			min_diag.subtruct -= d;
			min_diag.sum -= d;
			max_diag.subtruct += d;
			max_diag.sum += d;
		}

		void update(const int &x, const int &y, const int &d) {
			min_diag.subtruct = max_diag.subtruct = x - y;
			min_diag.sum = max_diag.sum = x + y;
			expand(d);
		}

		void intersection(const Rect &pos) {
			min_diag.intersection_max(pos.min_diag);
			max_diag.intersection_min(pos.max_diag);
		}
	};

	static void solution() {
		int t, d, n;
		std::cin >> t >> d >> n;
		Rect pos, pos_nav;

		for (int i = 0, x_nav, y_nav; ++i <= n;) {
			std::cin >> x_nav >> y_nav;
			pos_nav.update(x_nav, y_nav, d);
			pos.expand(t);
			pos.intersection(pos_nav);
		}

		std::vector<std::pair<int, int>> points;
		int x, y;
		for (int x_sum_y = pos.min_diag.sum; x_sum_y <= pos.max_diag.sum; ++x_sum_y) {
			for (int x_subtruct_y = pos.min_diag.subtruct; x_subtruct_y <= pos.max_diag.subtruct; ++x_subtruct_y) {
				if ((x_sum_y + x_subtruct_y) % 2 == 0) {
					x = (x_sum_y + x_subtruct_y) / 2;
					y = x_sum_y - x;
					points.push_back({ x, y });
				}
			}
		}
		std::cout << points.size() << '\n';
		for (const auto &point : points) {
			std::cout << point.first << ' ' << point.second << '\n';
		}
	}
};


int main() {
	J::solution();
}