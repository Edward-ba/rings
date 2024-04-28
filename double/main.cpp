#include <iostream>

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <iterator>

#include "spin_lock.h"

// struct ttas_lock {
//   std::atomic<bool> lock_ = {false};

//   void lock() {
//     for (;;) {
//       if (!lock_.exchange(true, std::memory_order_acquire)) {
//         break;
//       }
//       while (lock_.load(std::memory_order_relaxed)) {
//         __builtin_ia32_pause();
//       }
//     }
//   }
  
//   void unlock() { 
//     lock_.store(false, std::memory_order_release); 
//     }
// };


const int NUM_INSTRUMENTS = 16;

std::vector<int64_t> g_bank1(NUM_INSTRUMENTS*4, 0);
std::vector<int64_t> g_bank2(NUM_INSTRUMENTS*4, 0);

std::vector<int64_t>* g_modi = &g_bank1;
std::vector<int64_t>* g_read = &g_bank2;

static std::atomic_bool g_consume_lock = false;

spin_lock g_swap_lock2;

bool check(std::vector<int64_t>& validate) {
    int ix = 0;

    //std::pair<int64_t, int64_t> minmax = {__INT64_MAX__, 0 };

    while (ix < NUM_INSTRUMENTS*4) {
        bool good = true;
        int64_t chk0 = validate[ix + 0];
        int64_t chk1 = validate[ix + 1];
        int64_t chk2 = validate[ix + 2];
        int64_t chk3 = validate[ix + 3];

        std::this_thread::sleep_for(std::chrono::microseconds(500));

        if (chk0 != chk1 || chk0 != chk2 || chk0 != chk3) {
            std::cout << "ix: " << ix << std::endl;  
            std::cout << chk0 << " " << chk1 << " " << chk2 << " " << chk3 << std::endl;
            std::copy(begin(validate), end(validate), std::ostream_iterator<int64_t>(std::cout, " "));
            std::cout << std::endl;
            assert(false);
            return false;
        }
        ix += 4;

    }
    return true;
}

std::pair<int_fast64_t, int64_t> g_pro_locked{0, 0};

void producer0(bool& run, int64_t& inc, std::string name) {

    int ix = 0;
    while (run) {
        //std::cout << "prod: " << name << " :" << inc;

        (*g_modi)[4*ix+0] = inc;    // bid prc
        (*g_modi)[4*ix+1] = inc;    // bid sz
        (*g_modi)[4*ix+2] = inc;    // ask prc
        (*g_modi)[4*ix+3] = inc;    // ask sz

        ++inc;
        ix += 1;

        if (ix == NUM_INSTRUMENTS)
            ix = 0;

        // std::cout << "prod: " << name << " " << inc << " ";
        // std::copy(begin(*g_modi), end(*g_modi), std::ostream_iterator<int64_t>(std::cout, " ")); std::cout << std::endl;
        if (!g_consume_lock.load(std::memory_order_acquire)) {

        std::this_thread::sleep_for(std::chrono::microseconds(rand( ) % 10));


            if (g_swap_lock2.try_lock()) {
                std::swap(g_modi, g_read);
                g_swap_lock2.unlock();


        std::this_thread::sleep_for(std::chrono::microseconds(rand( ) % 10));

                // deep copy
                //*g_modi = *g_read;

                // std::cout << "swps: " << name << " " << inc << " ";
                // std::copy(begin(*g_modi), end(*g_modi), std::ostream_iterator<int64_t>(std::cout, " ")); std::cout << std::endl;

                //std::copy(begin(*g_modi), end(*g_modi), std::ostream_iterator<int64_t>(std::cout, " ")); std::cout << std::endl;
                //std::copy(begin(*g_read), end(*g_read), std::ostream_iterator<int64_t>(std::cout, " ")); std::cout << std::endl;
                //std::copy(begin(*g_modi), end(*g_modi), std::ostream_iterator<int64_t>(std::cout, " ")); std::cout << std::endl;
                ++g_pro_locked.first;
            } else {
                std::cout << "try-lock-fail: " << name << "------------------------- " << inc << std::endl;
                ++g_pro_locked.second;
            }
        } else {
            ++g_pro_locked.second;
        }

//        std::this_thread::sleep_for(std::chrono::microseconds(rand( ) % 10));
    }
}

void producer1(bool& run, int64_t& inc, std::string name) {

    while (run) {
        //std::cout << "prod: " << name << " :" << inc;

        for (int ix = 0; ix < NUM_INSTRUMENTS; ++ix) {
            (*g_modi)[4*ix+0] = inc;    // bid prc
            (*g_modi)[4*ix+1] = inc;    // bid sz
            (*g_modi)[4*ix+2] = inc;    // ask prc
            (*g_modi)[4*ix+3] = inc;    // ask sz
            ++inc;
        }

        std::cout << "prod: " << name << " " << inc << "->";
        std::copy(begin(*g_modi), end(*g_modi), std::ostream_iterator<int64_t>(std::cout, " ")); std::cout << std::endl;

        // g_consume_lock == false
        if (!g_consume_lock.load(std::memory_order_acquire)) {

            if (g_swap_lock2.try_lock()) {
                std::swap(g_modi, g_read);
                g_swap_lock2.unlock();
                // deep copy
                *g_modi = *g_read;

                // std::cout << "swps: " << name << " " << inc << " ";
                // std::copy(begin(*g_modi), end(*g_modi), std::ostream_iterator<int64_t>(std::cout, " ")); std::cout << std::endl;

                //std::copy(begin(*g_modi), end(*g_modi), std::ostream_iterator<int64_t>(std::cout, " ")); std::cout << std::endl;
                //std::copy(begin(*g_read), end(*g_read), std::ostream_iterator<int64_t>(std::cout, " ")); std::cout << std::endl;
                //std::copy(begin(*g_modi), end(*g_modi), std::ostream_iterator<int64_t>(std::cout, " ")); std::cout << std::endl;
                ++g_pro_locked.first;
            } else {
                std::cout << "try-lock-fail: " << name << "------------------------- " << inc << std::endl;
                ++g_pro_locked.second;
            }
        } else {
            ++g_pro_locked.second;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(rand( ) % 1));
    }
}



void consumer(bool& run, std::string name) {            // timer-thread

    int count = 0;
    std::vector<int64_t> tmp;

    while (run) {
        // set g_consume_lock = true
        g_consume_lock.store(true, std::memory_order_release);

g_swap_lock2.lock();
        // std::cout << "cons: " << name << " " << count << "---------- lock-------- " << std::endl;;

check(*g_read);

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        // std::cout << "cons: " << name << " " << count++ << " ";
        // std::copy(begin(*g_read), end(*g_read), std::ostream_iterator<int64_t>(std::cout, " "));
        // std::cout << std::endl;
g_swap_lock2.unlock();

        g_consume_lock.store(false, std::memory_order_release);
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
}

int main()
{
    // vector container stores threads
    std::vector<std::thread> workers;

    bool run = true;
    int64_t inc = 0;
    workers.push_back(std::thread(producer0, std::ref(run), std::ref(inc), "prod0"));
//    workers.push_back(std::thread(producer1, std::ref(run), std::ref(inc), "prod1"));
    workers.push_back(std::thread(consumer, std::ref(run), "cons0"));

    std::cout << "main thread\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    run = false;

    std::for_each(workers.begin(), workers.end(), [](std::thread &t) 
    {
        t.join();
    });

    std::cout << "inc: " << inc << std::endl;
    std::cout << "Produces locked unlocked_cnt: " << g_pro_locked.first <<  " locked_cnt:" << g_pro_locked.second << " ratio:" << (double) g_pro_locked.second / g_pro_locked.first * 100.0 << "%" << std::endl;

    return 0;
}