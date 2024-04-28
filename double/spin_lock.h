
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <assert.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include<errno.h>

pid_t gettid()
{
    static __thread pid_t tid = 0;
    if ((tid == 0))
        tid = syscall(SYS_gettid);
    return tid;
}

struct spin_lock
{
 public:
    spin_lock()
    {
        pthread_spin_init(&_lock, PTHREAD_PROCESS_PRIVATE);
    }
    void lock() noexcept
    {
        pthread_spin_lock(&_lock);
        _tidHoldingLock = gettid();
    }

    [[nodiscard]]
    bool try_lock() noexcept
    {
#ifdef __linux__
        if (pthread_spin_trylock(&_lock) == 0)
        {
            _tidHoldingLock = gettid();
            return true;
        }
        else
            return false;
#else
        abort();
#endif
    }

    void unlock() noexcept
    {
        _tidHoldingLock = 0;
        pthread_spin_unlock(&_lock);
    }

    bool is_lock_held_by_this_thread()
    {
#ifdef __linux__
        return _tidHoldingLock == gettid();
#else
        abort();
#endif
    }


    void assert_is_held()
    {
#ifdef __linux__
        assert(pthread_spin_trylock(&_lock) == EBUSY);
        assert(_tidHoldingLock == gettid());
#endif
    }
 private:
    int _tidHoldingLock{0};
    pthread_spinlock_t _lock;
};