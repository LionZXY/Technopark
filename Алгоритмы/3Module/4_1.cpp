#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cassert>

struct CNode {
    int value;
    int height;
    int count;
    CNode *left;
    CNode *right;

    CNode(int value) : value(value), height(1), left(NULL), right(NULL), count(1) {}

    ~CNode() {
        if (left != NULL) delete left;
        if (right != NULL) delete right;
    }
};

class AVLTree {
public:
    AVLTree();

    ~AVLTree();

    int add(int value);
    void removeByIndex(int index);
    bool has(int value);

private:
    CNode *root;

    int add(int value, CNode *&node);

    // Служебные методы для балансировки
    void balance();
    void updateHeight(CNode *node);
    void balance(CNode *&node);
    void rotateLeft(CNode *&node);
    void rotateRight(CNode *&node);

    CNode *remove(int value, CNode *&node);
    void remove(int value);
    CNode *minAndRemove(CNode *&p);
    // Height
    int h(CNode *node);
    //Count
    int c(CNode *node);
};

AVLTree::AVLTree(): root(NULL) {
    // Nothing
}
AVLTree::~AVLTree() {
    if (root != NULL)
        delete root;
}

// Методы-обертки
int AVLTree::h(CNode *node) { return node == NULL ? 0 : node->height; }
int AVLTree::c(CNode *node) { return node == NULL ? 0 : node->count; }
void AVLTree::remove(int value) { root = remove(value, root); }
void AVLTree::balance() { balance(root); }

int AVLTree::add(int value) {
    if (root == NULL) {
        root = new CNode(value);
        return 0;
    }

    int result = add(value, root);
    balance();
    return result;
}

int AVLTree::add(int value, CNode *&node) {
    int result = 0;
    if (node != NULL)
        if (value > node->value)
            result = add(value, node->right);
        else
            result = add(value, node->left) + 1 + c(node->right);
    else node = new CNode(value);
    balance(node);
    return result;
}


void AVLTree::updateHeight(CNode *node) {
    if (node != NULL) {
        node->height = std::max(h(node->left), h(node->right)) + 1;
        node->count = c(node->left) + c(node->right) + 1;
    }
}


void AVLTree::balance(CNode *&node) {
    if (node == NULL)
        return;
    updateHeight(node);
    if (h(node->left) - h(node->right) == 2) {
        if (h(node->left->left) - h(node->left->right) == -1) {
            rotateLeft(node->left);
        }
        rotateRight(node);
    } else if (h(node->left) - h(node->right) == -2) {
        if (h(node->right->left) - h(node->right->right) == 1) {
            rotateRight(node->right);
        }
        rotateLeft(node);
    }
    updateHeight(node);
}

void AVLTree::rotateLeft(CNode *&node) {
    CNode *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    node = tmp;
    updateHeight(node->left);
    updateHeight(node);
}

void AVLTree::rotateRight(CNode *&node) {
    CNode *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    node = tmp;
    updateHeight(node->right);
    updateHeight(node);
}


bool AVLTree::has(int value) {
    CNode *node = root;
    while (node != NULL) {
        if (value > node->value)
            node = node->right;
        else if (value < node->value)
            node = node->left;
        else return true;
    }
    return false;
}


CNode *AVLTree::minAndRemove(CNode *&node) // поиск узла с минимальным ключом в дереве p
{
    CNode *tmp;
    if (node->left == NULL) {
        tmp = node;
        node = node->right;
        updateHeight(node);
    } else { tmp = minAndRemove(node->left); }
    balance(node);
    return tmp;
}

CNode *AVLTree::remove(int value, CNode *&node) {
    if (node == NULL)
        return NULL;
    if (value < node->value)
        node->left = remove(value, node->left);
    else if (value > node->value)
        node->right = remove(value, node->right);
    else //  k == p->key
    {
        CNode *left = node->left;
        CNode *right = node->right;
        node->left = NULL;
        node->right = NULL;
        delete node;
        node = NULL;
        if (left == NULL && right == NULL) {
            return NULL;
        }
        if (right == NULL) {
            node = left;
            balance(node);
            return node;
        }

        if (left == NULL) {
            node = right;
            balance(node);
            return node;
        }

        CNode *minVar = minAndRemove(right);
        minVar->left = left;
        minVar->right = right;
        balance(minVar);
        node = minVar;
    }
    balance(node);
    return node;
}


void AVLTree::removeByIndex(int index) {
    assert(root != NULL);
    assert(index < c(root));

    CNode *node = root;
    int curPos = c(root->right);

    while (curPos != index) {
        if (index > curPos) {
            node = node->left;
            curPos += 1 + c(node->right);
        } else {
            node = node->right;
            curPos -= 1 + c(node->left);
        }
    }

    remove(node->value);
}

int main() {
    AVLTree tree;
    int N = 0;
    std::cin >> N;

    int command = 0;
    int value = 0;
    for (int i = 0; i < N; i++) {
        std::cin >> command;
        std::cin >> value;
        int rst;
        switch (command) {
            case 1:
                std::cout << tree.add(value) << '\n';
                break;
            case 2:
                tree.removeByIndex(value);
                break;
            default:
                assert(false);
        }
    }

    return 0;
}