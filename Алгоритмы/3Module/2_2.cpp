//
// Created by lionzxy on 19.05.17.
//

#include <cstdio>
#include <stack>
#include <iostream>
#include <functional>

struct CNode {
    int value;
    CNode *left;
    CNode *right;

    CNode(int value) : value(value), left(NULL), right(NULL) {}
};

class CSimpleTree {
public:
    CSimpleTree(int first);

    ~CSimpleTree();

    void add(int value);

    void iterrator(void (*next)(int value));

private:

    CNode *root;

    void iterrator(std::function<void(CNode *)> next);
};

CSimpleTree::CSimpleTree(int first) {
    root = new CNode(first);
}

CSimpleTree::~CSimpleTree() {
    iterrator([](CNode *node) {
        delete node;
    });
}

void CSimpleTree::add(int value) {
    CNode *node = root;
    CNode *nodePrev = root;
    while (node != NULL) {
        nodePrev = node;
        node = value > node->value ? node->right : node->left;
    }
    if (value > nodePrev->value)
        nodePrev->right = new CNode(value);
    else nodePrev->left = new CNode(value);
}

void CSimpleTree::iterrator(void (*next)(int)) {
    iterrator([next](CNode *node) -> void {
        next(node->value);
        return;
    });
}

void CSimpleTree::iterrator(std::function<void(CNode *)> next) {
    CNode *parent = root;
    std::stack<CNode *> stack;
    while (!stack.empty() || parent != NULL) {
        if (parent != NULL) {
            next(parent);
            if (parent->right != NULL) {
                stack.push(parent->right);
            }
            parent = parent->left;
        } else {
            parent = stack.top();
            stack.pop();
        }
    }
}


int main() {
    int n = 0;
    std::cin >> n;

    int tmp = 0;
    std::cin >> tmp;
    CSimpleTree tree(tmp);
    for (int i = 1; i < n; i++) {
        std::cin >> tmp;
        tree.add(tmp);
    }

    tree.iterrator([](int value) {
        std::cout << value << ' ';
    });
    return 0;
}

