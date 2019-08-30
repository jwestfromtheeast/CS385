#include <iostream>

using namespace std;

void display_array(int array[], const int length) {
    cout << "[";
    if (length > 0) {
        cout << array[0];
    }
    for (int i = 1; i < length; ++i) {
        cout << ", " << array[i];
    }
    cout << "]" << endl;
}

// Do the same as above by moving the pointers
void display_array_ptr(int array[], const int length) {
    cout << "[";
    int *ptr = array;
    int *end = ptr + length;
    while (ptr < end) {
        if (ptr != array) {
            cout << ", ";
        }
        cout << *ptr;
        ++ptr;
    }
    cout << "]" << endl;
}

void pass_by_value(int x) {
    x = 10;
}

void pass_by_pointer(int *x) {
    *x = 10;
}

void pass_by_reference(int &x) {
    x = 10;
}

int main() {
    // * : declares a pointer or dereferences a pointer
    // & : addressof operator
    int x = 5, y = 6, *z = &x; // z points to the place in memory where x resides
    cout << *z << endl; // derefernces z, so it prints the value, rather than the memory addr
    cout << "x = " << x << ", y = " << y << endl;
    z = &y;
    *z = 7; // Now above we pointed z to the address of y, so the value of y changes here
    cout << "x = " << x << ", y = " << y << endl;
    // cout << ++z << endl; // Bad idea: not sure where z points to. this increments the memory address
    // z += 30000; // Terrible idea: z now points outside the address space of this process
    // *z = 30; // Assigning a new value to the new place where z resides will cause a segmentation fault

    // Use valgrind to check for memory leaks or you lose points
    // valgrind --leak-check=yes myProgram
    int *values = new int[y];
    for (int i = 0; i < y; i++) {
        values[i] = i;
    }

    display_array(values, y);
    display_array_ptr(values, y);

    delete [] values;

    x = 5;
    pass_by_value(x);
    cout << "x = " << x << endl;

    // This one is not preferred
    x = 5;
    pass_by_pointer(&x);
    cout << "x = " << x << endl;

    x = 5;
    pass_by_reference(x);
    cout << "x = " << x << endl;

    return 0;
}