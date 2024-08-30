#include <iostream>
#include <vector>
#include <cstdlib>
#include <tuple>
#include <string>
#include <sstream>
#include <fstream>

#include <unordered_set>
#include <set>
#include <map>
#include <algorithm>


class A {
public:
	using ulong = unsigned long int;
	static void solution() {
		int n, m;
		std::vector<ulong> tshirts, pants;
		
		std::cin >> n;
		tshirts.reserve(n);
		for (int i = 0; i < n; ++i) {
			ulong num;
			std::cin >> num;
			tshirts.push_back(num);
		}

		std::cin >> m;
		pants.reserve(m);
		for (int i = 0; i < m; ++i) {
			ulong num;
			std::cin >> num;
			pants.push_back(num);
		}

		int a, b, result_sum;
		a = b = 0;
		result_sum = -1;
		std::tuple<ulong, ulong> results;
		while ((a < n) && (b < m)) {
			if ((result_sum == -1) || (std::labs(tshirts[a] - pants[b]) < result_sum)) {
				result_sum = std::labs(tshirts[a] - pants[b]);
				results = std::make_tuple(tshirts[a], pants[b]);
			}
			if (result_sum == 0) {
				break;
			}

			if (tshirts[a] < pants[b]) {
				++a;
			} else {
				++b;
			}
		}
		std::cout << get<0>(results) << ' ' << get<1>(results);
	}
};


class B {
public:
	using ulong = unsigned long int;
	static void solution() {
		ulong n, k;
		std::cin >> n >> k;

		std::vector<ulong> pref;
		pref.reserve(n + 1);
		pref.push_back(0);
	
		int num;
		for (int i = 1; i < n + 1; ++i) {
			std::cin >> num;
			pref.push_back(num + pref[i - 1]);
		}

		int result  = 0;
		int r = 0;
		for (int l = 0; l < n + 1; ++l) {
			while ((r < n + 1) && (pref[r] - pref[l] < k)) {
				++r;
			}
			if (r == n + 1) {
				break;
			}
			if (pref[r] - pref[l] == k) {
				++result;
			}
		}
		std::cout << result;
	}
};


class C {
public:
	using ulong = unsigned long int;
	static void solution() {
		int n;
		std::cin >> n;
		std::vector<ulong> pref_straight;
		std::vector<ulong> pref_reverse;
		pref_straight.reserve(n + 1);
		pref_reverse.reserve(n + 1);
		pref_straight.push_back(0);
		pref_reverse.push_back(0);

		ulong x, y_prev, y;
		std::cin >> x >> y_prev;
		for (int i = 1; i < n; ++i) {
			std::cin >> x >> y;
			if (y < y_prev) {
				pref_straight.push_back(pref_straight[i - 1]);
				pref_reverse.push_back(pref_reverse[i - 1] + (y_prev - y));
			} else {
				pref_straight.push_back(pref_straight[i - 1] + (y - y_prev));
				pref_reverse.push_back(pref_reverse[i - 1]);
			}
			y_prev = y;
		}

		int m, a, b;
		std::cin >> m;
		std::string result = "";
		for (int i = 0; i < m; ++i) {
			std::cin >> a >> b;
			if (a < b) {
				result.append(std::to_string(pref_straight[b - 1] - pref_straight[a - 1]));
			} else {
				result.append(std::to_string(pref_reverse[a - 1] - pref_reverse[b - 1]));
			}
			result += "\n";
		}
		std::cout << result;
	}
};


class D {
public:
	using ulong = unsigned long int;
	static void solution() {
		ulong n, r_max;
		std::cin >> n >> r_max;
		ulong d;

		std::vector<ulong> rs;
		rs.reserve(n);

		/*
		std::ifstream cin("040.txt");
		std::string line, subline;

		while (std::getline(cin, line)) {
			std::stringstream ss(line);
			while (std::getline(ss, subline, ' ')) {
				rs.push_back(std::stoul(subline));
			}
		}
		*/
		for (ulong i = 0; i < n; ++i) {
			std::cin >> d;
			rs.push_back(d);
		}

		ulong r = 1;
		ulong result = 0;
		for (ulong l = 0; l < n - 1; ++l) {
			while ((r < n) && (rs[r] - rs[l] <= r_max)) {
				++r;
			}
			if (r == n) {
				break;
			}
			result += n - r;
		}
		std::cout << result;
	}
};


class E {
public:
	using ull = unsigned long long int;
	static void solution() {
		ull n, k;
		std::cin >> n >> k;
		std::vector<ull> trees;
		trees.reserve(n);
		ull i;
		while (std::cin >> i)
			trees.push_back(i);

		std::unordered_map<ull, ull> h;
		i = 0;
		while (i++ < k)
			h[i] = 0;

		ull l = 0, r = 1, f_l = 0, f_r = n;
		ull sum = trees[l];
		ull f_sum = (k + 1) * k / 2;
		++h[trees[l]];
		do {
			if (++h[trees[r]] == 1)
				sum += trees[r]; 
			if ((trees[r] == trees[l]) && (l != r)) {
				while (h[trees[l]] > 1) {
					--h[trees[l]];
					++l;
				}
			}
			if (sum == f_sum) {
				if (f_r - f_l > r - l) {
					f_l = l;
					f_r = r;
				}
				sum -= trees[l];
				--h[trees[l++]];
				while (h[trees[l]] > 1) {
					--h[trees[l]];
					++l;
				}
			}
		} while (++r < n);
		std::cout << ++f_l << ' ' << ++f_r << '\n';
	}
};


class F {
public:
	static void solution() {
		uint n, m;
		std::cin >> n;
		std::vector<uint> rooms;
		std::map<uint, uint> conds;

		uint i = 0, b, c;
		while (i++ < n) {
			std::cin >> b;
			rooms.push_back(b);
		}

		i = 0;
		std::cin >> m;
		while (i++ < m) {
			std::cin >> b >> c;
			if ((conds.count(b)) && (conds[b] <= c))
				continue;
			conds[b] = c;
		}
		std::sort(rooms.begin(), rooms.end());

		auto it = --conds.end();
		unsigned long long int result = 0, min = it->second;
		for (uint i = rooms.size(); i-- > 0;) {
			while ((it->first >= rooms[i]) && (it != conds.cbegin())) {
				if (it->second < min)
					min = it->second;
				--it;
			}
			if ((it == conds.cbegin()) && (it->first >= rooms[i]) && (it->second < min)) {
				min = it->second;
			}
			result += min;
		}
		std::cout << result << '\n';
	}

	static void test_from_file() {
		std::ifstream cin("013.txt");
		std::string line, subline;

		std::vector<uint> rooms;
		std::map<uint, unsigned long long int> conds;

		std::getline(cin, line);
		std::stringstream ss_rooms(line);
		while (std::getline(ss_rooms, subline, ' ')) {
			rooms.push_back(std::stoul(subline));
		}

		uint b, pos;
		unsigned long long int c;
		while (std::getline(cin, line)) {
			pos = line.find(' ');
			b = std::stoul(line.substr(0, pos));
			c = std::stoul(line.substr(pos + 1, line.length()));
			if ((conds.count(b)) && (conds[b] <= c))
				continue;
			conds[b] = c;
		}
		
		std::sort(rooms.begin(), rooms.end());

		auto it = --conds.end();
		unsigned long long int result = 0, min = it->second;
		for (uint i = rooms.size(); i-- > 0;) {
			while ((it->first >= rooms[i]) && (it != conds.cbegin())) {
				if (it->second < min)
					min = it->second;
				--it;
			}
			if ((it == conds.cbegin()) && (it->first >= rooms[i]) && (it->second < min)) {
				min = it->second;
			}
			result += min;
		}
		std::cout << result << '\n';
	}
};


class G {
private:
	using ull = unsigned long long int;
public:
	static void solution() {
		ull n, k;
		std::cin >> n >> k;
		std::map<ull, ull> cards_map;
		std::vector<ull> cards; 

		ull card;
		for (ull i = 0; ++i <= n;) {
			std::cin >> card;
			if (!cards_map.contains(card)) {
				cards_map.insert({ card, 0 });
				cards.push_back(card);
			}
			++cards_map[card];
		}

		std::sort(cards.begin(), cards.end());

		
		ull combinations = 0, repeated = 0;
		for (ull l = 0, r = l; l < cards.size(); ++l) {
			while (r < cards.size() && cards_map[cards[l]] * k >= cards_map[cards[r]]) {
				if (cards_map[cards[r]] >= 2) {
					++repeated;
				}
				++r;
			}

			if (cards_map[cards[l]] >= 2) {
				combinations += (r - l - 1) * 3;
				--repeated;
			}
			if (cards_map[cards[l]] >= 3) {
				++combinations;
			}

			combinations += (r - l - 1) * (r - l - 2) * 3;
			combinations += repeated * 3;
		}

		std::cout << combinations << '\n';
	}
};


class H {
public:
	using ul = unsigned long int;
	static void solution() {
		ul n, k;
		std::unordered_map<char, ul> rates;
		std::cin >> n >> k;
		rates.reserve(n / k);

		ul i = 0;
		std::vector<char> seq;
		seq.reserve(n);
		
		char elem;
		while (i++ < n) {
			std::cin >> elem;
			seq.push_back(elem);
		}

		ul l = 0, r = 0, res_len = 0, res_l = 0;
		bool breaked = false;
		while (l < n) {
			while (r < n) {
				if (!rates.count(seq[r])) {
					rates.insert({ seq[r], 0});
				}
				if (++rates[seq[r++]] > k) {
					breaked = true;
					break;
				}
			}

			ul len = r - l;
			if (breaked) {
				len -= 1;
			}

			if (res_len < len) {
				res_len = len;
				res_l = l + 1;
			}
			
			if (breaked) {
				while (rates[seq[r - 1]] > k) {
					--rates[seq[l++]];
				}
			} else {
				--rates[seq[l++]];
			}
			breaked = false;
		}
		std::cout << res_len << ' ' << res_l << '\n';
	}
};


class I {
private:
	using ul = unsigned long int;
public:
	static void solution() {
		ul k;
		std::cin >> k;
		std::string str;
		std::cin >> str;	
		ul matches_number = 0, result = 0;
		for (ul i = k; i < str.length(); ++i) {
			if (str[i] == str[i - k]) {
				++matches_number;
			} else {
				matches_number = 0;
			}

			result += matches_number;
		}
		std::cout << result << '\n';
	}
};


class J {
private:
	using dot_type = std::pair<long int, long int>;

public:
	// O(n^2 * log(n))
	static void solution() {
		uint n;
		std::cin >> n;
		std::vector<dot_type> dots;
		dots.reserve(n);

		long int x, y;
		for (uint i = 0; ++i <= n;) {
			std::cin >> x >> y;
			dots.push_back({ x, y });
		}

		long int result = 0;
		for (const auto &main_top : dots) {
			std::set<dot_type> used_dots;
			std::vector<long int> sides;
			for (const auto &top : dots) {
				if (top == main_top) {
					continue;
				}

				if (used_dots.contains(top)) {
					--result;
				}
				used_dots.insert({ top.first * (-1), top.second * (-1) });

				const long int x_vec = main_top.first - top.first;
				const long int y_vec = main_top.second - top.second;
				const long int side_length = x_vec * x_vec + y_vec * y_vec;
				sides.push_back(side_length);
			}
			std::sort(sides.begin(), sides.end());

			for (uint l = 0, r = 0; l < n - 1; ++l) {
				while (r < n - 1 && sides[r] == sides[l]) {
					++r;
				}
				result += r - l - 1;
				l = r - 1;
			}
		}

		std::cout << result << '\n';
	}
};


int main(){
	J::solution();
}