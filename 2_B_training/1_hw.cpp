#include <iostream>

class A {
public:
	static void solution() {
		auto print_message = [](const int &result){
			std::cout << result << '\n';
		};

		int r, i, c;
		std::cin >> r >> i >> c;

		if (i == 0) {
			print_message((r != 0) ? 3 : c);
		} else if (i == 1) {
			print_message(c);
		} else if (i == 4) {
			print_message((r != 0) ? 3 : 4);
		} else if (i == 6) {
			print_message(0);
		} else if (i == 7) {
			print_message(1);
		} else {
			print_message(i);
		}
	}
};


class B {
public:
	static void solution() {
		uint n, i, j;
		std::cin >> n >> i >> j;
		uint l, r;
		if (i < j) {
			l = i + n - j - 1;
			r = j - i - 1;
		} else {
			l = i - j - 1;
			r = n - i + j - 1;
		}

		std::cout << ((l < r) ? l : r) << '\n';
	}
};


class C {
public:
	static void solution() {
		uint x, y, z;
		std::cin >> x >> y >> z;
		std::cout << (((x > 12 || y > 12) || (x == y)) ? 1 : 0) << '\n';
	}
};


class D {
public:
	static void solution() {
		long int n, a, i = 0;
		std::cin >> n;
		while (i != (n / 2 + static_cast<long int>(n % 2 != 0))) {
			std::cin >> a;
			++i;
		}
		std::cout << a << '\n';
	}
};


class E {
public:
	static void solution() {
		int d, x, y;
		std::cin >> d >> x >> y;
		if (x >= 0 && y >= 0 && y <=d && x <= d && y <= (d - x)) {
			std::cout << 0 << '\n';
			return;
		}
		
		int d_A = y * y + x * x;
		int d_B = y * y + (d - x) * (d - x);
		int d_C = x * x + (d - y) * (d - y);

		if (d_A <= d_B && d_A <= d_C) {
			std::cout << 1 << '\n';
		} else if (d_B <= d_A && d_B <= d_C) {
			std::cout << ((d_B == d_A) ? 1 : 2) << '\n';
		} else if (d_C <= d_A && d_C <= d_B) {
			std::cout << ((d_C == d_A) ? 1 : ((d_C == d_B) ? 2 : 3)) << '\n';
		}
	}
};


int main() {
	E::solution();
}