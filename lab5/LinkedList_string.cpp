#include "LinkedList_string.h"
#include <iostream>
#include <string>
#include <stdexcept>

LinkedList::LinkedList():head(nullptr)
{
}

LinkedList::LinkedList(const LinkedList& other) : head(nullptr) {
    if (other.head == nullptr)
        return;

    head = new Node(other.head->data);

    Node* currentNew = head;
    Node* currentOther = other.head->next;

    while (currentOther != nullptr) {
        currentNew->next = new Node(currentOther->data);

        // Move to the next nodes in both lists
        currentNew = currentNew->next;
        currentOther = currentOther->next;
    }
}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next; 
        delete current; 
        current = next; 
    }
    head = nullptr; 
}

string& LinkedList::at(int index) {
    if (index < 0) {
        throw out_of_range("Index out of range: Index is negative");
    }

    Node* current = head;
    int count = 0;
    while (current != nullptr && count < index) {
        current = current->next;
        count++;
    }

    if (current == nullptr) {
        throw out_of_range("Index out of range: Index is negative");
    }

    return current->data;
}

string& LinkedList::front() {
    if (head == nullptr) {
        throw out_of_range("Index out of range: Index is negative");
    }

    return head->data;
}

string& LinkedList::back() {
    if (head == nullptr) {
        throw out_of_range("Index out of range: Index is negative");
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    return current->data;
}

void LinkedList::push_back(const string& value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
    }
	else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }
}

void LinkedList::pop_back() {
    if (head == nullptr) {
        throw logic_error("List is empty");
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Node* prev = nullptr;
    Node* current = head;
    while (current->next != nullptr) {
        prev = current;
        current = current->next;
    }

    delete current;

    prev->next = nullptr;
}

void LinkedList::push_front(const string& value){
    Node* newNode = new Node(value);

    newNode->next = head;
    head = newNode;
}

void LinkedList::pop_front() {
    if (head == nullptr) {
        throw logic_error("List is empty");
    }

    Node* oldHead = head;

    head = head->next;

    delete oldHead;
}

void LinkedList::insert_at(int index, const string& value) {
    if (index < 0) {
        return;
    }

    if (index == 0) {
        push_front(value);
        return;
    }

    Node* current = head;
    int count = 0;
    while (current != nullptr && count < index - 1) {
        current = current->next;
        count++;
    }

    if (current == nullptr) {
        throw out_of_range("Index out of range");
    }

    // Create a new node with the given value
    Node* newNode = new Node(value);

    // Insert the new node after the current node
    newNode->next = current->next;
    current->next = newNode;
}

void LinkedList::insert_after(int index, const string& val) {
    if (index < 0) {
        throw out_of_range("Index out of range: Index is negative");
    }

    Node* current = head;
    int count = 0;
    while (current != nullptr && count < index) {
        current = current->next;
        count++;
    }

    if (current == nullptr) {
        throw out_of_range("Index out of range");
    }

    Node* newNode = new Node(val);

    // Insert the new node after the current node
    newNode->next = current->next;
    current->next = newNode;
}
void LinkedList::erase_at(int index) {
    if (index < 0) {
        throw out_of_range("Index out of range: Index is negative");
    }

    if (index == 0) {
        pop_front();
        return;
    }

    Node* prev = nullptr;
    Node* current = head;
    int count = 0;
    while (current != nullptr && count < index) {
        prev = current;
        current = current->next;
        count++;
    }

    if (current == nullptr) {
        throw out_of_range("Index out of range");
    }

    prev->next = current->next;

    Node* removedNode = current;
    delete removedNode;
}

void LinkedList::erase(const string& e) {
    if (head == nullptr) {
        return;
    }

    // If the element to be erased is at the head of the list
    while (head != nullptr && head->data == e) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    Node* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->next->data == e) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
}

void LinkedList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int LinkedList::size() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}
bool LinkedList::empty() const{
	return head==nullptr;
}

LinkedList& LinkedList::operator=(const LinkedList& lhs) {
    // Check for self-assignment
    if (this == &lhs) {
        return *this;
    }

    clear();
    
    Node* otherCurrent = lhs.head;
    while (otherCurrent != nullptr) {
        push_back(otherCurrent->data);
        otherCurrent = otherCurrent->next;
    }

    return *this;
}

bool LinkedList::operator==(const LinkedList& lhs) const {
    if (size() != lhs.size()) {
        return false;
    }

    Node* current = head;
    Node* otherCurrent = lhs.head;
    while (current != nullptr && otherCurrent != nullptr) {
        if (current->data != otherCurrent->data) {
            return false;
        }
        current = current->next;
        otherCurrent = otherCurrent->next;
    }

    return true;
}

ostream& operator<<(ostream& out, const LinkedList &list) {
    Node* current = list.head; 
    while (current != nullptr) {
        out << current->data << " ";
        current = current->next;
    }
    return out;
}

Node* LinkedList::findMiddleNode() {
    if (head == nullptr) {
        return nullptr;
    }

    int length = 0;
    Node* current = head;

    while (current != nullptr) {
        length++;
        current = current->next;
    }

    current = head;

    for (int i = 0; i < length / 2; ++i) {
        current = current->next;
    }

    // current pointer is at the middle node
    return current;
}

Node* LinkedList::getSmallestNode() {
    if (head == nullptr) {
        // nullptr if the list is empty
        return nullptr;
    }

    Node* smallestNode = head;
    Node* current = head->next;

    while (current != nullptr) {
        if (current->data < smallestNode->data) {
            smallestNode = current;
        }
        current = current->next;
    }

    return smallestNode;
}

void LinkedList::moveSmallestToFront() {
    if (head == nullptr || head->next == nullptr) {
        // If the list is empty or contains only one node, no need to move anything
        return;
    }

    Node* smallestNode = getSmallestNode();

    if (smallestNode == head) {
        return;
    }

    Node* prevOfSmallest = nullptr;
    Node* current = head;
    while (current != nullptr && current != smallestNode) {
        prevOfSmallest = current;
        current = current->next;
    }

    prevOfSmallest->next = smallestNode->next;

    smallestNode->next = head;
    head = smallestNode;
}



using namespace std;

int main() {
    LinkedList list;

    int choice;
    do {
        cout << "Welcome to the Linked List Program!" << endl;
        cout << "Menu:" << endl;
        cout << "1. Add an element" << endl;
        cout << "2. Remove an element by value" << endl;
        cout << "3. Access an element at index" << endl;
        cout << "4. Insert an element at index" << endl;
        cout << "5. Insert an element after index" << endl;
        cout << "6. Remove an element at index" << endl;
        cout << "7. Print the linked list" << endl;
        cout << "8. Print the size of the linked list" << endl;
        cout << "9. Check if the linked list is empty" << endl;
        cout << "10. Clear the linked list" << endl;
        cout << "11. Find the middle Node" << endl;
        cout << "12. Get the smallest Node" << endl;
        cout << "13. Move smallest Node to Front " << endl;
        cout << "14. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string value;
                cout << "Enter the value to add: ";
                cin >> value;
                list.push_back(value);
                cout << "Element added." << endl;
                break;
            }
            case 2: {
                string value;
                cout << "Enter the value to remove: ";
                cin >> value;
                list.erase(value);
                cout << "Element removed." << endl;
                break;
            }
            case 3: {
                int index;
                cout << "Enter the index: ";
                cin >> index;
                try {
                    cout << "Element at index " << index << " is: " << list.at(index) << endl;
                } catch (const out_of_range& e) {
                    cerr << "Error: " << e.what() << endl;
                }
                break;
            }
            case 4: {
                int index;
                string value;
                cout << "Enter the index: ";
                cin >> index;
                cout << "Enter the value to insert: ";
                cin >> value;
                try {
                    list.insert_at(index, value);
                    cout << "Element inserted." << endl;
                } catch (const out_of_range& e) {
                    cerr << "Error: " << e.what() << endl;
                }
                break;
            }
            case 5: {
                int index;
                string value;
                cout << "Enter the index: ";
                cin >> index;
                cout << "Enter the value to insert after index " << index << ": ";
                cin >> value;
                try {
                    list.insert_after(index, value);
                    cout << "Element inserted." << endl;
                } catch (const out_of_range& e) {
                    cerr << "Error: " << e.what() << endl;
                }
                break;
            }
            case 6: {
                int index;
                cout << "Enter the index to remove element: ";
                cin >> index;
                try {
                    list.erase_at(index);
                    cout << "Element removed." << endl;
                } catch (const out_of_range& e) {
                    cerr << "Error: " << e.what() << endl;
                }
                break;
            }
            case 7:
                if (!list.empty()) {
                    cout << "Linked List: " << list << endl;
                } else {
                    cout << "The linked list is empty." << endl;
                }
                break;
            case 8:
                cout << "Size of the Linked List: " << list.size() << endl;
                break;
            case 9:
                cout << (list.empty() ? "The linked list is empty." : "The linked list is not empty.") << endl;
                break;
            case 10:
                list.clear();
                cout << "Linked list cleared." << endl;
                break;
            case 11: {
			    Node* middleNode = list.findMiddleNode();
			    if (middleNode != nullptr) {
			        cout << "Middle Node: " << middleNode->data << endl;
			    } else {
			        cout << "The linked list is empty." << endl;
			    }
			    break;
			}
			case 12: {
			    Node* smallestNode = list.getSmallestNode();
			    if (smallestNode != nullptr) {
			        cout << "Smallest Node: " << smallestNode->data << endl;
			    } else {
			        cout << "The linked list is empty." << endl;
			    }
			    break;
			}
			case 13: {
			    list.moveSmallestToFront();
			    cout << "Smallest node moved to the front." << endl;
			    cout << "Linked List: " << list << endl;
			    break;
			}
            case 14:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 14);

    return 0;
}