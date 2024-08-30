#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <array>
#include <utility>
#include <vector>


class A {
private:
	using ll = long long int;

public:
	static void solution() {
		ll n, d, a;
		std::cin >> n;
		std::map<ll, ll> colors;

		for (ll i = 0; ++i <= n;) {
			std::cin >> d >> a;
			if (!colors.contains(d)) {
				colors.insert({ d, 0 });
			}
			colors[d] += a;
		}

		for (const auto &it : colors) {
			std::cout << it.first << ' ' << it.second << '\n';
		}
	}
};


class B {
public:
	static void solution() {
		std::string line, name, number;
		std::map<std::string, long int> votes;

		while (std::getline(std::cin, line)) {
			std::istringstream stream(line);
			std::getline(stream, name, ' ');
			std::getline(stream, number, ' ');

			if (!votes.contains(name)) {
				votes.insert({ name, 0 });
			}
			votes[name] += std::stol(number);
		}

		for (const auto &it : votes) {
			std::cout << it.first << ' ' << it.second << '\n';
		}
	}
};


class C {
public:
	static void solution() {
		std::string line, word;
		std::unordered_map<std::string, long int> words;
		std::vector<std::pair<long int, std::string>> counts;

		while (std::getline(std::cin, line)) {
			std::istringstream stream(line);
			while (std::getline(stream, word, ' ')) {
				if (word == "") {
					continue;
				}
				if (!words.contains(word)) {
					words.insert({ word, 0 });
				}
				++words[word];
			}
		}

		counts.reserve(words.size());
		for (const auto &it : words) {
			counts.push_back({ it.second, it.first });
		}
		std::sort(counts.begin(), counts.end(), 
			[](
				const std::pair<long int, std::string> &pair_a,
				const std::pair<long int, std::string> &pair_b
			) {
				if (pair_a.first == pair_b.first) {
					return (pair_a.second < pair_b.second);
				}
				return (pair_a.first > pair_b.first);
			}
		);

		for (const auto &pair : counts) {
			std::cout << pair.second << '\n';
		}
	}
};


class D {
private:
	using ull = unsigned long long int;

public:
	static void solution() {
		std::vector<std::string> ordered_parties_seq;
		std::map<std::string, std::pair<ull, ull>> parties;
		std::vector<std::pair<ull, std::pair<std::string, ull>>> distribution;

		ull general_votes = 0, votes;
		std::string line;
		while (std::getline(std::cin, line)) {
			const auto delim_pos = line.find_last_of(' ');
			std::string party = line.substr(0, delim_pos);
			try {
				votes = std::stoull(line.substr(delim_pos + 1, line.length() - delim_pos - 1));
			} catch (std::invalid_argument err) {
				continue;
			}
			general_votes += votes;
			ordered_parties_seq.push_back(party);
			if (!parties.contains(party)) {
				parties.insert({ party, { 0, 0 } });
			}
			parties[party].first += votes;
		}

		ull selective_division = general_votes / 450;
		std::cout << selective_division << '\n';
		if (selective_division == 0) {
			selective_division = 1;
		}
		distribution.reserve(parties.size());
		ull general_places = 0;
		for (auto &party : parties) {
			ull remainder = party.second.first % selective_division;
			ull places = party.second.first / selective_division;
			general_places += places;

			distribution.push_back({ remainder, { party.first, places } });
			party.second.second = places;
		}
		
		if (general_places < 450) {
			std::sort(distribution.begin(), distribution.end(), 
				[](
					const std::pair<ull, std::pair<std::string, ull>> &elem_a,
					const std::pair<ull, std::pair<std::string, ull>> &elem_b
				) {
					if (elem_a.first == elem_b.first) {
						return (elem_a.second.first < elem_b.second.first);
					}
					return (elem_a.first > elem_b.first);
				}
			);

			while (general_places < 450) {
				for (auto &elem : distribution) {
					if (general_places == 450) {
						break;
					}
					++parties[elem.second.first].second;
					++general_places;
				}
			}
		}

		for (const auto &party : ordered_parties_seq) {
			std::cout << party << ' ' << parties[party].second << '\n';
		}
	}
};


class E {
private:
	static void read_line(std::string &container) {
		do {
			std::getline(std::cin, container);
		} while (container.empty());
	}

public:
	static void solution() {
		uint n;
		std::cin >> n;
		std::vector<uint> message_order;
		message_order.reserve(n);
		message_order.push_back(0); // skip 0 element

		std::map<uint, std::pair<std::string, uint>> message_freq;

		uint number;
		std::string theme, line_container;
		for (uint i = 0; ++i <= n;) { // [1, n]
			read_line(line_container);
			number = static_cast<uint>(std::stoi(line_container));
			if (number == 0) {
				read_line(theme);
				message_freq.insert({ i, { theme, 0 } });
				number = i;
			} else {
				number = message_order[number];
			}
			message_order.push_back(number);
			++message_freq[number].second;
			read_line(line_container); // skip the message content (even if it's empty)
		}

		uint max_freq = 0;
		std::string result_theme;
		for (const auto &it : message_freq) {
			if (it.second.second > max_freq) {
				result_theme = it.second.first;
				max_freq = it.second.second;
			}
		}

		std::cout << result_theme << '\n';
	}
};


int main() {
	E::solution();
}