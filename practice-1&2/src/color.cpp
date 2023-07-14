#include "color.h"

Color::Color(const std::string& name) : name_(name) {}

std::string Color::getName() const {
    return name_;
}
