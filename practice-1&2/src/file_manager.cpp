#include "file_manager.h"
#include "rectangle.h"
#include "circle.h"

#include <fstream>
#include <iostream>
#include <memory>
/*
文件操作实践
*/

// 存储形状信息到文件中
// 格式：Rectangle [width] [height] 或者 Circle [radius]
void FileManager::saveShapesToFile(const std::string& filename, const ShapeContainer& container) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (auto &shape : container.getShapes()) {
            if (Rectangle *rectangle = dynamic_cast<Rectangle*>(shape.get())) {
                file << "Rectangle " << rectangle->getColor() << " " \
                << rectangle->getWidth() << " " << rectangle->getHeight() << std::endl;
            }
            else if (Circle *circle = dynamic_cast<Circle*>(shape.get())) {
                file << "Circle " << circle->getColor() << " " \
                << circle->getRadius() << std::endl;                
            }
        }
    }
    file.close();
    std::cout << "形状信息成功保存到文件: " << filename << std::endl;
}


// template<typename T, typename... Args>
// std::unique_ptr< T > make_unique(Args&&... args) {
//     return std::unique_ptr< T >(new T(std::forward<Args>(args)...));
// }


// 从文件中读取形状信息并加载到形状容器里
void FileManager::loadShapesFromFile(const std::string& filename, ShapeContainer& container) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string shape_type, color_name;
        double param1, param2;

        while (file >> shape_type >> color_name >> param1 >> param2) {
            if (shape_type == "Rectangle") {
                std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(param1, param2);
                rectangle->setColor(new Color(color_name));
                container.addShape(std::move(rectangle));
            } else if (shape_type == "Circle") {
                std::unique_ptr<Shape> circle = std::make_unique<Circle>(param1);
                circle->setColor(new Color(color_name));
                container.addShape(std::move(circle));
            }
            std::cout << "load " << shape_type << " successfully!" << std::endl;
        }

        file.close();
    }
}