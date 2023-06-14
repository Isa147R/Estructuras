#include <iostream>
#include <stack>
#include <string>
#include <cmath>

struct Node {
    std::string data;
    Node* left;
    Node* right;

    Node(const std::string& value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class ExpressionTree {
public:
    ExpressionTree() {
        root = nullptr;
    }

    ~ExpressionTree() {
        destroyTree(root);
    }

    void buildTree(const std::string& expression) {
        std::stack<Node*> nodeStack;

        for (int i = 0; i < expression.length(); i++) {
            if (isOperand(expression[i])) {
                std::string operand(1, expression[i]);
                Node* newNode = new Node(operand);
                nodeStack.push(newNode);
            } else if (isOperator(expression[i])) {
                Node* newNode = new Node(std::string(1, expression[i]));
                newNode->right = nodeStack.top();
                nodeStack.pop();
                newNode->left = nodeStack.top();
                nodeStack.pop();
                nodeStack.push(newNode);
            }
        }

        root = nodeStack.top();
        nodeStack.pop();
    }

    double evaluate() {
        return evaluateRecursive(root);
    }

private:
    Node* root;

    bool isOperand(char c) {
        return (c >= '0' && c <= '9');
    }

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    double evaluateRecursive(Node* node) {
        if (node == nullptr) {
            return 0.0;
        }

        if (isOperand(node->data[0])) {
            return std::stod(node->data);
        }

        double leftResult = evaluateRecursive(node->left);
        double rightResult = evaluateRecursive(node->right);

        if (node->data == "+") {
            return leftResult + rightResult;
        } else if (node->data == "-") {
            return leftResult - rightResult;
        } else if (node->data == "*") {
            return leftResult * rightResult;
        } else if (node->data == "/") {
            return leftResult / rightResult;
        } else {
            // Operador desconocido
            return 0.0;
        }
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
    std::string expression = "5+4*3-2/1";

    ExpressionTree tree;
    tree.buildTree(expression);

    double result = tree.evaluate();

    std::cout << "Expression: " << expression << std::endl;
    std::cout << "Result: " << result << std::endl;

    return 0;
}
