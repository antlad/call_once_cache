#include <boost/thread.hpp>

#include <mutex>
#include <vector>

#include <iostream>
#include "call_once.h"

class A
{
public:

    std::vector<int> get_foo()
    {
        return m_callcache.call([&](int a, int b)
        {
            m_data.push_back(a);
            m_data.push_back(b);
            return m_data;
        }, 123, 321);
    }

private:
    std::vector<int> m_data;
    cache::call_once m_callcache;
};

int main() {

    A a;
    std::cout << a.get_foo().size() << std::endl;
    return 0;
}

