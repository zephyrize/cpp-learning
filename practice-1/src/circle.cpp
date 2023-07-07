#include "circle.h"
#include <iostream>

Circle::Circle(double radius) : radius_(radius) {}

double Circle::calculateArea() const {
    return 3.14159 * radius_ * radius_;
}

void Circle::draw() const {
    std::cout << "Drawing a circle." << std::endl;
}

double Circle::getRadius() {
    return radius_;
}

void Circle::setColor(Color *ptr_color) {
    this->ptr_color_ = ptr_color;
}

std::string Circle::getColor() {
    return ptr_color_->getName();
}

Circle::~Circle() {
    if (this->ptr_color_ == nullptr) { return ; }
    delete this->ptr_color_;
    this->ptr_color_ == nullptr;
}

