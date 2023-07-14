#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(double width, double height);
    ~Rectangle();
    double calculateArea() const override;
    void draw() const override;
    void setColor(Color *ptr_color) override;

    double getWidth();
    double getHeight();
    std::string getColor();

private:
    double width_;
    double height_;
    Color *ptr_color_;
};

#endif 