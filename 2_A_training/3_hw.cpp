#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <vector>


class A {
private:
	static constexpr auto help_message = "HELP";
	static constexpr auto yes_message = "YES";
	static constexpr auto no_message = "NO";

	static void intersect(
		std::unordered_set<int> &answers, 
		std::unordered_map<int, int> &questions,
		std::unordered_set<int> &new_questions, bool yes_message = false
	) {
		if (yes_message) {
			for (auto it = answers.begin(); it != answers.end();) {
				if (!new_questions.contains(*it)) {
					questions[*it] = false;
					answers.erase(it++);
				} else {
					++it;
				}
			}
		} else {
			for (auto it = new_questions.begin(); it != new_questions.end(); ++it) {
				if (answers.contains(*it)) {
					questions[*it] = false;
					answers.erase(*it);
				}
			}
		}
	}

public:
	static void solution() {
		int n;
		std::unordered_map<int, int> questions;
		std::unordered_set<int> answers;
		std::cin >> n;

		for (int i = 1; i <= n; ++i) {
			answers.insert(i);
			questions[i] = true; // if the number was in a bad sample, set it to false
		}

		int a;
		std::string line;
		for (std::getline(std::cin, line); line != help_message; std::getline(std::cin, line)) {
			if (line.empty()) {
				continue;
			}
			std::istringstream ss(line);
			std::unordered_set<int> new_questions;
			while (ss >> a) {
				if (questions[a]) { // use only those numbers that can be answers and were not in a bad sample
					new_questions.insert(a);
				}
			}

			if (new_questions.size() == 0) {
				std::cout << no_message << '\n';
			} else if (new_questions.size() > std::ssize(answers) - new_questions.size()) {
				intersect(answers, questions, new_questions, true);
				std::cout << yes_message << '\n';
			} else {
				intersect(answers, questions, new_questions, false);
				std::cout << no_message << '\n';
			}
		}

		std::vector<int> results;
		results.reserve(answers.size());
		results.insert(results.begin(), answers.begin(), answers.end());
		std::ranges::sort(results);
		for (const auto &number : results) {
			std::cout << number << ' ';
		}
		std::cout << '\n';
	}
};


class B { // skip
public:
	static void solution() { // non-working
		int n, m;
		std::unordered_set<int> tops;
		std::unordered_map<int, std::unordered_set<int>> edges;

		std::cin >> n >> m;

		int edges_number = 0;
		for (int a, b; std::cin >> a >> b;) {
			if (a == b) {
				continue;
			}

			int key = std::min(a, b), value = std::max(a, b);
			if (!edges.contains(key)) {
				edges[key] = std::unordered_set<int>();
			}
			if (!edges[key].contains(value)) {
				edges[key].insert(value);
				++edges_number;
			}

			tops.insert(key);
			tops.insert(value);
		}



		std::cout << tops.size() << ' ' << edges_number << '\n' << '\n';
		for (const auto &[first_top, tops] : edges) {
			for (const auto &second_top : tops) {
				std::cout << first_top << ' ' << second_top << '\n';
			}
		}
		std::cout << '\n';
	}
};


class C {
public:
	// complexity: O(n * k)
	static void solution() {
		long int n, k;
		std::cin >> n >> k;
		std::unordered_set<int> results;
		for (int a, b, i = 0; i < k; ++i) {
			std::cin >> a >> b;
			for (int j = a; j <= n; j += b) {
				int day = j - (j / 7) * 7;
				if (day == 0 || day == 6) {
					continue;
				}
				results.insert(j);
			}
		}
		std::cout << results.size() << '\n';
	}
};


class D { // skip (strange task condition)
private:
	static void input_scores(
		std::vector<int> &scores,
		std::unordered_map<int, int> &scores_counts
	) {
		std::string line;
		while (line.empty()) {
			std::getline(std::cin, line);
		}
		std::istringstream iss(line);
		int score, i = 0;
		while (iss >> score) {
			++scores_counts[score];
			scores[i] = score;
			++i;
		}
	}

	static int find_winner(
		int n, std::vector<int> &scores,
		std::unordered_map<int, int> &scores_counts
	) {
		int winner = -1;
		for (int player = 0; player < n; ++player) {
			if (scores_counts[scores[player]] == 1 && (winner == -1 || scores[player] < scores[winner])) {
				winner = player;
			}
		}

		return winner;
	}


public:
	static void solution() { // non-working
		int n;
		std::cin >> n;
		int winner_1, winner_1_scores = 0;
		{
			std::unordered_map<int, int> scores_counts;
			std::vector<int> scores(n, 0);
			input_scores(scores, scores_counts);
			winner_1 = find_winner(n, scores, scores_counts);
			if (winner_1 != -1) {
				winner_1_scores = scores[winner_1];
			}
		}
		
		std::unordered_map<int, int> scores_counts;
		std::vector<int> scores(n, 0);
		input_scores(scores, scores_counts);

		int best_bad_players_amount = -1, best_last_player_score = 0;
		for (int i = 0; i <= 101; ++i) {
			scores[n - 1] = i;
			++scores_counts[i];

			int winner = find_winner(n, scores, scores_counts);
			int last_player_scores = 0;
			if (winner_1 == n - 1) {
				last_player_scores += winner_1_scores;
			}
			if (winner == n - 1) {
				last_player_scores += i;
			}

			int bad_players_amount = 0;
			for (int j = 0; j < n - 1; ++j) {
				int score = 0;
				if (j == winner_1) {
					score += winner_1_scores;
				}
				if (j == winner) {
					score += scores[j];
				}
				if (score < last_player_scores) {
					++bad_players_amount;
				}
			}

			if (best_bad_players_amount == -1 || bad_players_amount > best_bad_players_amount) {
				best_bad_players_amount = bad_players_amount;
				best_last_player_score = i;
			}

			--scores_counts[i];
		}

		std::cout << best_last_player_score << '\n';
	}
};


class E {
private:
	using ull = unsigned long long int;
	
	static ull fast_pow(ull base, ull exp) {
		if (exp == 0) {
			return 1;
		} else if (exp == 1) {
			return base;
		}
		ull one_half = fast_pow(base, exp / 2);
		return one_half * one_half * fast_pow(base, exp % 2);
	}

	// we could just write: mod_const = 1000000000;
	static inline const ull mod_const = fast_pow(10, 9);
	static inline const std::array<ull, 3> mod_consts {
		mod_const + 7,
	 	mod_const + 11,
	 	mod_const + 13
	};

	static void prepare_fibonacci_mods(std::array<std::unordered_set<ull>, 3> &fibonacci_mods) {
		for (int mod = 0; mod < 3; ++mod) {
			ull f_1 = 1, f_2 = 1;
			fibonacci_mods[mod] = std::unordered_set<ull>();
			fibonacci_mods[mod].insert(f_1);
			for (int i = 0; i <= 40000; ++i) {
				ull tmp = f_2;
				f_2 = (f_1 + f_2) % mod_consts[mod];
				f_1 = tmp;
				fibonacci_mods[mod].insert(f_2);
			}
		}
	}

public:
	static void solution() {
		std::ios::sync_with_stdio(false); // optimize iostream
		std::cin.tie(NULL);
		std::cout.tie(NULL);
		
		ull n;
		std::cin >> n;
		std::array<std::unordered_set<ull>, 3> fibonacci_mods;
		prepare_fibonacci_mods(fibonacci_mods);

		std::string output_string; 
		output_string.reserve(n * 3);
		
		std::array<ull, 3> number_mods;
		std::string line;
		std::istringstream iss(line);
		while (std::getline(std::cin, line)) {
			if (line.empty()) {
				continue;
			}
			number_mods = {0, 0, 0};
			iss.clear(); // optimize istringstream (the creation of the iss in each cycle is slow)
			iss.str(line);
			char digit;
			while (iss.get(digit)) { // get only one character per operation
				for (int j = 0; j < 3; ++j) {
					number_mods[j] = (number_mods[j] * 10 + (static_cast<ull>(digit - '0'))) % mod_consts[j];
				}
			}
			bool result = true;
			for (int j = 0; j < 3; ++j) {
				result *= fibonacci_mods[j].contains(number_mods[j]);
			}
			output_string += ((result) ? "Yes\n" : "No\n");
		}

		std::cout << output_string;
	}
};


int main() {
	D::solution();
}