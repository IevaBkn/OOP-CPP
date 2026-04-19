#include "IP2.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;
using namespace DataStructure;

void Log(ofstream& logFile, const string& msg) {
    cout << msg << endl;
    if (logFile.is_open()) {
        logFile << msg << endl;
    }
}

int main() {

    ofstream logFile("log.txt");
    if (!logFile) {
        cerr << "Cannot open log.txt\n";
        return 1;
    }

    // 1 test (Constructor)
    doublyLinkedList empty;
    assert(empty.size() == 0);
    Log(logFile, "size == 0");
    assert(empty.toString() == "");
    Log(logFile, "empty.toString() == \"\"");
    Log(logFile, "Test 1: PASSED\n");

    // 2 test (Operator +=)
    doublyLinkedList list;
    list += {0, 5};
    list += {1, 10};
    list += {2, 15};
    assert(list.size() == 3);
    Log(logFile, "size == 3 after 3 inserts");
    assert(list.toString() == "5 10 15 ");
    Log(logFile, "toString() == \"5 10 15 \"");
    Log(logFile, "Test 2: PASSED\n");

    // 3 test (Duplication exception)
    try {
        list += {1, 10};
        assert(false);
    } catch (const DuplicateException&) {
        Log(logFile, "Duplication exception caught");
    }
    assert(list.size() == 3);
    Log(logFile, "Size unchanged after failed insert");
    Log(logFile, "Test 3: PASSED\n");

    // 4 test (Search with [])
    assert(list[10] == 1);
    Log(logFile, "list[10] == 1");
    assert(list[5] == 0);
    Log(logFile, "list[5] == 0");
    assert(list[15] == 2);
    Log(logFile, "list[15] == 2");
    assert(list[99] == -1);
    Log(logFile, "list[99] == -1 (not found)");
    Log(logFile, "Test 4: PASSED\n");

    // 5 test (Operator -=)
    list -= 1;
    assert(list.size() == 2);
    Log(logFile, "size == 2 after removal");
    assert(list.toString() == "5 15 ");
    Log(logFile, "toString() == \"5 15 \"");
    assert(list[10] == -1);
    Log(logFile, "removed value not found ");
    try {
        list -= 999;
        assert(false);
    } catch (const out_of_range&) {
        Log(logFile, "out of range");
    }
    Log(logFile, "Test 5: PASSED\n");

    // 6 test (Change head with operator*=)
    list *= 100;
    assert(list.toString() == "100 15 ");
    Log(logFile, "head changed to 100");
    doublyLinkedList empty2;
    try {
        empty2 *= 5;
        assert(false);
    } catch (const runtime_error&) {
        Log(logFile, "runtime_error caught on empty list");
    }
    Log(logFile, "Test 6: PASSED\n");

    // 7 test (Copy constructor)
    doublyLinkedList copy(list);
    assert(copy.toString() == list.toString());
    Log(logFile, "copy has same content");
    copy += {2, 200};
    assert(list.size() == 2 && copy.size() == 3);
    Log(logFile, "copy is independent (deep copy)");
    Log(logFile, "Test 7: PASSED\n");

    // 8 test (Assignment operator =)
    Log(logFile, "Test 8: operator=");
    doublyLinkedList assigned;
    assigned = list;
    assert(assigned.toString() == list.toString());
    Log(logFile, "assignment copies content");
    assigned += {2, 300};
    assert(list.size() == 2 && assigned.size() == 3);
    Log(logFile, "assigned is independent");
    Log(logFile, "Test 8: PASSED\n");

    // 9 test (Operators +=, ==, !=)
    doublyLinkedList same;
    same += {0, 100};
    same += {1, 15};
    assert(list == same);
    Log(logFile, "list == same");
    assert(!(list != same));
    Log(logFile, "!(list != same)");
    assert(!(list == copy));
    Log(logFile, "list != copy (different content)");
    Log(logFile, "Test 9: PASSED\n");

    // 10 test (Comparison operators <, <=, >, >=)
    doublyLinkedList smaller, larger;
    smaller += {0, 1};
    larger += {0, 1};
    larger += {1, 2};
    larger += {2, 3};
    assert(smaller < larger);
    Log(logFile, "smaller < larger");
    assert(smaller <= larger);
    Log(logFile, "smaller <= larger");
    assert(larger > smaller);
    Log(logFile, "larger > smaller");
    assert(larger >= smaller);
    Log(logFile, "larger >= smaller");
    Log(logFile, "Test 10: PASSED\n");

    // 11 test (Clearing !)
    !list;
    assert(list.size() == 0);
    Log(logFile, "size == 0 after clear");
    assert(list.toString() == "");
    Log(logFile, "toString() == \"\" after clear");
    Log(logFile, "Test 11: PASSED\n");

    // 12 test (Single element list)
    doublyLinkedList single;
    single += {0, 42};
    assert(single.size() == 1);
    Log(logFile, "size == 1 after insert");
    assert(single[42] == 0);
    Log(logFile, "find(42) == 0");
    single -= 0;
    assert(single.size() == 0);
    Log(logFile, "size == 0 after remove");
    Log(logFile, "Test 12: PASSED\n");

    Log(logFile, "All tests passed");
    
    if (logFile) {
        logFile.close();
    }

    return 0;
}
