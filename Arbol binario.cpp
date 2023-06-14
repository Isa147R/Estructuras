#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
public:
    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        destroyTree(root);
    }

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    void remove(int value) {
        root = removeRecursive(root, value);
    }

    bool search(int value) {
        return searchRecursive(root, value);
    }

private:
    Node* root;

    Node* insertRecursive(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    Node* removeRecursive(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = removeRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = removeRecursive(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* minNode = findMinNode(node->right);
            node->data = minNode->data;
            node->right = removeRecursive(node->right, minNode->data);
        }

        return node;
    }

    bool searchRecursive(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return searchRecursive(node->left, value);
        } else {
            return searchRecursive(node->right, value);
        }
    }

    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};

int main() {
    BinarySearchTree tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);

    std::cout << "Tree contains 6? " << (tree.search(6) ? "Yes" : "No") << std::endl;

    tree.remove(6);
    std::cout << "Tree contains 6? " << (tree.search(6) ? "Yes" : "No") << std::endl;

    return 0;
}
