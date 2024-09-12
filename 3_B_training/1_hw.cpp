#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <array>
#include <map>
#include <unordered_set>


// "11. Стек с защитой от ошибок"
class A {
private:
	static inline const std::array<std::string, 6> cmds { 
		"push", "pop", "back", 
		"size", "clear", "exit"
	};
	static inline const std::string ok_msg = "ok";
	static inline const std::string error_msg = "error";
	static inline const std::string bye_msg = "bye";

public:
	static void solution() {
		std::stack<int> stack;
		std::string line, cmd;
		std::istringstream stream(line);
		while (std::getline(std::cin, line)) {
			stream.clear();
			stream.str(line);
			stream >> cmd;
			if (cmd == cmds[0]) {
				int n;
				stream >> n;
				stack.push(n);
				std::cout << ok_msg << '\n';
			} else if (cmd == cmds[1] || cmd == cmds[2]) {
				if (stack.empty()) {
					std::cout << error_msg;
				} else {
					std::cout << stack.top();
					if (cmd == cmds[1]) {
						stack.pop();
					}
				}
				std::cout << '\n';
			} else if (cmd == cmds[3]) {
				std::cout << stack.size() << '\n';
			} else if (cmd == cmds[4]) {
				while (!stack.empty()) {
					stack.pop();
				}
				std::cout << ok_msg << '\n';
			} else {
				std::cout << bye_msg << '\n';
				return;
			}
		}
	}
};


// "12. Правильная скобочная последовательность"
class B {
private:
	static inline std::map<char, char> brackets {
		{')', '('},
		{']', '['},
		{'}', '{'}
	};

public:
	static void solution() {
		std::stack<char> opened_brackets;
		for (char br; std::cin >> br;) {
			if (br == '(' || br == '[' || br == '{') {
				opened_brackets.push(br);
			} else if (!opened_brackets.empty() && opened_brackets.top() == brackets[br]) {
				opened_brackets.pop();
			} else {
				std::cout << "no\n";
				return;
			}
		}

		std::cout << (opened_brackets.empty() ? "yes" : "no") << '\n';
	}
};


// 13. Постфиксная запись
class C {
private:
	static inline std::unordered_set<std::string> operations {
		"+", "-", "*"
	};

public:
	static void solution() {
		std::stack<int> operands;

		for (std::string op; std::cin >> op;) {
			if  (!operations.contains(op)) {
				operands.push(std::stoi(op));
			} else {
				int r_op = operands.top();
				operands.pop();
				int l_op = operands.top();
				operands.pop();

				int result;
				if (op == "+") {
					result = l_op + r_op;
				} else if (op == "-") {
					result = l_op - r_op;
				} else {
					result = l_op * r_op;
				}
				operands.push(result);
			}
		}
		std::cout << operands.top() << '\n';
	}
};


// "14. Сортировка вагонов lite"
class D {
public:
	static void solution() {
		int n;
		std::cin >> n;
		std::stack<int> deadend;
		std::vector<int> wagons;
		wagons.reserve(n);
		for (int i = 0, a; i < n; ++i) {
			std::cin >> a;
			while (!deadend.empty() && deadend.top() < a) {
				wagons.push_back(deadend.top());
				deadend.pop();
			}
			deadend.push(a);
		}
		while (!deadend.empty()) {
			wagons.push_back(deadend.top());
			deadend.pop();
		}

		for (int i = 1; i < std::ssize(wagons); ++i) {
			if (wagons[i] != wagons[i - 1] + 1) {
				std::cout << "NO\n";
				return;
			}
		}
		std::cout << "YES\n";
	}
};


// "15. Великое Лайнландское переселение"
class E {
public:
	static void solution() {
		int n;
		std::cin >> n;
		std::vector<int> towns_costs(n), towns_ans(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> towns_costs[i];
		}

		std::stack<int> costly_cities;
		for (int i = 0; i < n; ++i) {
			while (!costly_cities.empty() && towns_costs[costly_cities.top()] > towns_costs[i]) {
				towns_ans[costly_cities.top()] = i;
				costly_cities.pop();
			}
			costly_cities.push(i);
		}

		while (!costly_cities.empty()) {
			towns_ans[costly_cities.top()] = -1;
			costly_cities.pop();
		}

		for (const auto near_cheap_сity : towns_ans) {
			std::cout << near_cheap_сity << ' '; 
		}
		std::cout << '\n';
	}
};


int main () {
	E::solution();
}
