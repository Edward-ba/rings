#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 10;

template<typename T>
class RingBuffer {
private:
    T buffer[BUFFER_SIZE];
    int head;
    int tail;
    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;

public:
    RingBuffer() : head(0), tail(0) {}

    void put(const T& item) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // lamda
        not_full.wait(lock, [this] () 
            { return (head + 1) % BUFFER_SIZE != tail; }
        );
        
        buffer[head] = item;
        head = (head + 1) % BUFFER_SIZE;
        not_empty.notify_one();
    }

    T get() {
        std::unique_lock<std::mutex> lock(mtx);
        not_empty.wait(lock, [this]() { return head != tail; });
        T item = buffer[tail];
        tail = (tail + 1) % BUFFER_SIZE;
        not_full.notify_one();
        return item;
    }
};

void producer(RingBuffer<int>& buffer) {
    for (int i = 0; i < 20; ++i) {
        buffer.put((double) i);
        std::cout << "Produced: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate some work
    }
}

void consumer(RingBuffer<int>& buffer) {
    for (int i = 0; i < 20; ++i) {
        int item = buffer.get();
        std::cout << "Consumed: " << item << std::endl;
    }
}

int main() {
    RingBuffer<int> buffer;

    std::thread producer_thread(producer, std::ref(buffer));
    std::thread consumer_thread(consumer, std::ref(buffer));

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
