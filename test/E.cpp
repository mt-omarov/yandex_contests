#include <iostream>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <map>


// "Занимательная алхимия"
// url: https://contest.yandex.ru/contest/50668/problems/E
// failed in the 38th test (WA)


using ull = unsigned long long int;

struct Node {
	int id;
	std::map<int, ull> neighbors;

	Node(int id): id(id) {}
};

static std::unordered_map<int, Node*> nodes;
static std::unordered_map<int, std::optional<std::pair<ull, ull>>> recipes;
static std::unordered_set<int> visited;

void untangle_tree(int main_id) {
	visited.insert(main_id);

	ull a = 0, b = 0;
	for (const auto &[id, count] : nodes[main_id]->neighbors) {
		if (id == 1) {
			a += count;
		} else if (id == 2) {
			b += count;
		} else if (visited.contains(id)) {
			recipes[main_id] = std::nullopt;
			return;
		} else if (recipes.contains(id) && recipes[id]) {
			a += (recipes[id]->first) * count;
			b += (recipes[id]->second) * count;
		} else {
			untangle_tree(id);
			if (visited.contains(id)) {
				recipes[main_id] = std::nullopt;
				return;
			} else {
				a += (recipes[id]->first) * count;
				b += (recipes[id]->second) * count;
			}
		}
	}

	recipes[main_id] = std::make_optional<std::pair<ull, ull>>(a, b);
	visited.erase(main_id);
}

void solution() {
	int n;
	std::cin >> n;
	nodes[1] = new Node(1);
	nodes[2] = new Node(2);
	for (int i = 3; i <= n; ++i) {
		int k;
		std::cin >> k;
		nodes[i] = new Node(i);
		for (int j = 0, id; j < k; ++j) {
			std::cin >> id;
			nodes[i]->neighbors[id] += 1;
		}
	}

	for (const auto &[main_id, root] : nodes) {
		if (!recipes.contains(main_id)) {
			untangle_tree(main_id);
		}
	}

	int q, result;
	ull x, y, s;
	std::cin >> q;
	for (int i = 0; i < q; ++i) {
		result = 0;
		std::cin >> x >> y >> s;
		if (recipes.contains(s) && recipes[s] && 
			x >= recipes[s]->first && y >= recipes[s]->second) {
			result = 1;
		}
		std::cout << result;
	}
	std::cout << '\n';
}


int main() {
	solution();
}