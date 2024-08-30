#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <algorithm>


// "Хитрый шифр"
// url: https://contest.yandex.ru/contest/50668/problems/A/


int get_uniq_literals_count(const std::string &name) {
	std::unordered_set<char> set;
	for (auto l : name) {
		set.insert(l);
	}
	return set.size();
}

std::string int_to_hex(int number) {
	std::string result(std::to_string(number).size(), 0);

	int i = 0;
	while (number != 0) {
		int temp = number % 16;
		result[i] = temp;
		if (temp < 10) {
			result[i] += 48;
		} else {
			result[i] += 55;
		}
		++i;
		number /= 16;
	}

	std::reverse(result.begin(), result.end());
	
	if (result.length() > 3) {
		result = result.substr(result.size() - 3);
	}
	return result;
}


void solution() {
	int n;
	std::cin >> n;
	std::string line;
	std::istringstream iss(line);
	for (int j = 0; j < n; ++j) {
		std::cin >> line;
		iss.clear();
		iss.str(line);
		std::string f, i, o, tmp;
		
		std::getline(iss, f, ',');
		std::getline(iss, i, ',');
		std::getline(iss, o, ',');
		std::getline(iss, tmp, ',');
		int d{std::stoi(tmp)};
		std::getline(iss, tmp, ',');
		int m{std::stoi(tmp)};
		std::getline(iss, tmp, ','); // skip year

		int first_number = get_uniq_literals_count(f + i + o);
		int second_number = 0;
		{
			for (char digit : std::to_string(d)) {
				second_number += digit - '0';
			}
			for (char digit : std::to_string(m)) {
				second_number += digit - '0';
			}
			second_number *= 64;
		}

		int third_number = ((static_cast<int>(std::toupper(f[0]) - 'A') + 1) * 256);
		int result = first_number + second_number + third_number;
		std::cout << int_to_hex(result) << '\n';
	}
}


int main() {
	solution();
}