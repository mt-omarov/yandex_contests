#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>


class A {
private:
	using ul = unsigned long int;

public:
	static void solution() {
		std::unordered_set<ul> nums_first;
		std::unordered_set<ul> nums_second;

		std::string line, subline;
		std::getline(std::cin, line);
		{ // read first array
			std::stringstream ss(line);
			while (std::getline(ss, subline, ' ')) {
				ul num = std::stoul(subline);
				if (!nums_first.contains(num)) {
					nums_first.insert(num);
				}
			}
		}

		std::getline(std::cin, line);
		ul result = 0;
		{ // read second array
			std::stringstream ss(line);
			while (std::getline(ss, subline, ' ')) {
				ul num = std::stoul(subline);
				if (!nums_first.contains(num)) {
					continue;
				}
				if (!nums_second.contains(num)) {
					nums_second.insert(num);
					++result;
				}
			}
		}

		std::cout << result << '\n';
	}
};


class B {
public:
	static void solution() {
		std::unordered_set<long int> nums;
		
		std::string line, subline;
		std::getline(std::cin, line);
		std::stringstream ss(line);
		while (std::getline(ss, subline, ' ')) {
			long int num = std::stol(subline);
			if (!nums.contains(num)) {
				nums.insert(num);
				std::cout << "NO\n";
			} else {
				std::cout << "YES\n";
			}
		}
	}
};


class C {
public:
	static void solution() {
		std::vector<long int> input_seq;
		std::unordered_map<long int, bool> nums;
		{ // input sequence
			std::string num;
			while (getline(std::cin, num, ' ')) {
				try {
					input_seq.push_back(std::stol(num));
				} catch (std::invalid_argument err) {
					continue;
				}
			}
		}

		for (const auto &num : input_seq) {
			if (!nums.contains(num)) {
				nums.insert({ num, true });
			} else {
				nums[num] = false;
			}
		}

		for (const auto &num : input_seq) {
			if (nums[num]) {
				std::cout << num << ' ';
			}
		}
		std::cout << '\n';
	}
};


class D {
private:
	inline static const std::string HELP_M{"HELP"};
	inline static const std::string YES_M{"YES"};

public:
	static void solution() {
		std::set<long int> good_nums, bad_nums;
		long int n;
		std::cin >> n;

		std::string line, subline;
		while (std::getline(std::cin, line)) {
			if (line.empty()) {
				continue;
			}
			if (line == HELP_M) {
				break;
			}

			long int num;
			std::unordered_set<long int> question_nums;
			std::istringstream stream(line);
			while (std::getline(stream, subline, ' ')) {
				try {
					num = std::stol(subline);
				} catch (std::invalid_argument err) {
					continue;
				}
				if (num <= n) {
					question_nums.insert(num);
				}
			}

			std::getline(std::cin, line);
			if (line == YES_M && good_nums.empty()){
				for (const auto &it : question_nums) {
					good_nums.insert(it);
				}
			} else if (line == YES_M) {
				for (const auto &it : good_nums) {
					if (!question_nums.contains(it)) {
						bad_nums.insert(it);
					}
				}
			} else {
				for (const auto &it : question_nums) {
					bad_nums.insert(it);
				}
			}
		}

		if (good_nums.empty()) {
			for (long int i = 1; i <= n; ++i) {
				if (!bad_nums.contains(i)) {
					std::cout << i << ' ';
				}
			}
		} else {
			for (const auto &it : good_nums) {
				if (!bad_nums.contains(it)) {
					std::cout << it << ' ';
				}
			}
		}
		std::cout << '\n';
	}
};


class E {
private:
	static int count_coincidences(
		const std::vector<std::set<char>> &witnesses, 
		const std::string &number_str
	) {
		std::set<char> number;
		for (const auto &literal : number_str) {
			number.insert(literal);
		}

		int matches = 0;
		// complexity: O(M * 2 * (20 + 20) - 1) -> O(8 * 10^3)
		for (const auto &statement : witnesses) {
			matches += static_cast<int>(std::includes(
				number.begin(), number.end(), 
				statement.begin(), statement.end()
			));
		}
		return matches;
	}

public:
	// complexity: O(N * M * 80) -> O(8 * 10^6) < O(2 * 10^8) 
	static void solution() {
		int m, n;
		std::cin >> m;
		std::vector<std::set<char>> witnesses;
		witnesses.reserve(m);

		std::string line;
		for (int i = 0; ++i <= m;) {
			std::cin >> line;
			std::set<char> statement;
			for (const char &literal : line) {
				statement.insert(literal);
			}
			witnesses.push_back(statement);
		}

		std::vector<std::string> numbers;
		int max_matches = -1, matches;
		std::cin >> n;
		for (int i = 0; ++i <= n;) { // get numbers
			std::cin >> line;
			matches = count_coincidences(witnesses, line);
			if (max_matches < matches) {
				max_matches = matches;
				numbers.clear();
				numbers.push_back(line);
			} else if (max_matches == matches) {
				numbers.push_back(line);
			}
		}

		for (const auto &number : numbers) {
			std::cout << number << '\n';
		}
	}
};


int main() {
	E::solution();
}