#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>


namespace A_impl {

struct Node {
public:
	int data;
	Node* left;
	Node* right;
};

Node* create_node(const int &data) {
	Node* node = new Node();
	node->data = data;
	node->left = node->right = nullptr;

	return node;
}

Node* insert_node(Node* root, const int &data) {
	if (root == nullptr) {
		std::cout << "DONE\n";
		return create_node(data);
	}

	if (data < root->data) {
		root->left = insert_node(root->left, data);
	} else if (data > root->data) {
		root->right = insert_node(root->right, data);
	} else {
		std::cout << "ALREADY\n";
	}

	return root;

}

void find_node(Node* root, const int &data) {
	if (root == nullptr) {
		std::cout << "NO\n";
		return;
	}

	if (data < root->data) {
		return find_node(root->left, data);
	} else if (data > root->data) {
		return find_node(root->right, data);
	}
	
	std::cout << "YES\n";
	return;
}


void print_tree(Node* root, int count = 0) {
	if (root == nullptr) {
		return;
	}
	++count;
	int left_count = count, right_count = count;
	print_tree(root->left, left_count);
	for (int i = 0; i < count - 1; ++i) {
		std::cout << '.';
	}
	std::cout << root->data << '\n';
	print_tree(root->right, right_count);
}


} // namespace


class A {
private:
	using Node = A_impl::Node;

public:
	static void solution() {
		int data;
		Node* root = nullptr;

		std::string line, message, data_string;
		while (std::getline(std::cin, line)) {
			std::stringstream ss(line);
			std::getline(ss, message, ' ');
			if (message == "PRINTTREE") {
				print_tree(root);
			} else {
				std::getline(ss, data_string, ' ');
				data = std::stoi(data_string);
				if (message == "ADD") {
					root = insert_node(root, data);
				} else if (message == "SEARCH") {
					find_node(root, data);
				}
			}
		}

	}
};

namespace B_impl {

template <class T>
class Node {
public:
	T data;
	Node* parent{nullptr};
	std::unordered_set<Node*> childs;
	int level{0};
	int deep{0};

	Node(const T &data): data(data) {}

	static void append_child(Node* parent, Node* child) {
		child->parent = parent;
		parent->childs.insert(child);
	}

	static void count_levels(Node* node) {
		for (const auto &child: node->childs) {
			child->level = node->level + 1;
			count_levels(child);
		}
	}

	static Node* determine_common_parent(Node* node_1, Node* node_2) {
		int level_1 = node_1->level;
		int level_2 = node_2->level;
		if (level_1 > level_2) {
			while (node_1 && node_1->level != level_2) {
				node_1 = node_1->parent;
			}
		} else if (level_1 < level_2) {
			while (node_2 && level_1 != node_2->level) {
				node_2 = node_2->parent;
			}
		}
		
		while (node_1 != node_2 && node_1 && node_2) {
			node_1 = node_1->parent;
			node_2 = node_2->parent;
		}
		return node_1;
	}

	static int determine_child(Node* node_1, Node* node_2) {
		Node* parent = determine_common_parent(node_1, node_2);
		if (node_1 != parent && node_2 != parent) {
			return 0;
		} else if (node_1->level < node_2->level) {
			return 1;
		} else {
			return 2;
		}
	}

	static Node* input_tree(std::unordered_map<T, Node*> &nodes) {
		int n;
		std::cin >> n;
		T child, parent;
		for (int i = 0; i < n - 1; ++i) {
			std::cin >> child >> parent;
			if (!nodes.contains(parent)) {
				nodes.insert({ parent, new Node(parent)});
			}
			if (!nodes.contains(child)) {
				nodes.insert({ child, new Node(child)});
			}
			append_child(nodes[parent], nodes[child]);
		}

		Node* root = nodes.begin()->second;
		while (root->parent) {
			root = root->parent;
		}
		return root;
	}
};

} // namespace


class B {
private:
	using Node = B_impl::Node<std::string>;

public:
	static void solution() {
		std::unordered_map<std::string, Node*> names;
		Node* root = Node::input_tree(names);
		Node::count_levels(root);

		std::string name_1, name_2;
		while (std::cin >> name_1 >> name_2) {
			std::cout << Node::determine_child(names[name_1], names[name_2]) << ' ';
		}
	}
};


class C {
private:
	using Node = B_impl::Node<std::string>;

public:
	static void solution() {
		std::unordered_map<std::string, Node*> names;
		Node* root = Node::input_tree(names);
		Node::count_levels(root);

		std::string name_1, name_2;
		while (std::cin >> name_1 >> name_2) {
			std::cout << Node::determine_common_parent(names[name_1], names[name_2])->data << '\n';
		}
	}
};


class D {
private:
	class Node {
	public:
		int data;
		int deep{0};
		std::unordered_set<Node*> neighbors;

		Node(const int &data): data(data) {}

		static void append_nodes(Node* first, Node* second) {
			first->neighbors.insert(second);
			second->neighbors.insert(first);
		}

		static int count_deep(Node* root, std::unordered_set<int> &visited) {
			visited.insert(root->data);
			for (const auto &node : root->neighbors) {
				if (!visited.contains(node->data)) {
					root->deep = std::max(root->deep, count_deep(node, visited));
				}
			}
			return root->deep + 1;
		}

		static int count_seq(Node* root, std::unordered_set<int> &visited) {
			visited.insert(root->data);
			int first_max = 0, second_max = 0, length = 0;
			for (const auto &node : root->neighbors) {
				if (!visited.contains(node->data)) {
					int deep = node->deep + 1; // get the deep of node + node itself
					if (deep > first_max) {
						second_max = first_max;
						first_max = deep;
					} else if (deep > second_max) {
						second_max = deep;
					}
				}
			}
			length = first_max + second_max + 1; // +1 takes into account the root
			for (const auto &node : root->neighbors) {
				if (!visited.contains(node->data)) {
					length = std::max(length, count_seq(node, visited));
				}
			}
			return length;
		}
	};

public:
	static void solution() {
		int n;
		std::cin >> n;
		std::unordered_map<int, Node*> nodes;
		int node_1, node_2;
		while (std::cin >> node_1 >> node_2) {
			if (!nodes.contains(node_1)) {
				nodes.insert({ node_1, new Node(node_1) });
			}
			if (!nodes.contains(node_2)) {
				nodes.insert({ node_2, new Node(node_2) });
			}
			Node::append_nodes(nodes[node_1], nodes[node_2]);
		}

		Node* root = nodes.begin()->second;	
		{
			std::unordered_set<int> visited;
			Node::count_deep(root, visited);
		}
		std::unordered_set<int> visited;
		std::cout << Node::count_seq(root, visited) << '\n';
	}
};


int main() {
	D::solution();
}