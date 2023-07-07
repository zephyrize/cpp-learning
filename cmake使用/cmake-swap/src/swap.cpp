#include "swap.h"

void Swap::run() {
    _a = _a ^ _b;
    _b = _a ^ _b;
    _a = _a ^ _b;
}

void Swap::printInfo() {
    
    std::cout << "_a = " << _a << std::endl;
    std::cout << "_b = " << _b << std::endl;
}