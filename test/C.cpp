#include <iostream>
#include <unordered_map>


// "Приснится же такое..."
// url: https://contest.yandex.ru/contest/50668/problems/C/


struct Node {
	int id;
	Node* parent{nullptr};
	Node* left{nullptr};
	Node* right{nullptr};

	Node(int id): id(id) {}
};

static std::unordered_map<int, Node*> nodes;

Node* addChilds(int id, const int &n, Node* parent = nullptr) {
	if (id > n) {
		return nullptr;
	}
	Node* node = new Node(id);
	nodes[id] = node;
	node->parent = parent;

	node->left = addChilds(id * 2, n, node);
	node->right = addChilds(id * 2 + 1, n, node);
	return node;
}

void printTree(Node* root) {
	if (root->left) {
		printTree(root->left);
	}
	std::cout << root->id << ' ';
	if (root->right) {
		printTree(root->right);
	}
}

void switchNodes(int id) {
	Node* v = nodes[id];
	Node* p = v->parent;
	if (p == nullptr) {
		return;
	}
	Node* pp = p->parent;
	if (pp) {
		if (p == pp->left) {
			pp->left = v;
		} else {
			pp->right = v;
		}
	}
	v->parent = pp;
	p->parent = v;
	if (v == p->left) {
		p->left = v->left;
		if (p->left) {
			p->left->parent = p;
		}
		v->left = p;
	} else {
		p->right = v->right;
		if (p->right) {
			p->right->parent = p;
		}
		v->right = p;
	}
}


void solution() {
	int n, q;
	std::cin >> n >> q;
	nodes.reserve(n);

	Node* root = addChilds(1, n);
	for (int i = 0, id; i < q; ++i) {
		std::cin >> id;
		if (nodes[id]->parent && nodes[id]->parent == root) {
			root = nodes[id];
		}
		switchNodes(id);
	}
	printTree(root);
	std::cout << '\n';
}


int main() {
	solution();
}