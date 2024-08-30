#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


class A {
public:
	using ll = long long int;

	// binary search from lecture
	static uint bin_search(std::vector<ll> &seq, ll &num) {
		uint l = 1, r = seq.size() - 1;
		while (l != r) {
			uint m = (l + r) / 2;
			if (seq[m] >= num) {
				r = m;
			} else {
				l = m + 1;
			}
		}
		return l;
	}

	static void solution() {
		uint n, k;
		std::cin >> n >> k;
		std::vector<ll> seq;
		seq.reserve(n);

		uint i = 0;
		ll num;
		while (i++ < n) {
			std::cin >> num;
			seq.push_back(num);
		}
		std::sort(seq.begin(), seq.end());
		
		i = 0;
		while (i++ < k) {
			std::cin >> num;
			std::cout << ((seq[bin_search(seq, num)] == num) ? "YES\n" : "NO\n");
		}
	}
};


class B {
public:
	using ll = long long int;

	// universal search with rules: { seq[l] <= num and seq[r] > num }
	static uint bin_search(std::vector<ll> &seq, ll &num) {
		uint l = 0, r = std::ssize(seq) - 1;
		uint m;
		while (r - l > 1) {
			m = (l + r) / 2;
			if (seq[m] < num) {
				l = m;
			} else {
				r = m;
			}
		}
		return (num - seq[l] <= seq[r] - num) ? l : r;
	}

	static void solution() {
		uint n, k;
		std::cin >> n >> k;
		std::vector<ll> seq;
		seq.reserve(n);

		uint i = 0;
		ll num;
		while (i++ < n) {
			std::cin >> num;
			seq.push_back(num);
		}
		
		i = 0;
		while (i++ < k) {
			std::cin >> num;
			std::cout << seq[bin_search(seq, num)] << '\n';
		}
	}
};


class C {
public:
	using ull = unsigned long long int;

	static ull bin_search(ull &w, ull &h, ull &n) {
		ull l = 0, r = std::max(w, h) * (std::sqrt(n) + 1), m;
		while (r > l + 1) {
			m = (l + r) / 2;
			if ((m / w) * (m / h) < n) {
				l = m;
			} else {
				r = m;
			}
		}
		return ((l / w) * (l / h) >= n) ? l : r;
	}

	static void solution() {
		ull w, h, n;
		std::cin >> w >> h >> n;
		std::cout << bin_search(w, h, n) << '\n';
	}
};


class D {
public:
	using ull = unsigned long long int;

	static ull bin_search(ull &n, ull &a, ull &b, ull &w, ull &h) {
		ull l = 0, r = (w / a) * (h / b) - n;
		r = std::max(r * a, r * b) / 2;
		ull m;

		while (r > l + 1) {
			m = (r + l) / 2;
			if ((w / (a + 2 * m)) * (h / (b + 2 * m)) >= n) {
				l = m;
			} else {
				r = m;
			}
		}
		return (((w / (a + 2 * r)) * (h / (b + 2 * r))) >= n) ? r : l;
	}

	static void solution() {
		ull n, a, b, w, h;
		std::cin >> n >> a >> b >> w >> h;
		ull res_hor = bin_search(n, a, b, w, h), res_ver = bin_search(n, b, a, w, h);
		std::cout << ((res_hor > res_ver) ? res_hor : res_ver) << '\n';
	}
};


class E {
public:
	using ull = unsigned long long int;

	static bool check(ull &m, ull &a, ull &b, ull &c) {
		long double res = (long double) (5 * m + 2 * a + 3 * b + 4 * c) / (a + b + c + m);
		return static_cast<ull>(std::round(res)) < 4;
	}

	static ull bin_search(ull &a, ull &b, ull &c) {
		ull l = 1, r = a + b + c, m;
		while (r > l + 1) {
			m = (l + r) / 2;
			if (check(m, a, b, c)) {
				l = m;
			} else {
				r = m;
			}
		}
		return check(l, a, b, c) ? r : l;
	}

	static void solution() {
		ull a, b, c;
		std::cin >> a >> b >> c;
		std::cout << bin_search(a, b, c) << '\n';
	}
};


class F {
public:
	using ul = unsigned long int;

	static ul bin_search(const ul &n, const ul &x, const ul &y) {
		ul l = 0, r = std::max(x, y) * (n - 1), m;
		while (r > l + 1) {
			m = (l + r) / 2;
			if ((m / x) + (m / y) < n - 1) {
				l = m;
			} else {
				r = m;
			}
		}
		return std::min(x, y) + r;
	}

	static void solution() {
		ul n, x, y;
		std::cin >> n >> x >> y;
		std::cout << bin_search(n, x, y) << '\n'; 
	}
};


class G {
public:
	using ull = unsigned long long int;

	static ull bin_search(const ull &n, const ull &m, const ull &t) {
		ull l = 1, r = std::min(n, m), d;
		while (r > l + 1) {
			d = (l + r) / 2;
			if ((d * 2) * (n + m - 2 * d) < t) {
				l = d;
			} else {
				r = d;
			}
		}
		l = ((l * 2) * (n + m - 2 * l) > t) ? 0 : l;
		return ((r * 2) * (n + m - 2 * r) <= t) ? r : l;
	}

	static void solution() {
		ull n, m, t; 
		std::cin >> n >> m >> t;
		std::cout << bin_search(n, m, t) << '\n';
	}
};


class H {
public:
	using ull = unsigned long long int;

	static bool check(const ull &m, const uint &k, const std::vector<ull> &segments) {
		ull res = 0;
		size_t i = 0;
		while (segments[i] / m > 0 && i < segments.size() && res < k) {
			res += segments[i++] / m;
		}
		return res >= static_cast<ull>(k);
	}

	static ull bin_search(const uint &k, const std::vector<ull> &segments) {
		ull l = 0, r = segments[0], m;
		while (l != r) {
			m = (l + r + 1) / 2;
			if (!check(m, k, segments)) {
				r = m - 1;
			} else {
				l = m;
			}
		}
		return l;
	}

	// complexity: O(n * log(n))
	static void solution() {
		uint n, k;
		std::cin >> n >> k;
		std::vector<ull> segments;
		segments.reserve(n);
		uint i = 0;
		ull l;

		while (i++ < n) {
			std::cin >> l;
			segments.push_back(l);
		} 
		std::sort(segments.begin(), segments.end(), std::greater<ull>());
		std::cout << bin_search(k, segments) << '\n';
	}
};


class I {
public:
	using ul = unsigned long int;

	static bool check(const ul &diff, const ul &R, const ul &C, const std::vector<ul> &group) {
		ul amount = 0, i = 0;
		while (i < std::ssize(group) - C + 1 && amount < R) {
			if (group[i + C - 1] - group[i] <= diff) {
				i += C;
				++amount;
			} else {
				++i;
			}
		}
		return amount >= R;
	}

	static ul bin_search(const ul &R, const ul &C, const std::vector<ul> &group) {
		ul l = 0, r = group[std::ssize(group) - 1] - group[0], m;
		while (l != r) {
			m = (l + r) / 2;
			if (check(m, R, C, group)) {
				r = m;
			} else {
				l = m + 1;
			}
		}
		return l;
	}

	static void solution() {
		ul N, R, C;
		std::cin >> N >> R >> C;
		std::vector<ul> group;
		group.reserve(N);
		
		ul h, i = 0;
		while (i++ < N) {
			std::cin >> h;
			group.push_back(h);
		}
		std::sort(group.begin(), group.end());
		std::cout << bin_search(R, C, group) << '\n';
	}
};


// non-working
class J {
public:

	static int lbin_search(const std::vector<int> &seq, const int &pillar) {
		int l = 0, r = std::ssize(seq) - 1, m;
		while (l != r) {
			m = (l + r) / 2;
			if (seq[m] >= pillar) {
				r = m;
			} else {
				l = m + 1;
			}
		}
		return l;
	}

	static int rbin_search(const std::vector<int> &seq, const int &pillar) {
		int l = 0, r = std::ssize(seq) - 1, m;
		while (l != r) {
			m = (l + r + 1) / 2;
			if (seq[m] <= pillar) {
				l = m;
			} else {
				r = m - 1;
			}
		}
		return l;
	}


	static int find_median(const std::vector<int> &first, const std::vector<int> &second, const int &L) {
		int l = std::min(first.front(), second.front());
		int r = std::max(first.back(), second.back());
		int m;

		while (l < r) {
			m = (l + r) / 2;
			int before_m = lbin_search(first, m) + lbin_search(second, m);
			int after_m = (2 * L) - before_m;
			
			if (before_m <= L - 1 && after_m <= L) {
				return m;
			}

			if (before_m > L - 1) {
				r = m - 1;
			} 
			if (after_m > L) {
				l = m + 1;
			}
		}
		
		return l;
	}

	static void solution() {
		int N, L;
		std::cin >> N >> L;
		std::vector<std::vector<int>> seqs;
		seqs.reserve(N);

		for (int i = 0; i < N; ++i) {
			std::vector<int> seq;
			seq.reserve(L);

			int k = 0, t;
			while (k++ < L) {
				std::cin >> t;
				seq.push_back(t);
			}
			seqs.push_back(seq);
		}

		for (int i = 0; i < N - 1; ++i) {
			for (int j = i + 1; j < N; ++j) {
				std::cout << i << "," << j << ":\n" << find_median(seqs[i], seqs[j], L) << '\n';
			}
		}
	}
};


// non-working too
class J_lecture {
public:
	using check_fn = std::function<bool(const std::vector<int> &seq, const int &index, const int &pillar)>;

	static int lbin_search(const std::vector<int> &seq, const check_fn &check, const int &pillar) {
		int l = 0, r = std::ssize(seq) - 1, m;
		while (l < r) {
			m = (l + r) / 2;
			if (check(seq, m, pillar)) {
				r = m;
			} else {
				l = m + 1;
			}
		}
		return l;
	}

	static bool check_is_ge(const std::vector<int> &seq, const int &index, const int &pillar) {
		return seq[index] >= pillar;
	}

	static bool check_is_gt(const std::vector<int> &seq, const int &index, const int &pillar) {
		return seq[index] > pillar;
	}

	static int count_less(const std::vector<int> &seq, const int &pillar) {
		int result = lbin_search(seq, check_is_ge, pillar);
		if (seq[result] < pillar) {
			return std::ssize(seq);
		}
		return result;
	}

	static int count_greater(const std::vector<int> &seq, const int &pillar) {
		return std::ssize(seq) - count_less(seq, pillar);
	}

	static int find_median(const std::vector<int> &first, const std::vector<int> &second, const int &L) {
		int l = std::min(first.front(), second.front());
		int r = std::max(first.back(), second.back());
		int m;

		while (l < r) {
			m = (l + r) / 2;
			int less = count_less(first, m) + count_less(second, m);
			int greater = count_greater(first, m) + count_greater(second, m);
			if (less <= L - 1 && greater <= L) {
				return m;
			}
			if (greater > L) {
				l = m + 1;
			}
			if (less > L - 1) {
				r = m - 1;
			}
		}
		return l;
	}

	static void solution() {
		int N, L;
		std::cin >> N >> L;
		std::vector<std::vector<int>> seqs;
		seqs.reserve(N);

		for (int i = 0; i < N; ++i) {
			std::vector<int> seq;
			seq.reserve(L);

			int k = 0, t;
			while (k++ < L) {
				std::cin >> t;
				seq.push_back(t);
			}
			seqs.push_back(seq);
		}

		for (int i = 0; i < N - 1; ++i) {
			for (int j = i + 1; j < N; ++j) {
				std::cout << find_median(seqs[i], seqs[j], L) << '\n';
			}
		}
	}
};


int main() {
	J_lecture::solution();
}