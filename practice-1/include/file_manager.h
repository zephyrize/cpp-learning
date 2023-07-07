#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "shape_container.h"


class FileManager {
/*
由于这两个函数不需要访问类的非静态成员变量，所以在这里我将它们声明为静态成员函数
这样可以在不创建对象实例的情况下，被所有对象共享，直接调用静态成员函数，节省内存。。。
*/
public:
    // 保存形状信息到文件中
    static void saveShapesToFile(const std::string& filename, const ShapeContainer& container);
    // 加载形状信息
    static void loadShapesFromFile(const std::string& filename, ShapeContainer& container);
};

#endif