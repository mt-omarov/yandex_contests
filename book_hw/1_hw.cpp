#include <iostream>


static int get_p_n(const int n) {
    int result = 1;
    for (int i = n; i > 0; --i) {
        result *= i;
    } 
    return result;
}


static int get_c_n_k(const int n, const int k) {
    int numerator = 1;
    for (int a = 1; a <= n; ++a) {
        numerator *= a;
    }
    int domenator = 1;
    for (int a = 1; a <= k; ++a) {
        domenator *= a;
    }
    for (int a = 1; a <= n - k; ++a) {
        domenator *= a;
    }
    return numerator / domenator;
}

void solution_A() {
    int n;
    std::cin >> n;
    std::cout << get_p_n(n) << '\n';
}

void solution_B() {
    int n, k;
    std::cin >> n >> k;
    std::cout << get_c_n_k(n, k) << '\n';
}

void solution_C() {
    int n, k;
    std::cin >> n >> k;
    std::cout << get_c_n_k(n + k - 1, k) << '\n';
}


int main() {
    solution_C();
}