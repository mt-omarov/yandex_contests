#include <iostream>
#include <map>
#include <set>


// "Через тернии к клиенту"
// url: https://contest.yandex.ru/contest/50668/problems/B/


using ll = long long int;

void solution() {
	int n;
	ll id, day, hour, minute;
	char status;

	std::cin >> n;
	std::map<ll, std::set<std::pair<ll, char>>> rockets;

	for (int i = 0; i < n; ++i) {
		std::cin >> day >> hour >> minute >> id >> status;
		minute += day * 24 * 60 + hour * 60;
		if (!rockets.contains(id)) {
			rockets[id] = std::set<std::pair<ll, char>>();
		}
		rockets[id].insert({ minute, status });
	}

	for (const auto &[id, orders] : rockets) {
		ll all_time = 0, i = 0, prev_time = 0;
		char prev_status;
		for (const auto &[time, status] : orders) {
			if (i > 0 && prev_status != 'S' && prev_status != 'C') {
				all_time += (time - prev_time);
			}
			prev_time = time;
			prev_status = status;
			++i;
		}
		std::cout << all_time << ' ';
	}

	std::cout << '\n';
}


int main() {
	solution();
}