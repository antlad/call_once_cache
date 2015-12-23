#include <boost/thread.hpp>

#include <vector>

#include <iostream>

#include "call_once.h"

class A
{
public:

    std::vector<int> get_foo()
    {
        m_callcache.call([&](int a, int b)
        {
            m_data.push_back(a);
            m_data.push_back(b);
            std::cout << "init" << std::endl;
        }, 123, 321);

        return m_data;
    }

private:
    std::vector<int> m_data;
    cache::call_once<cache::ThreadSafeStd> m_callcache;
};

int main() {
    A a;
    std::cout << a.get_foo().size() << std::endl;
    std::cout << a.get_foo().size() << std::endl;
    return 0;
}

