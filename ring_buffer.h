#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <assert.h>
#include <cstdint>
template <class T>
class RingBuffer
{
private:
    uint32_t m_size;
    uint32_t m_head;
    uint32_t m_tail;
    T* m_array;
public:
    explicit RingBuffer(uint32_t p_size) : m_size(p_size + 1), m_head(0), m_tail(0)
    {
        m_array = new T[m_size];
    }
    RingBuffer() : m_size(1000), m_head(0), m_tail(0)
    {
        m_array = new T[m_size];
    }
    RingBuffer(RingBuffer<T>& ringBuffer) = delete;
    RingBuffer(RingBuffer<T>&& ringBuffer) = delete;

    RingBuffer& operator=(RingBuffer<T>& ringBuffer) = delete;
    RingBuffer& operator=(RingBuffer<T>&& ringBuffer) = delete;
    ~RingBuffer()
    {
        delete[]m_array;
    }

    bool empty()
    {
        return m_head == m_tail;
    }
    uint32_t size()
    {
        return m_tail >= m_head ? (m_tail - m_head) : (m_tail + m_size - m_head);
    }
    bool push_back(const T& t)
    {
        if ((m_tail + 1) % m_size == m_head) // array fulled
        {
            return false;
        }
        else
        {
            m_array[m_tail] = t;
            m_tail = (m_tail + 1) % m_size;
            return true;
        }
    }
    T front()
    {
        bool empty = this->empty();
        assert(!empty);
        return m_array[m_head];
    }

    void pop_front()
    {
        if (this->empty())
        {
            return;
        }
        else
        {
            m_head = (m_head + 1) % m_size;
        }
    }
};

#endif
