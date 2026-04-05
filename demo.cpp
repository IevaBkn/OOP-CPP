#include "IP2.h"
#include <iostream>

using namespace std;
using namespace dataStructure;

int main() {

    doublyLinkedList list1;
    cout << "Size of empty list: " << list1.size() << "\n";
    cout << "Empty list toString: \"" << list1.toString() << "\"\n\n";

    // Push back
    cout << "Operator += :\n";
    list1 += 10;
    list1 += 20;
    list1 += 30;
    cout << "After += 10, 20, 30: " << list1.toString() << "\n\n";

    // Search
    cout << "Operator []:\n";
    cout << "Position of 20: " << list1[20] << "\n";
    cout << "Position of 99: " << list1[99] << " (-1 = not found)\n\n";

    // Head value 
    cout << "Operator *= (set head value):\n";
    list1 *= 100;
    cout << "After *= 100: " << list1.toString() << "\n\n";

    // Copying constructor
    cout << "Copy constructor:\n";
    doublyLinkedList list2(list1);
    cout << "list2: " << list2.toString() << "\n\n";

    // Assignment =
    cout << "Operator = :\n";
    doublyLinkedList list3;
    list3 = list2;
    cout << "list3: " << list3.toString() << "\n\n";

    // == and !=
    cout << "Comparison == and != :\n";
    cout << "list1 == list2: " << ((list1 == list2) ? "true" : "false") << "\n";
    cout << "list1 != list3: " << (list1 != list3) << "\n\n";

    // Comparing
    cout << "Size comparisons:\n";
    list3 += 40;
    cout << "list1.size()=" << list1.size() << ", list3.size()=" << list3.size() << "\n";
    cout << "list1 < list3: " << (list1 < list3) << "\n";
    cout << "list1 <= list3: " << (list1 <= list3) << "\n";
    cout << "list1 > list3: " << (list1 > list3) << "\n";
    cout << "list1 >= list3: " << (list1 >= list3) << "\n\n";

    // Remove
    cout << "Operator -= :\n";
    list1 -= 100;  // Remove the modified head
    cout << "After -= 100: " << list1.toString() << "\n\n";

    // Clear
    cout << "Operator ! :\n";
    !list1;
    cout << "After !list1, size: " << list1.size() << "\n";
    cout << "toString after clear: \"" << list1.toString() << "\"\n\n";

    // Duplicating
    cout << "Exception on duplication:\n";
    try {
        list2 += 20;
    } catch (const runtime_error& e) {
        cout << "Caught: " << e.what() << "\n\n";
    }

    // Exceptions

    cout << "Exception on remove not-found:\n";
    try {
        list2 -= 999;
    } catch (const invalid_argument& e) {
        cout << "Caught: " << e.what() << "\n\n";
    }

    cout << "Exception on *= empty list:\n";
    try {
        !list2;
        list2 *= 5;
    } catch (const runtime_error& e) {
        cout << "Caught: " << e.what() << "\n\n";
    }

    return 0;
}