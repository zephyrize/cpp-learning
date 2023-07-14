#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include "color.h"

#include <string>

class Circle : public Shape {

public:
    Circle(double radius);
    ~Circle();
    double calculateArea() const override;
    void draw() const override;
    void setColor(Color *ptr_color) override;

    double getRadius();
    std::string getColor();

private:
    double radius_;
    Color *ptr_color_;
};

#endif