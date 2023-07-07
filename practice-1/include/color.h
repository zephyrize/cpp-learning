#ifndef COLOR_H
#define COLOR_H

#include <string>

class Color {
public:
    Color(const std::string& name);
    std::string getName() const;

private:
    // 为了方便，这里只设置一个颜色的名称变量
    std::string name_;
};

#endif  
