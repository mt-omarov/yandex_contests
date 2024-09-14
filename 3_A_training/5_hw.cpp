#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iomanip>


// "31. Площадь комнаты"
class A {
private:
	static inline std::vector<std::vector<bool>> graph;
	static inline std::vector<std::vector<bool>> visited;

	static void dfs(int row, int col, int &count) {
		if (!graph[row][col] || visited[row][col]) {
			return;
		}
		++count;
		visited[row][col] = true;
		if (row > 0) {
			dfs(row - 1, col, count);
		}
		if (row < std::ssize(graph) - 1) {
			dfs(row + 1, col, count);
		}

		if (col > 0) {
			dfs(row, col - 1, count);
		}
		if (col < std::ssize(graph) - 1) {
			dfs(row, col + 1, count);
		}
	}

	static void input_graph(int n) {
		graph = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
		visited = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));

		char symbol;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				std::cin >> symbol;
				if (symbol == '.') {
					graph[i][j] = true;
				}
			}
		}
	}

public:
	static void solution() {
		int n;
		std::cin >> n;
		input_graph(n);

		int row, col;
		std::cin >> row >> col;
		--row, --col;
		int count = 0;
		dfs(row, col, count);

		std::cout << count << '\n';
	}
};


// "32. Откуда достижима первая вершина"
class B {
private:
	static inline std::set<int> result;
	static inline std::vector<std::vector<int>> graph;

	static void input(int n, int m) {
		graph = std::vector<std::vector<int>>(n, std::vector<int>());
		for (int from, to, i = 0; i < m; ++i) {
			std::cin >> from >> to;
			if (from != to) {
				--from, --to;
				graph[from].push_back(to);
			}
		}
	}

	static bool dfs(int i, std::unordered_set<int> &visited, int parent_i = -1) {
		visited.insert(i);
		bool is_good = false;
		for (auto j : graph[i]) {
			if (j == 0) {
				result.insert(i);
				return true;
			}
			if (j == parent_i) {
				continue;
			}
			if (result.contains(j) || (!visited.contains(j) && dfs(j, visited, i))) {
				result.insert(i);
				is_good = true;
			}
		}
		return is_good;
	}

public:
	static void solution() {
		int n, m;
		std::cin >> n >> m;
		input(n, m);
			
		result.insert(0);
		for (int i = 1; i < n; ++i) {
			std::unordered_set<int> visited;
			dfs(i, visited);
		}

		for (auto i : result) {
			std::cout << i + 1 << ' ';
		}
		std::cout << '\n';
	}
};


// "33. Радио Байтик"
class C {
private:
	static constexpr double max_r = 2 * 100'000;
	static constexpr double eps = 0.000'000'000'1;

	struct Node {
		int i;
		int x;
		int y;
		int color{0}; // 0 - not visited, 1 - gray, 2 - black
		std::vector<int> neighbors;

		Node(int i, int x, int y) noexcept: i(i), x(x), y(y) {}
	};

	static bool comp(const Node &first, const Node &second) {
		return (first.i < second.i);
	}

	static inline int n;
	static inline std::vector<Node> tops;
	static inline std::vector<Node> graph;

	static void input() {
		std::cin >> n;
		for (int x, y, i = 0; i < n; ++i) {
			std::cin >> x >> y;
			tops.push_back(Node(i, x, y));
		}
	}

	static bool intersect(int a, int b, double power) { // check that the towers can interfere
		long int d_left = tops[a].x - tops[b].x;
		d_left *= d_left;
		long int d_right = tops[a].y - tops[b].y;
		d_right *= d_right;

		double d = d_left + d_right;
		double power_2 = power * power * 4.0;
		return (d <= power_2);
	}

	static bool dfs(int i, int parent_color, int parent_i = -1) { // check the graph for bipartite
		graph[i].color = 3 - parent_color;
		bool result = true;
		for (auto j : graph[i].neighbors) {
			if (i == parent_i) {
				continue;
			}
			if (!graph[j].color) {
				result &= dfs(j, graph[i].color, i);
			} else if (graph[i].color == graph[j].color) {
				return false;
			}
		}
		return result;
	}

	static bool check(double power) { // // check that the power gives high accuracy
		graph = tops; // copy nodes

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i != j && intersect(i, j, power)) { // the towers interfere – build an edge
					graph[i].neighbors.push_back(j);
				}
			}
		}

		bool result = true;
		for (int i = 0; i < n && result; ++i) {
			if (!graph[i].color) {
				result &= dfs(i, 2);
			}
		}

		return result;
	}

public:
	static void solution() {
		input();

		double l = 0, r = max_r, m;
		while (r > l + eps) { // binary search
			m = (r - l) / static_cast<double>(2) + l;
			if (check(m)) {
				l = m;
			} else {
				r = m;
			}
		}

		if (!check(r)) {
			std::cout << std::setprecision(15) << l << '\n';
			check(l); // copy nodes and color it 
		} else {
			std::cout << std::setprecision(15) << r << '\n';
		}
		std::ranges::sort(graph, comp); // sort by indexes from the input
		for (const auto &node : graph) {
			std::cout << node.color << ' ';
		}
		std::cout << '\n';
	}
};


int main() {
	C::solution();
}