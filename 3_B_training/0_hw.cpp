#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>


// "1. Гистограмма"
class A {
private:
	static inline std::ostringstream stream;

public:
	static void solution() {
		std::map<char, int> rates;
		int max_rate = 0;
		for (char a; std::cin >> a;) {
			++rates[a];
			if (max_rate < rates[a]) {
				max_rate = rates[a];
			}
		}
		while (max_rate > 0) {
			for (auto &[symbol, rate] : rates) {
				if (rate == max_rate) {
					stream << '#';
					--rate;
				} else {
					stream << ' ';
				}
			}
			--max_rate;
			stream << '\n';
		}
		for (auto &[symbol, rate]: rates) {
			stream << symbol;
		}
		std::cout << stream.str() << '\n';
	}
};


// "2. Красивая строка"
class B {
public:
	static void solution() {
		int k;
		std::string str;
		std::cin >> k >> str;
		std::map<char, int> rates;

		int max_subsequent_length = 0, result = 0;
		for (int l = 0, r = 0; r < std::ssize(str); ++r) {
			++rates[str[r]];
			max_subsequent_length = std::max(max_subsequent_length, rates[str[r]]);
			if (r - l + 1 - max_subsequent_length > k) {
				--rates[str[l]];
				++l;
			}
			result = std::max(result, r - l + 1);
		}
		std::cout << result << '\n';
	}
};


// "3. Коллекционер Диего"
class C {
private:
	static int find_last_less(const std::vector<int> &cards, int target) {
		int l = 0, r = std::ssize(cards) - 1, m;
		while (r > l + 1) {
			m = (l + r) / 2;
			if (cards[m] < target) {
				l = m;
			} else {
				r = m;
			}
		}
		if (cards[l] >= target) {
			return -1;
		}
		return (cards[r] < target) ? r : l;
	}


public:
	static void solution() {
		std::unordered_set<int> uniq_cards;
		std::vector<int> cards;
		int n, k;
		std::cin >> n;
		for (int card, i = 0; ++i <= n;) {
			std::cin >> card;
			if (!uniq_cards.contains(card)) {
				cards.push_back(card);
				uniq_cards.insert(card);
			}
		}
		std::ranges::sort(cards);
		
		std::cin >> k;
		for (int p, i = 0; ++i <= k;) {
			std::cin >> p;
			std::cout << find_last_less(cards, p) + 1 << '\n';
		}
	}
};


// "4. Контрольная работа"
class D {
public:
	static void solution() {
		int n, k, row, pos;
		std::cin >> n >> k >> row >> pos;
		int desk_num = row * 2 - (2 - pos);
		int variant = desk_num - (desk_num / k) * k;
		if (variant == 0) {
			variant = k;
		}
		
		int upper_desk, lower_desk, upper_row, lower_row;
		if (desk_num + k <= n) {
			upper_desk = desk_num + k;
			upper_row = (upper_desk + (upper_desk) % 2) / 2;
		} else {
			upper_desk = -1;
		}
		
		if (desk_num - k > 0) {
			lower_desk = desk_num - k;
			lower_row = (lower_desk + (lower_desk) % 2) / 2;
		} else {
			lower_desk = -1;
		}

		if (upper_desk == -1 && lower_desk == -1) {
			std::cout << "-1\n";
		} else if (upper_desk == -1 || (lower_desk != -1 && row - lower_row < upper_row - row)) {
			std::cout << lower_row << ' ' << 2 - (lower_desk % 2) << '\n';
		} else if (lower_desk == -1 || (upper_desk != -1 && row - lower_row >= upper_row - row)) {
			std::cout << upper_row << ' ' << 2 - (upper_desk % 2) << '\n';
		}
	}
};


// "5. Хорошая строка"
class E {
public:
	static void solution() {
		int n, result = 0;
		int first_sym, sym;
		std::cin >> n >> first_sym;
		for (int i = 1; i < n; ++i) {
			std::cin >> sym;
			result += std::min(first_sym, sym);
			first_sym = sym;
		}
		std::cout << result << '\n';
	}
};


// "6. Операционные системы lite"
class F {
private:
	static void find_intersections(
		std::vector<std::pair<std::pair<int, int>, bool>> &segments,
		const int start, const int end,
		int &closed_count
	) {
		for (auto &[segment, is_closed] : segments) {
			const int prev_start = segment.first;
			const int prev_end = segment.second;
			if (!is_closed && !(prev_end < start || prev_start > end)) {
				++closed_count;
				is_closed = true;
			}
		}
	}

public:
	static void solution() {
		int n, m;
		std::cin >> m >> n;
		std::vector<std::pair<std::pair<int, int>, bool>> segments;
		segments.reserve(n);

		int closed_count = 0;
		for (int i = 0, start, end; i < n; ++i) {
			std::cin >> start >> end;
			find_intersections(segments, start, end, closed_count);
			segments.push_back({ { start, end }, false });
		}
		std::cout << std::ssize(segments) - closed_count << '\n';
	}
};


// "7. SNTP"
class G {
private:
	struct Time {
	public:
		int h{0};
		int m{0};
		int s{0};

		Time() = default;
		
		Time(const int sec) {
			h = (sec / 3600) % 24;
			m = sec % 3600;
			s = m % 60;
			m /= 60;
		}

		void input() {
			std::string line;
			std::getline(std::cin, line);
			std::istringstream stream(line);

			std::string tmp;
			std::getline(stream, tmp, ':');
			h = std::stoi(tmp);
			std::getline(stream, tmp, ':');
			m = std::stoi(tmp);
			std::getline(stream, tmp, ':');
			s = std::stoi(tmp);
		}

		void print() const {
			if (h < 10) {
				std::cout << '0';
			}
			std::cout << h << ':';
			if (m < 10) {
				std::cout << '0';
			}
			std::cout << m << ':';
			if (s < 10) {
				std::cout << '0';
			}
			std::cout << s << '\n';
		}

		bool operator > (const Time &other) const {
			return (
				(h > other.h) ||
				(h == other.h && m > other.m) ||
				(h == other.h && m == other.m && s > other.s)
			);
		}

		int to_sec() const {
			return h * 3600 + m * 60 + s;
		}
	};

public:
	static void solution() {
		Time a, b, c;
		a.input();
		b.input();
		c.input();

		int delay;
		if (a > c) {
			delay = 24 * 3600 - a.to_sec() + c.to_sec(); 
		} else {
			delay = c.to_sec() - a.to_sec();
		}
		delay = std::round(static_cast<double>(delay) / 2);

		Time time(b.to_sec() + delay);
		time.print();
	}
};


// "8. Минимальный прямоугольник"
class H {
public:
	static void solution() {
		int left_x, right_x;
		int lower_y, upper_y;

		int k;
		std::cin >> k;
		std::cin >> left_x >> lower_y;
		right_x = left_x;
		upper_y = lower_y;

		for (int i = 1, x, y; i < k; ++i) {
			std::cin >> x >> y;
			if (x < left_x) {
				left_x = x;
			}
			if (x > right_x) {
				right_x = x;
			}
			if (y < lower_y) {
				lower_y = y;
			}
			if (y > upper_y) {
				upper_y = y;
			}
		}

		std::cout << left_x << ' ' << lower_y << ' ';
		std::cout << right_x << ' ' << upper_y << '\n';
	}
};


// "9. Сумма в прямоугольнике"
class I {
public:
	static void solution() { // non-working
		int n, m, k;
		std::cin >> n >> m >> k;
		std::vector<int> pref_sum(n * m + 1, 0);
		
		pref_sum[0] = 0;
		for (int i = 1, a; i <= n * m; ++i) {
			std::cin >> a;
			pref_sum[i] += pref_sum[i - 1] + a;
		}

		for (int i = 0; i < k; ++i) {
			int col_left, col_right, row_upper, row_lower;
			std::cin >> row_upper >> col_left >> row_lower >> col_right;

			int result = 0;
			for (int row = row_upper - 1; row <= row_lower - 1; ++row) {
				result += pref_sum[row * n + col_right] - pref_sum[row * n + col_left - 1];
			}
			std::cout << result << '\n';
		}
	}
};


// "10. Скучная лекция"
class J {
public:
	static void solution() {
		std::string word;
		std::cin >> word;

		std::map<char, size_t> chars;
		for (size_t i = 0; i < word.size() / 2; ++i) {
			chars[word[i]] += (i + 1) * (word.size() - i);
		}

		for (size_t i = word.size() - 1; i >= word.size() / 2; --i) {
			chars[word[i]] += (word.size() - i) * (i + 1);
		}

		for (const auto &[ch, count] : chars) {
			std::cout << ch << ": " << count << '\n';
		}
	}
};


int main() {
	J::solution();
}