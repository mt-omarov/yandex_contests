#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <map>
#include <set>


class A {
public:
	static void solution() {
		int n;
		std::cin >> n;
		std::map<char, size_t> literals;

		for (char l; std::cin.get(l);) {
			if (l == '\n') {
				continue;
			}
			++literals[l];
		}

		std::string result;
		char first_odd = ' ';
		for (const auto &[l, count] : literals) {
			if (first_odd == ' ' && count % 2 == 1) {
				first_odd = l;
			}
			result += std::string(count / 2, l);
		}
		
		std::string second_half = result;
		std::reverse(second_half.begin(), second_half.end());

		if (first_odd != ' ') {
			result += first_odd;
		}

		std::cout << result << second_half << '\n';
		
	}
};


class B {
public:
	static void solution() {
		int n, m;
		std::cin >> n >> m;
		std::unordered_map<char, size_t> table;

		std::string line;
		for (int i = 0; i < n;) {
			std::getline(std::cin, line);
			if (line.empty()) {
				continue;
			}
			for (const char l : line) {
				++table[l];
			}
			++i;
		}

		for (int i = 0; i < m; ++i) {
			std::getline(std::cin, line);
			for (const char l : line) {
				--table[l];
			}
		}

		std::string result;
		for (const auto &[l, count] : table) {
			if (count > 0) {
				result += std::string(count, l);
			}
		}

		std::cout << result << '\n';
	}
};


class C { // non-working
public:
	static void solution() {
		int n, k;
		std::cin >> n >> k;
		std::unordered_map<char, int> history;
		std::unordered_map<char, std::unordered_set<char>> beatiful_pairs;


		std::string s;
		s.reserve(n);
		std::cin >> s;
		for (int i = 0; i < k; ++i) {
			char first, second;
			std::cin >> first >> second;
			if (!beatiful_pairs.contains(first)) {
				beatiful_pairs[first] = std::unordered_set<char>();
			}
			beatiful_pairs[first].insert(second);
		}

		int result = 0;
		for (int i = n - 2; i >= 0; --i) {
			if (beatiful_pairs.contains(s[i])) {
				for (const auto &l : beatiful_pairs[s[i]]) {
					if (history.contains(l)) {
						result += history[l];
					}
				}
			}
			++history[s[i]];
		}

		std::cout << result << '\n';
	}
};


class D {
private:
	static void input_number(std::unordered_map<char, int> &table) {
		std::string line;
		std::getline(std::cin, line);
		for (auto digit : line) {
			++table[digit];
		}
	}

public:
	static void solution() {
		std::unordered_map<char, int> first, second;
		std::map<char, int> common_number;
		input_number(first);
		input_number(second);
		for (const auto &[digit, count] : first) {
			if (second.contains(digit)) {
				common_number[digit] += (count > second[digit]) ? second[digit] : count;
			}
		}
		std::string result;
		for (auto it = common_number.crbegin(); it != common_number.crend(); ++it) {
			result += std::string(static_cast<size_t>(it->second), it->first);
		}

		if (common_number.size() == 1 && common_number.begin()->first == '0') {
			result = "0";
		} else if (result.empty()) {
			result = "-1";
		}
		std::cout << result << '\n';
	}
};


class E {
private:
	static void fill_map(const std::string &str, std::map<char, int> &map) {
		for (auto l : str) {
			++map[l];
		}
	}

	static void intersect_map(std::map<char, int> &first_map, std::map<char, int> &second_map) {
		for (auto it = first_map.begin(); it != first_map.end();) {
			if (!second_map.contains(it->first)) {
				first_map.erase(it++);
			} else {
				++it;
			}
		}
	}

	static void update_maps(std::map<char, int> &first_map, std::map<char, int> &second_map, const char literal) {
		if (first_map[literal] == 0 || second_map[literal] == 0) {
			first_map.erase(literal);
			second_map.erase(literal);
		}
	}

public:
	static void solution() {
		std::map<char, int> first_map, second_map;
		std::string first_str, second_str;

		std::cin >> first_str >> second_str;
		fill_map(first_str, first_map);
		fill_map(second_str, second_map);
		intersect_map(first_map, second_map);
		intersect_map(second_map, first_map);

		std::string result;
		if (first_map.crbegin() == first_map.crend()) {
			std::cout << result << '\n';
			return;
		}
		auto current_max_literal = first_map.crbegin()->first;
		for (size_t f_i = 0, s_i = 0; f_i < first_str.length() && s_i < second_str.length();) {
			bool first_cond = (first_str[f_i] != current_max_literal);
			bool second_cond = (second_str[s_i] != current_max_literal);

			if (first_cond || second_cond) {
				if (first_cond) {
					--first_map[first_str[f_i]];
					update_maps(first_map, second_map, first_str[f_i]);
					++f_i;
				}
				if (second_cond) {
					--second_map[second_str[s_i]];
					update_maps(first_map, second_map, second_str[s_i]);
					++s_i;
				}
			} else {
				int count = first_map[first_str[f_i]];
				if (count > second_map[first_str[f_i]]) {
					count = second_map[first_str[f_i]];
				}
				result += std::string(static_cast<size_t>(count), current_max_literal);
				while (count > 0) {
					if (first_str[f_i] == current_max_literal && second_str[s_i] == current_max_literal) {
						--first_map[first_str[f_i]];
						--second_map[second_str[s_i]];
						update_maps(first_map, second_map, first_str[f_i]);
						++f_i;
						++s_i;
						--count;
					} else {
						if (first_str[f_i] != current_max_literal) {
							--first_map[first_str[f_i]];
							update_maps(first_map, second_map, first_str[f_i]);
							++f_i;
						}
						if (second_str[s_i] != current_max_literal) {
							--second_map[second_str[s_i]];
							update_maps(first_map, second_map, second_str[s_i]);
							++s_i;
						}
					}
				}
				if (first_map.crbegin() == first_map.crend()) {
					std::cout << result << '\n';
					return;
				}
				current_max_literal = first_map.crbegin()->first;
			}
		}

		std::cout << result << '\n';
	}
};


int main() {
	E::solution();
}