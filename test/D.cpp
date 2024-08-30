#include <iostream>
#include <map>


// "Лей, лей, не жалей"
// url: https://contest.yandex.ru/contest/50668/problems/D/


using ll = long long int;

ll find_lower_bound(const std::map<ll, ll> &map, const ll &target) {
	auto it = map.lower_bound(target);
	if (it == map.end()) {
		return -1;
	}
	if (it == map.begin()) {
		return 0;
	}
	return std::prev(it)->second;
}


ll find_upper_bound(const std::map<ll, ll> &map, const ll &target) {
	auto it = map.lower_bound(target);
	if (it == map.end()) {
		return map.rbegin()->second;
	} else if (it->first != target && it != map.begin()) {
		return std::prev(it)->second;
	} else if (it->first != target && it == map.begin()) {
		return -1;
	}
	return it->second;
}


void solution() {
	int n;
	std::cin >> n;

	std::map<ll, ll> pref_costs, pref_durations;
	ll start, end, cost;
	for (int i = 0; i < n; ++i) {
		std::cin >> start >> end >> cost;
		pref_costs[start] += cost;
		pref_durations[end] += end - start;
	}
	
	for (auto it = std::next(pref_durations.begin()); it != pref_durations.end(); ++it) {
		it->second += std::prev(it)->second;
	}
	for (auto it = std::next(pref_costs.begin()); it != pref_costs.end(); ++it) {
		it->second += std::prev(it)->second;
	}

	int q, type;
	std::cin >> q;
	for (int i = 0; i < q; ++i) {
		std::cin >> start >> end >> type;
		std::map<ll, ll> *pref;
		if (type == 1) {
			pref = &pref_costs;
		} else {
			pref = &pref_durations;
		}
		ll lower_bound = find_lower_bound(*pref, start);
		ll upper_bound = find_upper_bound(*pref, end);
		if (lower_bound == -1 || upper_bound == -1) {
			std::cout << "0 ";
		} else {
			std::cout << upper_bound - lower_bound << ' ';
		}
	}
	std::cout << '\n';
}


int main() {
	solution();
}