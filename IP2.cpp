/*
 Attribution:
- AI tools were used for guidance (Pimpl idiom, deep copies)
- Some code/algorithms were taken from previous coursework of the past semester from my own work
- Linked list logic was also adapted from geeksforgeeks.org web page
*/

#include "IP2.h"
#include <sstream>
#include <stdexcept>

using namespace std;

namespace dataStructure {

// No duplications allowed in doubly linked list
DuplicateException::DuplicateException(const std::string& msg)
: std::runtime_error(msg) {}

// Private Pimpl Idiom
class doublyLinkedList::Impl {
    public:
        struct Node {
            int data;
            Node* prev = nullptr;  // Default initializer
            Node* next = nullptr;  // Default initializer
            Node(int d) : data(d) {} // Constructor
        };

        Node* head;
        Node* tail;
        int count;

        Impl() : head(nullptr), tail(nullptr), count(0) {} // Constructor

        // Destructor
        ~Impl() {
            clear();
        }

        // Deletes all the nodes from the list
        void clear() {
            Node* curr = head;
            while (curr != nullptr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
            head = nullptr;
            tail = nullptr;
            count = 0;
        }

        // Creates a new node
        void push_back(int value) {
            if (find(value) != -1) {
                throw DuplicateException("Duplication: " + std::to_string(value));
            }
            Node* n = new Node(value);
            if (head == nullptr) {
                head = tail = n;
            } else {
                tail->next = n;
                n->prev = tail;
                tail = n;
            }
            count++;
        }

        // Runs earch by value
        int find(int value) const {
            Node* curr = head;
            int pos = 0;
            while (curr) {
                if (curr->data == value) {
                    return pos;
                }
                curr = curr->next;
                pos++;
            }
            return -1;
        }

        // Removes a given value
        void remove(int value) {
            Node* curr = head;
            while (curr != nullptr) {
                if (curr->data == value) {
                    if (curr->prev) {
                        curr->prev->next = curr->next;
                    } else {
                        head = curr->next;
                    }
                    if (curr->next) {
                        curr->next->prev = curr->prev;
                    } else {
                        tail = curr->prev;
                    }
                    delete curr;
                    count--;
                    return;
                }
                curr = curr->next;
            }
            throw invalid_argument("Value not found");
        }
    };

    doublyLinkedList::doublyLinkedList() { //Constructor
        impl = new Impl();
    }

    // Deep copy
    doublyLinkedList::doublyLinkedList(const doublyLinkedList& other) {
        impl = new Impl();
        try {
            Impl::Node* curr = other.impl->head;
            while (curr) {
                impl->push_back(curr->data);
                curr = curr->next;
            }
        } catch (...) {
            delete impl;
            throw;
        }
    }

    doublyLinkedList::~doublyLinkedList() { // Destructor
        delete impl;
    }

    doublyLinkedList& doublyLinkedList::operator=(const doublyLinkedList& other) { // Deep copy
        if (this != &other) {
            impl->clear();
            Impl::Node* curr = other.impl->head;
            while (curr != nullptr) {
                impl->push_back(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    // CRUD
    doublyLinkedList& doublyLinkedList::operator+=(int value) { // Creates value
        impl->push_back(value);
        return *this;
    }

    doublyLinkedList& doublyLinkedList::operator-=(int value) { // Deletes
        impl->remove(value);
        return *this;
    }

    doublyLinkedList& doublyLinkedList::operator*=(int value) { // Updates
        if (!impl->head) {
            throw runtime_error("List is empty");
        }
        impl->head->data += value;
        return *this;
    }

    // Comparing

    bool doublyLinkedList::operator==(const doublyLinkedList& other) const {
        if (impl->count != other.impl->count) {
            return false;
        }
        Impl::Node* a = impl->head;
        Impl::Node* b = other.impl->head;

        while (a != nullptr) {
            if (a->data != b->data) {
                return false;
            }
            a = a->next;
            b = b->next;
        }
        return true;
    }

    bool doublyLinkedList::operator!=(const doublyLinkedList& other) const {
        return !(*this == other);
    }

    bool doublyLinkedList::operator<(const doublyLinkedList& other) const {
        return impl->count < other.impl->count;
    }

    bool doublyLinkedList::operator<=(const doublyLinkedList& other) const {
        return impl->count <= other.impl->count;
    }

    bool doublyLinkedList::operator>(const doublyLinkedList& other) const {
        return impl->count > other.impl->count;
    }

    bool doublyLinkedList::operator>=(const doublyLinkedList& other) const {
        return impl->count >= other.impl->count;
    }

    void doublyLinkedList::operator!() { // Clears all elements from list
        impl->clear();
    }

    int doublyLinkedList::operator[](int value) const { // Searches for values (impl, CRUD)
        return impl->find(value);
    }

    int doublyLinkedList::size() const { //Returns number of elements (getter)
        return impl->count;
    }

    string doublyLinkedList::toString() const { // toString
        stringstream ss;
        Impl::Node* curr = impl->head;
        while (curr != nullptr) {
            ss << curr->data << " ";
            curr = curr->next;
        }
        return ss.str();
    }

}