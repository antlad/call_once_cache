#pragma once

#include <boost/functional/hash.hpp>

#ifdef DEBUG_OUTPUT
#include <iostream>
#endif

namespace cache
{

template<typename T>
void pack_hash(size_t & seed, T&& value)
{
#ifdef DEBUG_OUTPUT
    std::cout << "calc hash from " << value << std::endl;
#endif
    boost::hash_combine(seed, value);
}

template<typename T, typename... Args>
void pack_hash(size_t & seed, T&& value, Args&&... args)
{
#ifdef DEBUG_OUTPUT
    std::cout << "calc hash from " << value << std::endl;
#endif
    boost::hash_combine(seed, value);
    pack_hash(seed, args...);
}

class call_once
{
public:
    template<typename Functor, typename... Args>
    auto call(Functor f, Args&&... args) -> decltype(f(std::forward<Args>(args)...))
    {
        std::size_t seed = typeid(Functor).hash_code();
        pack_hash(seed, std::forward<Args>(args)...);
#ifdef DEBUG_OUTPUT
        std::cout << seed << std::endl;
#endif
        return f(std::forward<Args>(args)...);
    }
};

}
