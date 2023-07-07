#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include "color.h"
#include "shape_container.h"
#include "file_manager.h"

#include <iostream>
#include <memory>

// 踩坑：第一次编译没有通过，原因是编译器没法识别make_unique是std的成员 
//（我一直以为这些是c++11的新特性。原来unique_ptr是c++11推出的，但是c++14才引入了make_unique）
// make_unique是即将推出的C ++ 14功能，因此即使它符合C++ 11，也可能在编译器上不可用。
// 错误原因：CMakeLists.txt一开始制定了c++11的编译器，导致无法编译。改成c++14即可

// 手动复制一个 make_unique
// template<typename T, typename... Args>
// std::unique_ptr< T > make_unique(Args&&... args) {
//     return std::unique_ptr< T >(new T(std::forward<Args>(args)...));
// }


int main() {
    // 创建两个形状-矩形和圆形
    std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(4.0, 5.0);
    std::unique_ptr<Shape> circle = std::make_unique<Circle>(3.0);

    // 为每个形状设置颜色
    rectangle->setColor(new Color("red"));
    circle->setColor(new Color("blue"));

    // 绘图 （打印一条命令）
    rectangle->draw();
    circle->draw();

    // 计算形状的面积
    std::cout << "Rectangle area: " << rectangle->calculateArea() << std::endl;
    std::cout << "Circle area: " << circle->calculateArea() << std::endl;

    // 创建一个形状的容器
    ShapeContainer shape_container;

    // 将形状添加到容器中
    shape_container.addShape(std::move(rectangle));
    shape_container.addShape(std::move(circle));

    // 将容器中的形状信息都保存到文件中
    FileManager::saveShapesToFile("../files_save/shapes.txt", shape_container);

    // 清除容器信息
    shape_container.clear();

    // 从文件中获取形状信息并再次保存到容器中
    FileManager::loadShapesFromFile("../files_save/shapes.txt", shape_container);


    // 打印容器内的信息
    // std::cout << "从文件加载信息后的容器大小为" << shape_container.getShapes().size() << std::endl;


    // 打印形状信息，通过面积范围查询
    auto shapes = shape_container.findShapesByArea(0.0, 100.0);
    std::cout << "Shapes with areas between 0 and 100:" << std::endl;
    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "Area: " << shape->calculateArea() << std::endl;
    }

    return 0;
}
