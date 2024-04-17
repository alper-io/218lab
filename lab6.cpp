#include <iostream>
#include <stdexcept>

class Node {
public:
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

using namespace std;

class UnorderedSet {
private:
    Node* head;

public:
    UnorderedSet() : head(nullptr) {}

    // Destructor
    ~UnorderedSet() {
        clear();
    }

    // Insert an element into the set
    void insert(int value) {
        Node *current = head;
        while (current != nullptr) {
            if (current->data == value)
                return;
            current = current->next;
        }
        Node* newnode = new Node(value);
        newnode->next = head;
        head = newnode;
    }

    // Remove an element from the set
    void remove(int value) {
        Node* prev = nullptr;
        Node* current = head;
        while (current != nullptr && current->data != value) {
            prev = current;
            current = current->next;
        }
        if (current == nullptr) {
            throw out_of_range("Value not found in set");
        }
        if (prev != nullptr) {
            prev->next = current->next;
        } else {
            head = current->next;
        }
        delete current;
    }

    // Check if an element exists in the set
    bool contains(int value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    // Get the size of the set
    int size() const {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            current = current->next;
            count++;
        }
        return count;
    }

    // Check if the set is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Clear the set
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Display the set elements
    void printSet() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
    }

    // Compute the intersection of two sets
    UnorderedSet intersection(const UnorderedSet& other) const {
        UnorderedSet result;
        Node* current = head;
        while (current != nullptr) {
            if (other.contains(current->data)) {
                result.insert(current->data);
            }
            current = current->next;
        }
        return result;
    }

    // Compute the union of two sets
    UnorderedSet setUnion(const UnorderedSet& other) const {
        UnorderedSet result = *this; // Copy constructor
        Node* current = other.head;
        while (current != nullptr) {
            if (!result.contains(current->data)) {
                result.insert(current->data);
            }
            current = current->next;
        }
        return result;
    }

    // Compute the set difference of two sets
    UnorderedSet setDifference(const UnorderedSet& other) const {
        UnorderedSet result = *this; // Copy constructor
        Node* current = other.head;
        while (current != nullptr) {
            if (result.contains(current->data)) {
                result.remove(current->data);
            }
            current = current->next;
        }
        return result;
    }
};

int main(){
	
	return 0;
}