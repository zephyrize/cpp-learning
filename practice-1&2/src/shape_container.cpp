#include "shape_container.h"

#include <algorithm>
#include <memory>

void ShapeContainer::addShape(std::unique_ptr<Shape> shape) {
    shapes_.emplace_back(std::move(shape));
}

void ShapeContainer::removeShape(const Shape * shape) {

    // 采用标准库中的remove_if函数和lambda表达式对Shape vector内的元素进行删除。
    auto it = std::remove_if(shapes_.begin(), shapes_.end(), 
        [shape](const std::unique_ptr<Shape>& s) { return s.get() == shape; });
    shapes_.erase(it, shapes_.end());
}


std::vector<const Shape*> ShapeContainer::findShapesByArea(double min_area, double max_area) const {
    std::vector<const Shape*> result;
    for (const auto& shape : shapes_) {
        double area = shape->calculateArea();
        if (area >= min_area && area <= max_area) {
            result.emplace_back(shape.get());
        }
    }
    return result;
}

const std::vector<std::unique_ptr<Shape>>& ShapeContainer::getShapes() const {
    return shapes_;
}

void ShapeContainer::clear() {
    shapes_.clear();
}