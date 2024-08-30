#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <map>


class A {
public:
	using ul = unsigned long int;

	static void solution() {
		ul n, m;
		std::cin >> n >> m;
		std::vector<std::pair<ul, ul>> teachers;
		teachers.reserve(2 * m);

		ul i = 0, b, e;
		while (++i <= m) {
			std::cin >> b >> e;
			teachers.push_back(std::make_pair(b, 0));
			teachers.push_back(std::make_pair(e, 1));
		}

		std::sort(teachers.begin(), teachers.end());

		i = 0;
		ul amount_observed = 0, result = 0;
		while (i < 2 * m) {
			if (amount_observed == 0) {
				result += (i == 0) ? (teachers[i].first) : (teachers[i].first - teachers[i - 1].first - 1);
			}

			if (teachers[i].second == 0) {
				++amount_observed;
			} else {
				--amount_observed;
			}
			++i;
		}

		if (teachers.back().first < n - 1) {
			result += n - 1 - teachers.back().first;
		}

		std::cout << result << '\n';
	}
};


class B {
public:
	using ll = long long int;

	static void solution() {
		ll n, m;
		std::cin >> n >> m;
		std::vector<std::pair<ll, ll>> sections;
		sections.reserve(2 * n + m);
		
		std::vector<ll> dots_seq;
		dots_seq.reserve(m);
		std::unordered_map<ll, ll> dots;
		dots.reserve(m);

		ll i = 0, a, b;
		while (++i <= n) {
			std::cin >> a >> b;
			sections.push_back(std::make_pair(std::min(a, b), -1));
			sections.push_back(std::make_pair(std::max(a, b), 1));
		}
		i = 0;
		while (++i <= m) {
			std::cin >> a;
			dots_seq.push_back(a);
			dots[a] = 0;
			sections.push_back(std::make_pair(a, 0));
		}

		std::sort(sections.begin(), sections.end());

		i = 0;
		ll opened = 0;
		while (i < 2 * n + m) {
			if (sections[i].second == -1) {
				++opened;
			} else if (sections[i].second == 1) {
				--opened;
			} else {
				dots[sections[i].first] = opened;
			}
			++i;
		}

		for (auto dot : dots_seq) {
			std::cout << dots[dot] << ' ';
		}
	}
};


class C {
public:
	using ul = unsigned long int;

	static void solution() {
		ul n, d;
		std::cin >> n >> d;
		std::vector<ul> sorted_seq, ordered_seq;
		std::map<ul, ul> results_map;
		sorted_seq.reserve(n);
		ordered_seq.reserve(n);

		uint i = 0;
		ul x;
		while (++i <= n) {
			std::cin >> x;
			sorted_seq.push_back(x);
			ordered_seq.push_back(x);
		}

		std::sort(sorted_seq.begin(), sorted_seq.end());

		ul l = 0, r = 0;
		ul max_d = 0;
		while (l < n) {
			while (sorted_seq[r] - sorted_seq[l] <= d && r < n) {
				++r;
				results_map[sorted_seq[r - 1]] = r - l;
				max_d = std::max(r - l, max_d);
			}
			l = r;
		}

		std::cout << max_d << '\n';
		for (const auto &x : ordered_seq) {
			std::cout << results_map[x] << ' ';
		}
	}
};


class D {
public:
	using ul = unsigned long int;

	static uint bin_search(uint target, uint n, const std::vector<std::pair<ul, int>> &schedule) {
		uint l = target, r = n - 1, m;
		while (l != r) {
			m = (l + r) / 2;
			if (schedule[m].first < schedule[target].first + 5) {
				l = m + 1;
			} else {
				r = m;
			}
		}
		return (schedule[l].first == schedule[target].first) ? n : l;
	}

	static void solution() {
		uint n;
		std::cin >> n;
		std::vector<std::pair<ul, int>> schedule;
		std::vector<std::pair<ul, ul>> customers;
		schedule.reserve(n * 2);
		customers.reserve(n);

		uint i = 0;
		ul arrival_time, leave_time;
		while (++i <= n) {
			std::cin >> arrival_time >> leave_time;
			schedule.push_back(std::make_pair(arrival_time, -1));
			schedule.push_back(std::make_pair(leave_time, 1));
			customers.push_back(std::make_pair(arrival_time, leave_time));
		}
		std::sort(schedule.begin(), schedule.end());
		std::sort(customers.begin(), customers.end());

		uint first_max = 0, second_max = 0;
		uint first_begin = 0, second_begin = 0;
		uint listeners = 0, missed = 0;
		uint l = 0, r = 0;
		while (l < n * 2) {
			while (r < n * 2 && schedule[r].first < schedule[l].first + 5) {
				if (schedule[r].second == -1 && schedule[r].first == schedule[l].first) {
					++listeners;
				}
				if (schedule[r].second == -1 && schedule[r].first != schedule[l].first) {
					++missed;
				}
				
				if (schedule[r].second == 1 && missed > 0) {
					--missed;
				} else if (schedule[r].second == 1 && missed == 0) {
					--listeners;
				}
				++r;
			}
			if (r < n * 2) {
				if (listeners > first_max) {
					if (first_begin + 5 <= schedule[l].first) {
						second_max = first_max;
						second_begin = first_begin;
					} else {
						second_max = 0;
						second_begin = 0;
					}
					first_max = listeners;
					first_begin = schedule[l].first;
				} else if (listeners > second_max && first_begin + 5 <= schedule[l].first) {
					second_max = listeners;
					second_begin = schedule[l].first;
				}
			}
			listeners += missed;
			missed = 0;
			l = bin_search(l, r, schedule);
		}
		if (second_begin == 0) {
			second_begin = first_begin + 5;
		}

		uint common_listeners = 0;
		bool in_first = 0, in_second = 0; 
		for (const auto &c : customers) {
			if (c.first <= first_begin && c.second >= first_begin + 5) {
				in_first = 1;
			}
			if (c.first <= second_begin && c.second >= second_begin + 5) {
				in_second = 1;
			}
			if (in_first || in_second) {
				++common_listeners;
			}
			in_first = in_second = 0;
		}
		std::cout << common_listeners << ' ' 
				<< std::min(first_begin, second_begin) << ' '
				<< std::max(first_begin, second_begin) << '\n';
	}
};


class E {
public:
	using ull = unsigned long long int;

	class Time {
	public:
		uint hour;
		uint min;
		
		Time(const uint &hour, const uint &min): hour(hour), min(min) {}

		bool operator < (const Time &time) const {
			return (hour < time.hour || (hour == time.hour && min < time.min));
		}

		static const ull get_duration(const Time &start, const Time &end) {
			ull result = 0;
			result = (end.hour - start.hour) * 60 + (end.min - start.min);
			return result;
		}
	};

	static void solution() {
		uint n;
		std::cin >> n;
		std::vector<std::pair<Time, uint>> schedule;
		schedule.reserve(2 * n);
		uint i = 0;
		uint open_h, open_m, close_h, close_m;
		while (++i <= n) {
			std::cin >> open_h >> open_m >> close_h >> close_m;
			if (close_h == open_h && close_m == open_m) {
				open_h = open_m = close_m = 0;
				close_h = 24;
			}
			if (close_h < open_h || (close_h == open_h && close_m < open_m)) {
				schedule.push_back({ Time(open_h, open_m), 0});
				schedule.push_back({ Time(24, 0), 1});
				schedule.push_back({ Time(0, 0), 0});
				schedule.push_back({ Time(close_h, close_m), 1});
			} else {
				schedule.push_back({ Time(open_h, open_m), 0});
				schedule.push_back({ Time(close_h, close_m), 1});
			}
		}
		std::sort(schedule.begin(), schedule.end());

		ull result = 0;
		uint opened_count = 0;
		for (uint i = 0; i < schedule.size(); ++i) {
			if (schedule[i].second == 0) {
				++opened_count;
			}
			if (schedule[i].second > 0 && opened_count == n) {
				result += Time::get_duration(schedule[i - 1].first, schedule[i].first);
			}
			if (schedule[i].second > 0) {
				--opened_count;
			}
		}

		std::cout << result << '\n';
	}
};


int main() {
	E::solution();
}