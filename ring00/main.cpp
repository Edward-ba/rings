#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <stdlib.h>

const int BUFFER_SIZE = 10;

template<typename T>
class RingBuffer {
private:
    T buffer[BUFFER_SIZE];
    int head_;
    int tail_;

public:
    RingBuffer() : head_(0), tail_(0) {}

    void put(const T& item) {
        while ((head_ + 1) % BUFFER_SIZE == tail_) {}
        
        buffer[head_] = item;
        head_ = (head_ + 1) % BUFFER_SIZE;
        // std::cout << "head_ " << head << std::endl;
    }

    void get(std::vector<T>& items) {
        while (head_ == tail_) {}
        int size = (head_ - tail_ + BUFFER_SIZE) % BUFFER_SIZE;
        // std::cout << "size " << size << std::endl;
        items.resize(size);
        int i = 0;
        while (i < size) {
            items[i] = buffer[tail_];
            i += 1;
            tail_ = (tail_ + 1) % BUFFER_SIZE;
        }

        // std::cout << "tail " << tail_ << std::endl;
        // return items;
    }
};

template<typename T>
void producer(RingBuffer<T>& buffer) {
    for (uint32_t i = 0; i < 20; ++i) {
        buffer.put(i);
        std::cout << "Produced: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate some work
    }
}

template<typename T>
void consumer(RingBuffer<T>& buffer) {

    std::vector<T> items; 
    for (uint32_t i = 0; i < 20; ++i) {
        buffer.get(items);
        const auto now = std::chrono::system_clock::now();
        const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
        std::cout << std::ctime(&t_c) << "Consumed: ";

        for (const T& i : items) {
            std::cout << i << ' ';
        }

        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate some work
    }
}

class Foo {
    int32_t i_;
public:
    Foo() : i_(0) {}
    Foo(int i) {
        i_ = (i);
    } 

    Foo operator+(Foo const& obj)
    {
        Foo res;
        res.i_ = i_*100 + obj.i_;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Foo& dt);
};

std::ostream& operator<<(std::ostream& os, const Foo& foo)
{
    os << "i_:" << foo.i_;
    return os;
}

int main() {
    RingBuffer<Foo> buffer;

   std::thread producer_thread(producer<Foo>, std::ref(buffer));
   std::thread consumer_thread(consumer<Foo>, std::ref(buffer));

   producer_thread.join();
   consumer_thread.join();

    // Foo a (5);  
    // Foo b (6);  
    // Foo c = a + b;
    // std::cout << c << std::endl;


    return 0;
}
