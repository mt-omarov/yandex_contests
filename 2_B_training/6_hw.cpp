#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>


namespace binary_searches {

// left binary search (first greater than or equal to target)
static long long int bin_search_first_ge(
	const std::vector<long long int> &nums, 
	const long long int &target
) {
	long long int l = 0, r = std::ssize(nums) - 1, m;
	while (l < r) {
		m = (l + r) / 2;
		if (nums[m] >= target) {
			r = m;
		} else {
			l = m + 1;
		}
	}
	return l;
}

// right binary search (last greater than or equal to target)
static long long int bin_search_last_ge(
	const std::vector<long long int> &nums,
	const long long int &target
) {
	long long int l = 0, r = std::ssize(nums) - 1, m;
	while (l < r) {
		m = (l + r + 1) / 2;
		if (nums[m] <= target) {
			l = m;
		} else {
			r = m - 1;
		}
	}
	return l;
}

} // namespace


class A {
private:
	using ll = long long int;

public:
	static void solution() {
		ll n, k, num;
		std::cin >> n;
		std::vector<ll> nums(n, 0);
		for (uint i = 0; i < n; ++i) {
			std::cin >> num;
			nums[i] = num;
		}
		std::sort(nums.begin(), nums.end());

		std::cin >> k;
		ll l, r, l_i, r_i;
		for (uint i = 0; i < k; ++i) {
			std::cin >> l >> r;
			l_i = binary_searches::bin_search_first_ge(nums, l);
			r_i = binary_searches::bin_search_last_ge(nums, r);
			if (nums[l_i] < l || nums[r_i] > r) {
				std::cout << 0 << ' ';
			} else {
				std::cout << r_i + 1 - l_i << ' ';
			}
		}
	}
};


class B {
private:
	using ll = long long int;

public:
	static void solution() {
		ll n, m;
		std::cin >> n;
		std::vector<ll> nums(n, 0);
		for (ll i = 0, a; i < n; ++i) {
			std::cin >> a;
			nums[i] = a;
		}

		std::cin >> m;
		for (ll i = 0, a, l_i, r_i; i < m; ++i) {
			std::cin >> a;
			l_i = binary_searches::bin_search_first_ge(nums, a);
			r_i = binary_searches::bin_search_last_ge(nums, a);
			if (nums[l_i] != a) {
				std::cout << 0 << ' ' << 0;
			} else {
				std::cout << l_i + 1 << ' ' << r_i + 1;
			}
			std::cout << '\n';
		}
	}
};


class C {
private:
	static constexpr double eps = 0.00000001;

public:
	static void solution() {
		std::ifstream in("cubroot.in");
		double a, b, c, d;
		in >> a >> b >> c >> d;
		if (a < 0) {
			a *= -1;
			b *= -1;
			c *= -1;
			d *= -1;
		}

		double l = -2000, r = 2000, m;
		while (r - l > eps) {
			m = (l + r) / 2;
			double result = (a * m * m * m) + (b * m * m) +(c * m) + d;
			if (result > 0) {
				r = m;
			} else {
				l = m;
			}
		}
		l = (l + r) / 2.0;
		std::ofstream out("cubroot.out");
		out << std::setprecision(11) << l << '\n';
	}
};


class E {
private:
	using ll = long long int;

	static bool check(const std::vector<ll> &points, const ll &length, const ll &k) {
		ll segments_count = 0, i = 0;
		while (i < points.size() && segments_count <= k) {
			ll segment_end = points[i] + length;
			while (points[i] <= segment_end && i < points.size()) {
				++i;
			}
			++segments_count;
		}
		
		return (segments_count <= k);
	}

public:
	static void solution() {
		ll n, k;
		std::cin >> n >> k;
		std::vector<ll> points(n, 0);
		for (ll i = 0, p; i < n; ++i) {
			std::cin >> p;
			points[i] = p;
		}
		std::sort(points.begin(), points.end());

		ll l = 0, r = points[n - 1] - points[0], m;
		while (l < r) {
			m = (l + r) / 2;
			if (check(points, m, k)) {
				r = m;
			} else {
				l = m + 1;
			}
		}

		std::cout << l << '\n';
	}
};


int main() {
	E::solution();
}