#ifndef SHAPE_H
#define SHAPE_H

#include "color.h"


class Shape {
public:
    virtual double calculateArea() const = 0;
    virtual void draw() const = 0;

    virtual void setColor(Color *ptr_color) = 0; 
};

#endif
