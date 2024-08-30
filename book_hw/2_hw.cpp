#include <iostream>
#include <map>

/*
"Бронирование переговорки"
url: https://new.contest.yandex.ru/48557/problem?id=215/2023_04_06/RdGbbmsLQn
*/

int main() {
	int n;
	std::cin >> n;
	std::map<int, int> segments;
	for (int i = 0, l, r; i < n; ++i) {
		std::cin >> l >> r;
		if (!segments.contains(r) || segments[r] < l) {
			segments[r] = l;
		}
	}
	
	int result = 1, last_r = segments.begin()->first;
	for (auto it = std::next(segments.cbegin()); it != segments.cend(); ++it) {
		const int &l = it->second;
		const int &r = it->first;
		if (l > last_r) {
			last_r = r;
			++result;
		}
	}
	std::cout << result << '\n';
}