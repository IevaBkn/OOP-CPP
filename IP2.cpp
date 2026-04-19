/*
- AI tools were used for learning/guidance (Pimpl idiom, deep copies)
- Some code/algorithms were taken from my own previous coursework
*/

#include "IP2.h"
#include <sstream>
#include <utility>
#include <stdexcept>

using namespace std;

namespace DataStructure {

// No duplications allowed in doubly linked list
DuplicateException::DuplicateException(const std::string& msg)
    : std::runtime_error(msg)
{
}

// Private Pimpl Idiom
class doublyLinkedList::Impl {
    public:
        struct Node {
            int data;
            Node* prev = nullptr; // Default initializer
            Node* next = nullptr; // Default initializer
            explicit Node(int d) : data(d) // Constructor
            {
            }
        };

        Node* head;
        Node* tail;
        int count;

        Impl()
            : head(nullptr), tail(nullptr), count(0) // Constructor
        {
        }

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

    doublyLinkedList& doublyLinkedList::operator+=(const std::pair<int, int>& p) {
        int pos = p.first;
        int value = p.second;
        
        if (pos < 0 || pos > impl->count) {
            throw std::out_of_range("Position out of range");
        }
        if (impl->find(value) != -1) {
            throw DuplicateException("Duplication: " + std::to_string(value));
        }
        if (pos == impl->count) {
            impl->push_back(value);
            return *this;
        }

        Impl::Node* n = new Impl::Node(value);
        
        if (pos == 0) {
            n->next = impl->head;
            if (impl->head) {
                impl->head->prev = n;
            } else {
                impl->tail = n;
            }
            impl->head = n;
        } else {
            Impl::Node* curr = impl->head;
            for (int i = 0; i < pos; ++i) {
                curr = curr->next;
            }
            n->prev = curr->prev;
            n->next = curr;
            if (curr->prev) {
                curr->prev->next = n;
            }
            curr->prev = n;
        }
        impl->count++;
        return *this;
    }

    doublyLinkedList& doublyLinkedList::operator-=(int position) {
        if (position < 0 || position >= impl->count) {
            throw std::out_of_range("Position out of range");
        }
        
        Impl::Node* curr = impl->head;
        for (int i = 0; i < position; ++i) {
            curr = curr->next;
        }
        if (curr->prev) {
            curr->prev->next = curr->next;
        } else {
            impl->head = curr->next;
        }
        if (curr->next) {
            curr->next->prev = curr->prev;
        } else {
            impl->tail = curr->prev;
        }
        
        delete curr;
        impl->count--;
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
        return !(*this < other) && !(*this > other);
    }

    bool doublyLinkedList::operator!=(const doublyLinkedList& other) const {
        return !(*this == other);
    }

    bool doublyLinkedList::operator<(const doublyLinkedList& other) const {
        Impl::Node* a = impl->head;
        Impl::Node* b = other.impl->head;
        
        while (a != nullptr && b != nullptr) {
            if (a->data < b->data) {
                return true;
            }
            if (a->data > b->data) {
                return false;
            }
            a = a->next;
            b = b->next;
        }
        return (a == nullptr && b != nullptr);
    }

    bool doublyLinkedList::operator>(const doublyLinkedList& other) const {
        return other < *this;
    }

    bool doublyLinkedList::operator<=(const doublyLinkedList& other) const {
        return !(other < *this);
    }

    bool doublyLinkedList::operator>=(const doublyLinkedList& other) const {
        return !(*this < other);
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
