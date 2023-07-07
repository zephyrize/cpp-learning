#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(double width, double height) : width_(width), height_(height) {}

double Rectangle::calculateArea() const {
    return width_ * height_;
}

void Rectangle::draw() const {
    std::cout << "Drawing a rectangle." << std::endl;
}

double Rectangle::getWidth() {
    return width_;
}

double Rectangle::getHeight() {
    return height_;
}

void Rectangle::setColor(Color *ptr_color) {
    this->ptr_color_ = ptr_color;
}

std::string Rectangle::getColor() {
    return ptr_color_->getName();
}

Rectangle::~Rectangle() {
    if (this->ptr_color_ == nullptr) { return ; }
    delete this->ptr_color_;
    this->ptr_color_ == nullptr;
}
