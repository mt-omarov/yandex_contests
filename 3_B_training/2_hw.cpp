#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <list>
#include <deque>
#include <array>
#include <vector>


// "16. Очередь с защитой от ошибок"
class A {
public:
	static void solution() {
		std::queue<int> queue;
		
		std::string line;
		std::istringstream stream(line);
		for (std::string cmd; std::getline(std::cin, line);) {
			stream.clear();
			stream.str(line);
			stream >> cmd;
			if (cmd == "push") {
				int num;
				stream >> num;
				queue.push(num);
				std::cout << "ok\n";
			} else if (cmd == "front" || cmd == "pop") {
				if (queue.empty()) {
					std::cout << "error\n";
				} else {
					std::cout << queue.front() << '\n';
					if (cmd == "pop") {
						queue.pop();
					}
				}
			} else if (cmd == "clear") {
				while (!queue.empty()) {
					queue.pop();
				}
				std::cout << "ok\n";
			} else if (cmd == "size") {
				std::cout << queue.size() << '\n';
			} else {
				std::cout << "bye\n";
				return;
			}
		}
	}

	static void implement_solution() {
		std::list<int> queue;
		std::string line;
		std::istringstream stream(line);
		for (std::string cmd; std::getline(std::cin, line);) {
			stream.clear();
			stream.str(line);
			stream >> cmd;
			if (cmd == "push") {
				int num;
				stream >> num;
				queue.push_back(num);
				std::cout << "ok\n";
			} else if (cmd == "front" || cmd == "pop") {
				if (queue.empty()) {
					std::cout << "error\n";
				} else {
					std::cout << queue.front() << '\n';
					if (cmd == "pop") {
						queue.pop_front();
					}
				}
			} else if (cmd == "clear") {
				while (!queue.empty()) {
					queue.pop_front();
				}
				std::cout << "ok\n";
			} else if (cmd == "size") {
				std::cout << queue.size() << '\n';
			} else {
				std::cout << "bye\n";
				return;
			}
		}
	}
};


// "17. Игра в пьяницу"
class B {
private:
	static void input_queue(std::queue<int> &queue) {
		std::string line;
		std::getline(std::cin, line);
		std::istringstream stream(line);
		int card;	
		while (stream >> card) {
			queue.push(card);
		}
	}

public:
	static void solution() {
		std::queue<int> first, second;
		input_queue(first);
		input_queue(second);
		
		int count = 0;
		while (!first.empty() && !second.empty() && count < 1'000'000) {
			bool revert = (std::abs(first.front() - second.front()) == 9);
			bool first_less = (first.front() < second.front());

			if ((revert && first_less) || (!revert && !first_less)) {
				first.push(first.front());
				first.push(second.front());
			} else {
				second.push(first.front());
				second.push(second.front());
			}

			first.pop();
			second.pop();
			++count;
		}

		if (count == 1'000'000) {
			std::cout << "botva\n";
		} else if (second.empty()) {
			std::cout << "first " << count << '\n';
		} else {
			std::cout << "second " << count << '\n';
		}
	}
};


// "18. Дек с защитой от ошибок"
class C {
private:
	static constexpr int k = 101;

	template<int n>
	class deque {
	private:
		std::array<int, n> buf;
		int head = 0;
		int tail = 1;

	public:
		void push_front(const int num) {
			buf[head] = num;
			if (head == 0) {
			head = n - 1;
			} else {
				--head;
			}
			std::cout << "ok\n";
		}

		void push_back(const int num) {
			buf[tail] = num;
			tail = (tail + 1) % n;
			std::cout << "ok\n";
		}

		void pop_front() {
			if ((head + 1) % n == tail) {
				std::cout << "error\n";
			} else {
				head = (head + 1) % n;
				std::cout << buf[head] << '\n';
			}
		}

		void pop_back() {
			if (head == ((tail == 0) ? n - 1 : tail - 1)) {
				std::cout << "error\n";
				return;
			}
			if (tail == 0) {
				tail = n - 1;
			} else {
				--tail;
			}
			std::cout << buf[tail] << '\n';
		}

		void front() const {
			if ((head + 1) % n == tail) {
				std::cout << "error\n";
			} else {
				std::cout << buf[(head + 1) % n] << '\n';
			}
		}

		void back() const {
			if ((head + 1) % n == tail) {
				std::cout << "error\n";
			} else {
				std::cout << buf[(tail == 0) ? n - 1 : tail - 1] << '\n';
			}
		}

		void clear() {
			while ((head + 1) % n != tail) {
				head = (head + 1) % n;
			}
			std::cout << "ok\n";
		}

		int size() const {
			if (head < tail) {
				return tail - head - 1;
			} else {
				return k - head - 1 + tail;
			}
		}

	};


public:
	static void solution() {
		deque<k> deque;

		std::string line;
		std::istringstream stream(line);
		for (std::string cmd; std::getline(std::cin, line);) {
			stream.clear();
			stream.str(line);
			stream >> cmd;
			if (cmd == "push_front" || cmd == "push_back") {
				int num;
				stream >> num;
				if (cmd == "push_front") {
					deque.push_front(num);
				} else {
					deque.push_back(num);
				}
			} else if (cmd == "pop_front") {
				deque.pop_front();
			} else if (cmd == "pop_back") {
				deque.pop_back();
			} else if (cmd == "clear") {
				deque.clear();
			} else if (cmd == "front") {
				deque.front();
			} else if (cmd == "back") {
				deque.back();
			} else if (cmd == "size") {
				std::cout << deque.size() << '\n';
			} else {
				std::cout << "bye\n";
				return;
			}
		}
	}
};


// "19. Хипуй"
class D {
private:
	class Heap {
	private:
		std::vector<int> buf;

	public:
		void insert(const int num) {
			buf.push_back(num);
			int i = std::ssize(buf) - 1;
			while (i > 0 && buf[i] > buf[(i - 1) / 2]) {
				int tmp = buf[(i - 1) / 2];
				buf[(i - 1) / 2] = buf[i];
				buf[i] = tmp;
				i = (i - 1) / 2;
			}
		}

		void extract() {
			std::cout << buf[0] << '\n';
			buf[0] = buf[std::ssize(buf) - 1];

			int i = 0;
			bool balanced = false;
			while (i * 2 + 1 < std::ssize(buf) && !balanced) {
				int max_i = i * 2 + 1;
				if (max_i + 1 < std::ssize(buf) && buf[max_i + 1] > buf[max_i]) {
					++max_i;
				}
				if (buf[max_i] > buf[i]) {
					int tmp = buf[i];
					buf[i] = buf[max_i];
					buf[max_i] = tmp;
					i = max_i;
				} else {
					balanced = true;
				}
			}
			buf.pop_back();
		}
	};

public:
	static void solution() {
		{ // skip n
			int n;
			std::cin >> n;
		}
		Heap heap;
		std::string line;
		std::istringstream stream(line);
		for (int cmd; std::getline(std::cin, line);) {
			stream.clear();
			stream.str(line);
			stream >> cmd;
			if (!cmd) {
				int num;
				stream >> num;
				heap.insert(num);
			} else {
				heap.extract();
			}
		}
	}
};


// "20. Пирамидальная сортировка"
class E {
private:
	class Heap {
	private:
		std::vector<int> buf;

	public:
		void insert(const int num) {
			buf.push_back(num);
			int i = std::ssize(buf) - 1;
			while (i > 0 && buf[i] < buf[(i - 1) / 2]) {
				int tmp = buf[(i - 1) / 2];
				buf[(i - 1) / 2] = buf[i];
				buf[i] = tmp;
				i = (i - 1) / 2;
			}
		}

		int extract() {
			int top = buf[0];
			buf[0] = buf[std::ssize(buf) - 1];

			int i = 0;
			bool balanced = false;
			while (i * 2 + 1 < std::ssize(buf) && !balanced) {
				int min_i = i * 2 + 1;
				if (min_i + 1 < std::ssize(buf) && buf[min_i + 1] < buf[min_i]) {
					++min_i;
				}
				if (buf[min_i] < buf[i]) {
					int tmp = buf[i];
					buf[i] = buf[min_i];
					buf[min_i] = tmp;
					i = min_i;
				} else {
					balanced = true;
				}
			}
			buf.pop_back();
			return top;
		}

		bool empty() const {
			return (std::ssize(buf) == 0);
		}
	};
public:
	static void solution() {
		Heap heap;
		int n; 
		std::cin >> n;
		// complexity: log(1) + log(2) + ... + log(n) = (log(1) + log(n)) * n / 2 => O(log(n) * n)
		for (int num, i = 0; ++i <= n;) {
			std::cin >> num;
			heap.insert(num);
		}

		// the same => overall: O(n * log(n))
		while (!heap.empty()) {
			std::cout << heap.extract() << ' ';
		}
		std::cout << '\n';
	}
};


int main() {
	E::solution();
}