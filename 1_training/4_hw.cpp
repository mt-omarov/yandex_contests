#include <iostream>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <string>
#include <iterator>
#include <sstream>
#include <string_view>
#include <cctype>
#include <algorithm>


class E {
public:
	using ul = unsigned long int;
	static void solution() {
		uint n;
		ul w, h;
		std::cin >> n;
		std::unordered_map<ul, ul> blocks;

		for (int i = 0; ++i <= n;) {
			std::cin >> w >> h;
			if (!blocks.contains(w)) {
				blocks.insert({ w, h });
			} else if (blocks[w] < h) {
				blocks[w] = h;
			}
		}

		ul result_height = 0;
		for (auto it = blocks.cbegin(); it != blocks.cend(); ++it) {
			result_height += it->second;
		}
		std::cout << result_height << '\n';
	}
};


class F {
public:
	using ul = unsigned long int;
	static void solution() {
		std::map<std::string, std::map<std::string, ul>> shoppers;
		std::string line;
		while (std::getline(std::cin, line)) {
			std::istringstream iss(line);
			std::string name, product;
			uint i = 0;
			auto it = std::istream_iterator<std::string>(iss);
			while (it != std::istream_iterator<std::string>() && i < 2) {
				if (i == 0) {
					name = *it;
				} else {
					product = *it;
				}
				++it;
				++i;
			}
			if (!shoppers.contains(name)) {
				shoppers.insert({ name, std::map<std::string, ul>() });
			}
			if (!shoppers[name].contains(product)) {
				shoppers[name].insert({ product, 0 });
			}
			shoppers[name][product] += std::stoul(*it);
		}

		for (auto const &shopper : shoppers) {
			std::cout << shopper.first << ":\n";
			for (auto const &product : shopper.second) {
				std::cout << product.first << ' ' << product.second << '\n';
			}
		}
	}
};


class G {
private:
	inline static std::map<std::string, long int> accs;
	inline static std::map<const char, const std::string> ops {
		{ 'D', std::string("DEPOSIT") },
		{ 'I', std::string("INCOME") },
		{ 'B', std::string("BALANCE") },
		{ 'T', std::string("TRANSFER") },
		{ 'W', std::string("WITHDRAW") }
	};

	static void income(const long int &p) {
		for (auto &acc : accs) {
			if (acc.second > 0) {
				acc.second += acc.second * p / 100;
			}
		}
	}

	static void balance(const std::string &name) {
		if (!accs.contains(name)) {
			std::cout << "ERROR\n";
			return;
		}
		std::cout << accs[name] << '\n';
	}

	static void deposit(const std::string &name, const long int &sum) {
		if (!accs.contains(name)) {
			accs.insert({ name, 0 });
		}
		accs[name] += sum;
	}

	static void widthraw(const std::string &name, const long int &sum) {
		if (!accs.contains(name)) {
			accs.insert({ name, 0 });
		}
		accs[name] -= sum;
	}

	static void transfer(const std::string &from, const std::string &to, const long int &sum) {
		widthraw(from, sum);
		deposit(to, sum);
	}

public:
	static void solution() {
		std::string line;
		while (std::getline(std::cin, line)) {
			std::stringstream ss(line);
			std::string op;
			std::getline(ss, op, ' ');
			if (op == ops['I']) {
				std::string p;
				std::getline(ss, p, ' ');
				income(std::stol(p));
				continue;
			}
			std::string from_name;
			std::getline(ss, from_name, ' ');
			if (op == ops['B']) {
				balance(from_name);
				continue;
			}

			if (op == ops['T']) {
				std::string to_name, sum;
				std::getline(ss, to_name, ' ');
				std::getline(ss, sum, ' ');
				transfer(from_name, to_name, std::stol(sum));
				continue;	
			}

			std::string sum;
			std::getline(ss, sum, ' ');
			if (op == ops['D']) {
				deposit(from_name, std::stol(sum));
			} else {
				widthraw(from_name, std::stol(sum));
			}
		}
	}
};


class H {
private:
	using ul = unsigned long int;
public:
	// TL: O(g * s) = O(9 * 10^9)
	static void first_solution() {
		ul g, s;
		std::cin >> g >> s;
		std::string W, S;
		std::cin >> W >> S;

		std::map<const char, ul> W_content, S_content, S_positions;
		for (const auto &literal : W) {
			if (!W_content.contains(literal)) {
				W_content.insert({ literal, 0 });
			}
			++W_content[literal];
		}
		
		ul combinations = 0;
		for (ul i = 0; i < S.size(); ++i) {
			const char &literal = S[i];
			if (!W_content.contains(literal)) {
				if (S_content.size() > 0) {
					S_content.clear();
					S_positions.clear();
				}
				continue;
			}

			if (!S_content.contains(literal)) {
				S_content.insert({ literal, 1 });
				S_positions.insert({ literal, i });
			} else if (W_content[literal] <= S_content[literal]) {
				ul start = S_positions[literal];
				ul &end = i;
				for (auto &it : S_content) {
					if (S_positions[it.first] <= start) {
						S_positions.erase(it.first);
					}
				}
				S_content.clear();
				for (ul j = start + 1; j <= end; ++j) {
					if (!S_content.contains(S[j])) {
						S_content.insert({ S[j], 0 });
					}
					++S_content[S[j]];
					if (!S_positions.contains(S[j])) {
						S_positions.insert({ S[j], j });
					}
				}
			} else {
				++S_content[literal];
			}
			combinations += static_cast<ul>((S_content == W_content));
		}

		std::cout << combinations << '\n';
	}

	static void solution() {
		ul g, s;
		std::cin >> g >> s;
		std::string W, S;
		W.reserve(g); S.reserve(s);
		std::cin >> W >> S;

		std::map<const char, ul> W_content, S_content;
		for (const auto &literal : W) {
			if (!W_content.contains(literal)) {
				W_content.insert({ literal, 0 });
			}
			++W_content[literal];
		}

		for (ul i = 0; i < g; ++i) {
			if (!W_content.contains(S[i])) {
				continue;
			}
			if (!S_content.contains(S[i])) {
				S_content.insert({ S[i], 0 });
			}
			++S_content[S[i]];
		}

		ul combinations = 0, coincidences = 0;
		for (auto const &it : S_content) {
			if (W_content[it.first] == it.second) {
				++coincidences;
			}
		}

		if (coincidences == W_content.size()) {
			++combinations;
		}

		for (ul i = g; i < s; ++i) {
			const auto &new_literal = S[i];
			const auto &first_literal = S[i-g];

			if (S_content.contains(first_literal)) {
				if (S_content[first_literal] == W_content[first_literal]) {
					--coincidences;
				}
				--S_content[first_literal];
				if (S_content[first_literal] == W_content[first_literal]) {
					++coincidences;
				}
			}
			
			if (!W_content.contains(new_literal)) {
				continue;
			}
			if (!S_content.contains(new_literal)) {
				S_content.insert({ new_literal, 0 });
			} else if (S_content[new_literal] == W_content[new_literal]) {
				--coincidences;
			}
			++S_content[new_literal];
			if (S_content[new_literal] == W_content[new_literal]) {
				++coincidences;
			}

			if (coincidences == W_content.size()) {
				++combinations;
			}
		}

		std::cout << combinations << '\n';
	}
};


class I {
private:
	static char tolower(const char &literal) {
		return static_cast<char>(std::tolower(static_cast<unsigned char>(literal)));
	}

	static bool isupper(const char &literal) {
		return std::isupper(static_cast<unsigned char>(literal));
	}

public:
	static void solution() {
		uint n;
		std::cin >> n;
		std::unordered_map<std::string, std::unordered_set<uint>> dict;

		std::string word;
		for (uint i = 0; ++i <= n;) {
			std::cin >> word;
			uint j;
			for (j = 0; j < word.size(); ++j) {
				if (isupper(word[j])) {
					break;
				}
			}
			word[j] = tolower(word[j]);
			if (!dict.contains(word)) {
				dict.insert({ word, std::unordered_set<uint>() });
			}
			dict[word].insert(j);
		}

		unsigned long int result = 0;
		while (std::cin >> word) {
			uint accents_amount = 0;
			int accent_i = -1;
			for (uint i = 0; i < word.length(); ++i) {
				if (!isupper(word[i])) {
					continue;
				}
				++accents_amount;
				if (accent_i == -1) {
					accent_i = i;
				} else {
					break;
				}
			}
			if (accents_amount == 0 || accents_amount > 1) {
				++result;
			} else {
				word[accent_i] = tolower(word[accent_i]);
				if (dict.contains(word) && !dict[word].contains(accent_i)) {
					++result;
				}
			}
		}

		std::cout << result << '\n';
	}
};


class J {
private:
	using ul = unsigned long int;

	static bool isalpha(const char &literal) {
		return std::isalpha(static_cast<unsigned char>(literal));
	}

	static bool isdigit(const char &literal) {
		return std::isdigit(static_cast<unsigned char>(literal));
	}
	
	static char tolower(const char &literal) {
		return static_cast<char>(std::tolower(static_cast<unsigned char>(literal)));
	}

	static bool isupper(const char &literal) {
		return std::isupper(static_cast<unsigned char>(literal));
	}

	static void str_tolower(std::string &word) {
		std::transform(
			word.begin(), word.end(), word.begin(),
			[](const char &literal) { return (isupper(literal) ? tolower(literal) : literal); }
		);
	}

public:
	static void solution() {
		uint n;
		bool case_sensitive, starts_with_number;
		std::string C, D;
		std::cin >> n >> C >> D;
		case_sensitive = (C == "yes");
		starts_with_number = (D == "yes");

		std::unordered_set<std::string> key_words;
		key_words.reserve(n);

		std::string word;
		for (uint i = 0; ++i <= n;) {
			std::cin >> word;
			if (!case_sensitive) {
				str_tolower(word);
			}
			if (!key_words.contains(word)) {
				key_words.insert(word);
			}
		}

		std::unordered_map<std::string, std::pair<ul, ul>> ids;
		std::string line, max_id = "";
		ul l, r, i = 0;
		while (std::getline(std::cin, line)) {
			for (l = 0; l < line.length(); ++l) {
				if (!isdigit(line[l]) && !isalpha(line[l]) && line[l] != '_') {
					continue;
				}
				r = l + 1;
				while (r < line.length() && (isdigit(line[r]) || isalpha(line[r]) || line[r] == '_')) {
					++r;
				}

				if ((r - l == 1 || !starts_with_number) && isdigit(line[l])) {
					l = r;
					continue;
				}
				
				++i;
				word = line.substr(l, r - l);
				if (!case_sensitive) {
					str_tolower(word);
				}
				if (key_words.contains(word)) {
					l = r;
					continue;
				}

				if (!ids.contains(word)) {
					ids.insert({ word, { 0, i } });
				}
				++ids[word].first;
				if (max_id == "" || ids[max_id].first < ids[word].first ||
					(ids[max_id].first == ids[word].first && ids[max_id].second > ids[word].second)) {
					max_id = word;
				}
				
				++i;
				l = r;
			}
		}
		std::cout << max_id << '\n';
	}
};


int main() {
	J::solution();
}