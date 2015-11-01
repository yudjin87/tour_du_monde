#pragma once

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>


template<typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue(const size_t limit)
        : m_queue()
        , m_mtx()
        , m_cond()
        , m_limitCond()
        , m_limit(limit)
    {
    }

    void push(T item)
    {
        std::unique_lock<std::mutex> pop_guard(m_mtx);
        m_limitCond.wait(pop_guard, [this] () { return m_queue.size() < m_limit; } );

        m_queue.push(std::move(item));
        m_cond.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> pop_guard(m_mtx);
        m_cond.wait(pop_guard, [this] () { return !m_queue.empty(); } );
        T item = std::move(m_queue.front());
        m_queue.pop();
        m_limitCond.notify_one();

        return std::move(item);
    }

    bool tryPop(T& item)
    {
        std::unique_lock<std::mutex> pop_guard(m_mtx);

        if (m_queue.empty())
        {
            return false;
        }

        item = m_queue.front();
        m_queue.pop();
        return true;
    }

    size_t size()
    {
        std::unique_lock<std::mutex> pop_guard(m_mtx);
        return m_queue.size();
    }

    void clean()
    {
        std::unique_lock<std::mutex> clean_guard(m_mtx);
        while (!m_queue.empty())
        {
            m_queue.pop();
        }
    }

private:
    std::queue<T> m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cond;
    std::condition_variable m_limitCond;
    const size_t m_limit;
};
