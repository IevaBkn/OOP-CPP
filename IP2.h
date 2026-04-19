#ifndef IP2_H
#define IP2_H

#include <string>
#include <stdexcept>

namespace DataStructure {

    class DuplicateException : public std::runtime_error {
        public:
            explicit DuplicateException(const std::string& msg);
    };

    class doublyLinkedList {
    private:
        class Impl;
        Impl* impl;

    public:
        doublyLinkedList();
        
        doublyLinkedList(const doublyLinkedList& other);
        
        ~doublyLinkedList();
        
        doublyLinkedList& operator=(const doublyLinkedList& other);

        doublyLinkedList& operator+=(const std::pair<int, int>& p);

        doublyLinkedList& operator-=(int position);
        
        doublyLinkedList& operator*=(int value);

        bool operator==(const doublyLinkedList& other) const;
        
        bool operator!=(const doublyLinkedList& other) const;
        
        bool operator<(const doublyLinkedList& other) const;
        
        bool operator<=(const doublyLinkedList& other) const;
        
        bool operator>(const doublyLinkedList& other) const;
        
        bool operator>=(const doublyLinkedList& other) const;

        void operator!();
        
        int operator[](int value) const;

        int size() const;
        
        std::string toString() const;
    };
}

#endif
