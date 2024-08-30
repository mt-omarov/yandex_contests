#include <iostream>
#include <sstream>


class A {
private:
	static inline std::ostringstream stream;

	static void hanoi_towers(int n, int from, int to, int &count) {
		++count;
		if (n == 1) {
			stream << from << ' ' << to << '\n';
			return;
		}
		int next_to = 6 - from - to;
		hanoi_towers(n - 1, from, next_to, count);
		stream << from << ' ' << to << '\n';
		hanoi_towers(n - 1, next_to, to, count);
	}

public:
	static void solution() {
		int n, count = 0;
		std::cin >> n;
		hanoi_towers(n, 1, 3, count);
		std::cout << count << '\n' << stream.str();
	}
};


// https://new.contest.yandex.ru/48568/problem?id=215/2023_04_06/NQ3L2sn9W8
class B {
private:
	static void hanoi_towers(int n, int from, int to) {
		// soon...
	}

public:
	static void solution() {
		int n;
		std::cin >> n;
	}
};


int main() {
	A::solution();
}