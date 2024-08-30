#include <iostream>
#include <vector>
#include <map>


namespace A_to_H {

struct Node {
public:
	int data;
	Node* left;
	Node* right;
};

Node* create_node(int data) {
	Node* node = new Node();
	node->data = data;
	node->left = node->right = nullptr;
	return node;
}

Node* insert_node(Node* root, int data) {
	if (root == nullptr) {
		return create_node(data);
	}

	if (data < root->data) {
		root->left = insert_node(root->left, data);
	} else if (data > root->data) {
		root->right = insert_node(root->right, data);
	}

	return root;
}

Node* insert_node_count(Node* root, int data, int &count) {
	++count;
	if (root == nullptr) {
		return create_node(data);
	}

	if (data < root->data) {
		root->left = insert_node_count(root->left, data, count);
	} else if (data > root->data) {
		root->right = insert_node_count(root->right, data, count);
	} else {
		count = -1;
	}

	return root;
}

int calculate_height(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	int leftHeight = calculate_height(root->left) + 1;
	int rightHeight = calculate_height(root->right) + 1;

	if (leftHeight > rightHeight) {
		return leftHeight;
	} else {
		return rightHeight;
	}
}

int find_second_max(Node* root) {
	int max2;
	Node* node = root;
	if (root->right != nullptr) {
		while (node->right->right != nullptr) {
			node = node->right;
		}
		if (node->right->left == nullptr) {
			max2 = node->data;
			return max2;
		}
		node = node->right->left;
	} else {
		node = root->left;
	}
	while (node->right != nullptr) {
		node = node->right;
	}
	max2 = node->data;
	
	return max2;
}

void inorder_traversal(Node* root) {
	if (root == nullptr) {
		return;
	}
	inorder_traversal(root->left);
	std::cout << root->data << '\n';
	inorder_traversal(root->right);
}

void inorder_leaves_traversal(Node* root) {
	if (root == nullptr) {
		return;
	}
	inorder_leaves_traversal(root->left);
	if (root->left == nullptr && root->right == nullptr) {
		std::cout << root->data << '\n';
	}
	inorder_leaves_traversal(root->right);
}

void inorder_nodes_traversal(Node* root) {
	if (root == nullptr) {
		return;
	}
	inorder_nodes_traversal(root->left);
	if (root->left != nullptr && root->right != nullptr) {
		std::cout << root->data << '\n';
	}
	inorder_nodes_traversal(root->right);
}

void inorder_branches_traversal(Node* root) {
	if (root == nullptr) {
		return;
	}
	inorder_branches_traversal(root->left);
	if ((root->left != nullptr && root->right == nullptr) || (root->left == nullptr && root->right != nullptr)) {
		std::cout << root->data << '\n';
	}
	inorder_branches_traversal(root->right);
}


void check_balance(Node* root, bool &balanced) {
	int leftHeight = calculate_height(root->left);
	int rightHeight = calculate_height(root->right);
	if (leftHeight - rightHeight > 1 || leftHeight - rightHeight < -1) {
		balanced = false;
		return;
	}
	if (root->left) {
		check_balance(root->left, balanced);
	}
	if (root->right) {
		check_balance(root->right, balanced);
	}
}

Node* input_tree() {
	int data;
	Node* root = nullptr;
	
	std::cin >> data;
	while (data != 0) {
		root = insert_node(root, data);
		std::cin >> data;
	}
	return root;
}


class A {
public:
	static void solution() {
		std::cout << calculate_height(input_tree()) << '\n';
	}
};


class B {
public:
	static void solution() {
		int data, count = 0;
		Node* root = nullptr;
		
		std::cin >> data;
		while (data != 0) {
			root = insert_node_count(root, data, count);
			if (count != -1) {
				std::cout << count << ' ';
			}
			std::cin >> data;
			count = 0;
		}
		std::cout << '\n';
	}
};


class C {
public:
	static void solution() {
		std::cout << find_second_max(input_tree()) << '\n';
	}
};


class D {
public:
	static void solution() {
		inorder_traversal(input_tree());
	}
};


class E {
public:
	static void solution() {
		inorder_leaves_traversal(input_tree());
	}
};


class F {
public:
	static void solution() {
		inorder_nodes_traversal(input_tree());
	}
};


class G {
public:
	static void solution() {
		inorder_branches_traversal(input_tree());
	}
};


class H {
public:
	static void solution() {
		bool balanced = true;
		check_balance(input_tree(), balanced);
		std::cout << (balanced ? "YES\n" : "NO\n"); 
	}
};

} // namespace A_to_H

namespace I_J {

struct Node {
public:
	std::string name;
	Node* parent{nullptr};
	std::vector<Node*> childs;
	int childs_count{0};
	int level{-1};

	Node(const std::string &name): name(name) {}
};

Node* create_node(const std::string &name) {
	Node* node = new Node(name);
	return node;
}

Node* add_child(Node* parent, Node* child) {
	parent->childs.push_back(child);
	child->parent = parent;
	return child;
}

int count_childs(Node* parent) {
	if (parent->childs_count > 0) {
		return parent->childs_count;
	}
	for (const auto &child : parent->childs) {
		parent->childs_count += count_childs(child) + 1;
	}
	return parent->childs_count;
}

int count_level(Node* child) {
	if (child == nullptr) {
		return -1;
	}

	if (child->level > -1) {
		return child->level;
	}
	
	child->level = count_level(child->parent) + 1;
	return child->level;
}


class I {
public:
	static void solution() {
		std::map<std::string, Node*> names;
		int n;
		std::cin >> n;
		std::string parent, child;
		for (int i = 0; i < n - 1; ++i) {
			std::cin >> child >> parent;
			if (names.find(parent) == names.end()) {
				names.insert({parent, create_node(parent)});
			}
			if (names.find(child) == names.end()) {
				names.insert({child, create_node(child)});
			}
			add_child(names[parent], names[child]);
		}

		for (auto it = names.cbegin(); it != names.cend(); ++it) {
			std::cout << it->first << ' ' << count_childs(it->second) << '\n';
		}
	}
};


class J {
public:
	static void solution() {
		std::map<std::string, Node*> names;
		int n;
		std::cin >> n;
		std::string parent, child;
		for (int i = 0; i < n - 1; ++i) {
			std::cin >> child >> parent;
			if (names.find(parent) == names.end()) {
				names.insert({parent, create_node(parent)});
			}
			if (names.find(child) == names.end()) {
				names.insert({child, create_node(child)});
			}
			add_child(names[parent], names[child]);
		}

		for (auto it = names.cbegin(); it != names.cend(); ++it) {
			std::cout << it->first << ' ' << count_level(it->second) << '\n';
		}
	}
};

} // namespace I_J


int main() {
	I_J::J::solution();
}