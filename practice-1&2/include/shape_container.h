#ifndef SHAPE_CONSTAINER_H
#define SHAPE_CONSTAINER_H

#include "shape.h"
#include <vector>
#include <memory>

class ShapeContainer {

public: 
    void addShape(std::unique_ptr<Shape> shape);
    void removeShape(const Shape* shape);
    std::vector<const Shape*> findShapesByArea(double min_area, double max_area) const;
    const std::vector<std::unique_ptr<Shape>>& getShapes() const;
    void clear();

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};

#endif