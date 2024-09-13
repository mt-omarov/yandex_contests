#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>


// "31. Поиск в глубину"
class A {
private:
	struct Node {
	public:
		static inline int first_component_count{0};

		int value;
		int component{0};
		bool visited{false};
		std::vector<int> neighbors;

		Node(int value) noexcept: value(value) {}
	};

	static bool comp (const Node &first, const Node &second) {
		return ((first.component < second.component) || 
				(first.component == second.component && first.value < second.value));
	}

	static inline std::vector<Node> tops;

	static void dfs(int i, int &component) {
		tops[i].visited = true;
		tops[i].component = component;
		for (auto j : tops[i].neighbors) {
			if (!tops[j].visited) {
				dfs(j, component);
			}
		}
		Node::first_component_count += (component == 1);
	}

	static void input_graph(int m) {
		for (int a, b, i = 0; i < m; ++i) {
			std::cin >> a >> b;
			--a; --b;
			tops[a].neighbors.push_back(b);
			tops[b].neighbors.push_back(a);
		}
	}

public:
	static void solution() {
		int n, m;
		std::cin >> n >> m;
		for (int i = 0; i < n; ++i) {
			tops.push_back(Node(i));
		}
		input_graph(m);

		for (int component = 1, i = 0; i < n; ++i) {
			if (!tops[i].visited) {
				dfs(i, component);
				++component;
			}
		}

		std::ranges::sort(tops, comp);
		std::cout << Node::first_component_count << '\n';
		for (const auto &top : tops) {
			if (top.component == 1) {
				std::cout << top.value + 1 << ' ';
			}
		}
		std::cout << '\n';
	}
};


// "32. Компоненты связности"
class B {
private:
	struct Node {
	public:
		static inline std::vector<std::vector<int>> components;

		bool visited{false};
		std::vector<int> neighbors;

		Node() = default;
	};

	static inline std::vector<Node> tops;

	static void dfs(int i, int &component) {
		tops[i].visited = true;
		Node::components[component].push_back(i);
		for (auto j : tops[i].neighbors) {
			if (!tops[j].visited) {
				dfs(j, component);
			}
		}
	}

	static void input_graph(int n, int m) {
		for (int i = 0; i < n; ++i) {
			tops.emplace_back(Node());
		}
		for (int a, b, i = 0; i < m; ++i) {
			std::cin >> a >> b;
			--a; --b;
			tops[a].neighbors.push_back(b);
			tops[b].neighbors.push_back(a);
		}
	}

public:
	static void solution() {
		int n, m;
		std::cin >> n >> m;
		input_graph(n, m);

		for (int component = 0, i = 0; i < n; ++i) {
			if (!tops[i].visited) {
				Node::components.emplace_back(std::vector<int>());
				dfs(i, component);
				++component;
			}
		}

		std::cout << Node::components.size() << '\n';
		for (const auto &component: Node::components) {
			std::cout << component.size() << '\n';
			for (const auto i : component) {
				std::cout << i + 1 << ' ';
			}
			std::cout << '\n';
		}
	}
};


// "33. Списывание"
class C {
private:
	struct Node {
	public:
		int color{0}; 
		std::vector<int> neighbors;

		Node() = default;
	};

	static inline std::vector<Node> graph;

	static void input_graph(int n, int m) {
		for (int i = 0; i < n; ++i) {
			graph.emplace_back(Node());
		}
		for (int a, b, i = 0; i < m; ++i) {
			std::cin >> a >> b;
			--a; --b;
			graph[a].neighbors.push_back(b);
			graph[b].neighbors.push_back(a);
		}
	}

	static bool dfs(int i, int parent_color) {
		bool result = true;
		graph[i].color = 3 - parent_color;
		for (auto j : graph[i].neighbors) {
			if (!graph[j].color) {
				result &= dfs(j, graph[i].color);
			} else if (graph[j].color == graph[i].color) {
				return false;
			}
		}
		return result;
	}

public:
	static void solution() {
		int n, m;
		std::cin >> n >> m;
		input_graph(n, m);

		int result = true;
		for (int color = 2, i = 0; i < n; ++i) {
			if (!graph[i].color) {
				result &= dfs(i, color);
			}
		}
		std::cout << (result ? "YES" : "NO") << '\n';
	}
};


// "34. Топологическая сортировка"
class D {
private:
	struct Node {
	public:
		int color{0}; 	// 0 - unset, 1 - gray (still in dfs), 2 - black (dead end)
		std::vector<int> childs;

		Node() = default;
	};

	static inline std::vector<Node> graph;
	static inline std::stack<int> sorted_graph;

	static void input_graph(int n, int m) {
		for (int i = 0; i < n; ++i) {
			graph.emplace_back(Node());
		}
		for (int a, b, i = 0; i < m; ++i) {
			std::cin >> a >> b;
			--a; --b;
			graph[a].childs.push_back(b);
		}
	}

	static bool dfs(int i) {
		bool result = true;
		graph[i].color = 1;
		for (auto j : graph[i].childs) {
			if (!graph[j].color) {
				result &= dfs(j);
			} else if (graph[j].color == 1) {
				return false;
			}
		}
		graph[i].color = 2;
		sorted_graph.push(i);
		return result;
	}

public:
	static void solution() {
		int n, m;
		std::cin >> n >> m;
		input_graph(n, m);

		bool result = true;
		for (int i = 0; i < n; ++i) {
			if (!graph[i].color) {
				result &= dfs(i);
			}
		}

		if (!result) {
			std::cout << "-1\n";
			return;
		}
		while (!sorted_graph.empty()) {
			std::cout << sorted_graph.top() + 1 << ' ';
			sorted_graph.pop();
		}
		std::cout << '\n';
	}
};


// "35. Поиск цикла"
class E {
private:
	struct Node {
	public:
		int color{0};
		std::vector<int> neighbors;

		Node() = default;
	};

	static inline std::vector<Node> graph;
	static inline std::vector<int> cycle;

	static void input_graph(int n) {
		for (int i = 0; i < n; ++i) {
			graph.emplace_back(Node());
		}

		for (int i = 0; i < n; ++i) {
			for (int is_connected, j = 0; j < n; ++j) {
				std::cin >> is_connected;
				if (is_connected && i != j) {
					graph[i].neighbors.push_back(j);
				}
			}
		}
	}

	static void restore_cycle(std::unordered_map<int, int> &history, int start, int end) {
		while (start != end) {
			cycle.push_back(start);
			start = history[start];
		}
		cycle.push_back(end);
	}

	static bool dfs(std::unordered_map<int, int> &history, int i, int parent_i = -1) {
		graph[i].color = 1;
		history[i] = parent_i;
		for (auto j : graph[i].neighbors) {
			if (j == parent_i) {
				continue;
			}
			if (!graph[j].color && !dfs(history, j, i)) {
				return false;
			} else if (graph[j].color == 1) {
				restore_cycle(history, i, j);
				return false;
			}
		}
		graph[i].color = 2;
		return true;
	}

public:
	static void solution() {
		int n;
		std::cin >> n;
		input_graph(n);

		bool acyclic = true;
		for (int i = 0; i < n && acyclic; ++i) {
			if (!graph[i].color) {
				std::unordered_map<int, int> history;
				acyclic &= dfs(history, i);
			}
		}

		if (acyclic) {
			std::cout << "NO\n";
		} else {
			std::cout << "YES\n" << cycle.size() << '\n';
			for (auto i : cycle) {
				std::cout << i + 1 << ' ';
			}
			std::cout << '\n';
		}
	}
};


int main() {
	E::solution();
}