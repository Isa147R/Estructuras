#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class CircularLinkedList {
public:
    CircularLinkedList() {
        head = nullptr;
    }

    ~CircularLinkedList() {
        clear();
    }

    void insert(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
        } else {
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
        }
    }

    void remove(int value) {
        if (head == nullptr) {
            return;
        }

        if (head->data == value) {
            Node* temp = head;
            if (head->next == head) {
                head = nullptr;
            } else {
                Node* current = head;
                while (current->next != head) {
                    current = current->next;
                }
                current->next = head->next;
                head = head->next;
            }
            delete temp;
        } else {
            Node* current = head;
            while (current->next != head && current->next->data != value) {
                current = current->next;
            }
            if (current->next != head) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
        }
    }

    bool search(int value) {
        if (head == nullptr) {
            return false;
        }

        Node* current = head;
        do {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        } while (current != head);

        return false;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            if (head->next == head) {
                head = nullptr;
            } else {
                Node* current = head;
                while (current->next != head) {
                    current = current->next;
                }
                current->next = head->next;
                head = head->next;
            }
            delete temp;
        }
    }

    void display() {
        if (head == nullptr) {
            return;
        }

        Node* current = head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);

        std::cout << std::endl;
    }

private:
    Node* head;
};

int main() {
    CircularLinkedList list;
    list.insert(5);
    list.insert(10);
    list.insert(15);
    list.insert(20);

    std::cout << "List: ";
    list.display();

    std::cout << "Search for 10: " << (list.search(10) ? "Found" : "Not found") << std::endl;

    list.remove(10);

    std::cout << "List after removing 10: ";
    list.display();

    return 0;
}
