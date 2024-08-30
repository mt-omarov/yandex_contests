#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>


class A {
private:
	using ll = long long int;

public:
	static void solution() {
		uint n;
		std::cin >> n;
		std::vector<std::pair<ll, int>> points;
		points.reserve(n * 2);

		ll begin, end;
		for (uint i = 0; i < n; ++i) {
			std::cin >> begin >> end;
			points.push_back({ begin, -1 });
			points.push_back({ end, 1 });
		}
		std::sort(points.begin(), points.end());

		ll result_length = 0, first_opened = 0;
		int opened_count = 0;
		for (const auto &point : points) {
			if (point.second > 0) {
				--opened_count;
				if (opened_count == 0) {
					result_length += point.first - first_opened;
				}
			} else if (point.second < 0) {
				if (opened_count == 0) {
					first_opened = point.first;
				}
				++opened_count;
			}
		}

		std::cout << result_length << '\n';
	}
};


class B {
public:
	static void solution() {
		uint n;
		std::cin >> n;
		std::vector<std::pair<long int, int>> points;
		points.reserve(2 * n);

		long int start, duration;
		for (uint i = 0; i < n; ++i) {
			std::cin >> start >> duration;
			points.push_back({ start + duration, -1 }); // firstly output the closure to account for all intersections
			points.push_back({ start, 1 });
		}
		std::sort(points.begin(), points.end());

		int result_count = 0, opened_count = 0;
		for (const auto &point : points) {
			if (point.second > 0) {
				++opened_count;
				if (opened_count > result_count) {
					result_count = opened_count;
				}
			} else {
				--opened_count;
			}
		}

		std::cout << result_count << '\n';
	}
};


class C {
public:
	static void solution() {
		uint m;
		std::cin >> m;
		std::vector<std::pair<long int, long int>> segs;
		long int l, r;
		std::cin >> l >> r;
		while (l != 0 || r != 0) {
			if (l < m && r > 0) {
				segs.push_back({ l, r });
			}
			std::cin >> l >> r;
		}
		std::sort(segs.begin(), segs.end());

		std::vector<std::pair<long int, long int>> result;
		long int current_right_border = 0;
		long int next_right_border = 0;
		std::pair<long int, long int> current_best_seg = { 0, 0 };
		for (const auto &seg : segs) {
			if (seg.first > current_right_border) {
				result.push_back(current_best_seg);
				current_right_border = next_right_border;
				if (current_right_border >= m) {
					break;
				}
			}
			if (seg.first <= current_right_border && seg.second > next_right_border) {
				next_right_border = seg.second;
				current_best_seg = seg;
			}
		}

		if (current_right_border < m) {
			current_right_border = next_right_border;
			result.push_back(current_best_seg);
		}
		if (current_right_border < m) {
			std::cout << "No solution\n";
		} else {
			std::sort(result.begin(), result.end());
			std::cout << result.size() << '\n';
			for (const auto &seg : result) {
				std::cout << seg.first << ' ' << seg.second << '\n';
			}
		}
	}
};


class D {
public:
	static void solution() {
		uint n, m;
		std::cin >> n >> m;
		std::map<long int, uint> kittens;
		std::map<long int, uint> pref_sums_kittens;

		long int a;
		for (uint i = 0; i < n; ++i) {
			std::cin >> a;
			if (!kittens.contains(a)) {
				kittens.insert({ a, 0 });
			}
			++kittens[a];
		}

		uint prev_count = 0;
		for (const auto &[x, count] : kittens) {
			pref_sums_kittens[x] = prev_count;
			prev_count += count;
		}
		pref_sums_kittens[pref_sums_kittens.rbegin()->first + 1] = prev_count;

		long int l, r;
		for (uint i = 0; i < m; ++i) {
			std::cin >> l >> r;
			auto end = pref_sums_kittens.upper_bound(r);
			if (end == pref_sums_kittens.end()) {
				end = --pref_sums_kittens.end();
			}
			auto begin = pref_sums_kittens.lower_bound(l);
			std::cout << end->second - begin->second << '\n';
		}
	}
};


int main() {
	D::solution();
}