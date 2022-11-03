#include <iostream>
#include "MyArray.h"

int main() {
    std::cout << "Hello, World!" << std::endl;


    MyArray<int> b;
    b.insert(1);
    b.insert(2);
    b.insert(3);

    for (auto it = b.iterator(); it.hasNext(); it.next())
        std::cout << it.get() << std::endl;
    b.remove(0);

    for (auto it = b.iterator(); it.hasNext(); it.next())
        std::cout << it.get() << std::endl;


    return 0;

}
