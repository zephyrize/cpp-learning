#pragma once
#include <iostream>

class Swap {
private:
    int _a;
    int _b;
public:

    Swap(int a, int b) {
        this->_a = a;
        this->_b = b;
    }
    
    void run();
    void printInfo();
};
