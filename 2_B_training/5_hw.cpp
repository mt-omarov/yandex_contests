#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>


class A {
private:
	using ull = unsigned long long int;

public:
	static void solution() {
		ull n, q;
		std::cin >> n >> q;
		std::vector<ull> pref_sums;
		pref_sums.reserve(n + 1);
		pref_sums.push_back(0);

		ull a;
		for (ull i = 0; ++i <= n;) {
			std::cin >> a;
			pref_sums.push_back(pref_sums[i - 1] + a);
		}

		ull l, r;
		for (ull i = 0; ++i <= q;) {
			std::cin >> l >> r;
			std::cout << pref_sums[r] - pref_sums[l - 1] << '\n';
		}
	}
};


class B {
private:
	using ll = long long int;

public:
	static void solution() {
		ll n, a;
		std::cin >> n >> a;
		ll s = a, result = a;
		for (ll i = 0; ++i <= n - 1;) {
			std::cin >> a;
			if (s < 0) {
				s = 0;
			}
			s += a;
			result = (result > s) ? result : s;
		}

		std::cout << result << '\n';
	}
};


class C {
public:
	static void solution() {
		uint n, m;
		std::cin >> n >> m;
		std::multimap<uint, uint> groups, rooms;
		std::vector<uint> results(n, 0);

		for (uint a, i = 0; i < n; ++i) {
			std::cin >> a;
			groups.insert({ a, i });
		}

		for (uint a, i = 0; ++i <= m;) { // (i = 1; i <= m; ++i)
			std::cin >> a;
			rooms.insert({ a, i });
		}

		uint k = 0;
		for (auto it_g = groups.cbegin(), it_r = rooms.cbegin(); it_g != groups.cend() && it_r != rooms.cend(); ++it_r) {
			if (it_g->first + 1 <= it_r->first) {
				results[it_g->second] = it_r->second;
				++it_g;
				++k;
			}
		}

		std::cout << k << '\n';
		for (const auto &it : results) {
			std::cout << it << '\n';
		}
	}
};


class D {
public:
	static void solution() {
		std::string str;
		std::cin >> str;

		int k = 0;
		for (const char &ch : str) {
			if (ch == ')' && --k < 0) {
				break;
			} else if (ch == '(') {
				++k;
			}
		}

		std::cout << ((k == 0) ? "YES" : "NO") << '\n';
	}
};


class E {
private:
	using ul = unsigned long int;

	static void input_array(std::unordered_map<ul, uint> &container) {
		uint n;
		std::cin >> n;
		for (uint a, i = 0; i < n; ++i) {
			std::cin >> a;
			if (!container.contains(a)) {
				container.insert({ a, i });
			}
		}
	}

	static void input_array(std::map<uint, ul> &container) {
		uint n;
		std::cin >> n;
		for (uint a, i = 0; i < n; ++i) {
			std::cin >> a;
			if (!container.contains(i)) {
				container.insert({ i, a });
			}
		}
	}

public:
	static void solution() {
		std::map<uint, ul> A, B;		// keys are indexes
		std::unordered_map<ul, uint> C;	// keys are values
		ul s;
		std::cin >> s;
		input_array(A);
		input_array(B);
		input_array(C);

		int i = -1, j = -1, k = -1;
		for (const auto &it_a : A) {
			for (const auto &it_b : B) {
				ul c_value = s - it_a.second - it_b.second;
				if (C.contains(c_value)) {
					if (i == -1 || k > C[c_value]) {
						i = it_a.first;
						j = it_b.first;
						k = C[c_value];
					}
					break;
				}
			}

			if (i != -1) {
				break;
			}
		}

		if (i == -1) {
			std::cout << i;
		} else {
			std::cout << i << ' ' << j << ' ' << k;
		}
		std::cout << '\n';
	}
};


int main() {
	E::solution();
}