/*
一些关于shared_ptr和weak_ptr学习的测试代码
*/

#include <iostream>
#include <memory>

using namespace std;

weak_ptr<int> fwPtr;

int main() {
    shared_ptr<int> ptr(new int(42));
    weak_ptr<int> wptr = ptr;
    // 判断shared_ptr对象是否已被销毁
    if (wptr.expired()) {
        cout << "shared_ptr对象已被销毁" << endl;
    } else {
        cout << "shared_ptr对象未被销毁" << endl;
    }

    // 释放ptr2对资源的所有权
    ptr.reset();

    // 再次判断shared_ptr对象是否已被销毁
    if (wptr.expired()) {
        cout << "shared_ptr对象已被销毁" << endl;
    } else {
        cout << "shared_ptr对象未被销毁" << endl;
    }


    {
        shared_ptr<int> fsPtr(new int(5));
        fwPtr = fsPtr;
    }

    // cout << "fsPtr use_count:" << fsPtr.use_count() << " fwPtr use_count:" << fwPtr.use_count() << endl;
    cout << "fwPtr use_count:" << fwPtr.use_count() << endl;

    shared_ptr<int> fsPtr2 = fwPtr.lock();
    cout << "fsPtr use_count:" << fsPtr2.use_count() << " fwPtr use_count:" << fwPtr.use_count() << endl;
    
    return 0;
}

/*
shared_ptr对象未被销毁
shared_ptr对象已被销毁
fwPtr use_count:0
fsPtr use_count:0 fwPtr use_count:0
*/