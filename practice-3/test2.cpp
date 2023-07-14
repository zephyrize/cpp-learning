/*
一些关于shared_ptr和weak_ptr学习的测试代码
*/

#include <iostream>
#include <memory>

std::weak_ptr<int> fwPtr;

int main() {
    std::shared_ptr<int> ptr(new int(42));
    std::weak_ptr<int> wptr = ptr;
    // 判断shared_ptr对象是否已被销毁
    if (wptr.expired()) {
        std::cout << "shared_ptr对象已被销毁" << std::endl;
    } else {
        std::cout << "shared_ptr对象未被销毁" << std::endl;
    }

    // 释放ptr2对资源的所有权
    ptr.reset();

    // 再次判断shared_ptr对象是否已被销毁
    if (wptr.expired()) {
        std::cout << "shared_ptr对象已被销毁" << std::endl;
    } else {
        std::cout << "shared_ptr对象未被销毁" << std::endl;
    }


    {
        std::shared_ptr<int> fsPtr(new int(5));
        fwPtr = fsPtr;
    }

    // std::cout << "fsPtr use_count:" << fsPtr.use_count() << " fwPtr use_count:" << fwPtr.use_count() << std::endl;
    std::cout << "fwPtr use_count:" << fwPtr.use_count() << std::endl;

    std::shared_ptr<int> fsPtr2 = fwPtr.lock();
    std::cout << "fsPtr use_count:" << fsPtr2.use_count() << " fwPtr use_count:" << fwPtr.use_count() << std::endl;
    
    return 0;
}

/*
shared_ptr对象未被销毁
shared_ptr对象已被销毁
fwPtr use_count:0
fsPtr use_count:0 fwPtr use_count:0
*/