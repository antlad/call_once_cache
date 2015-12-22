#pragma once

#include <boost/functional/hash.hpp>

#include <mutex>
#include <unordered_set>

namespace cache
{

template<typename T>
void pack_hash(size_t & seed, T&& value)
{
    boost::hash_combine(seed, value);
}

template<typename T, typename... Args>
void pack_hash(size_t & seed, T&& value, Args&&... args)
{
    boost::hash_combine(seed, value);
    pack_hash(seed, args...);
}

class call_once
{
public:

    template<typename Functor, typename... Args>
    void call(Functor f, Args&&... args)
    {
        std::size_t seed = typeid(Functor).hash_code();
        pack_hash(seed, std::forward<Args>(args)...);


        if (m_calls.find(seed) != m_calls.end())
            return;
        f(std::forward<Args>(args)...);
        m_calls.insert(seed);
    }

private:
    std::unordered_set<std::size_t> m_calls;
};

class call_once_thread_safe
        : public call_once
{
public:
    template<typename Functor, typename... Args>
    void call(Functor f, Args&&... args)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        call_once::call(f, args...);
    }

private:
    std::mutex m_mutex;
};





}
