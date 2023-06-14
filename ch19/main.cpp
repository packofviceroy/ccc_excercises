#include <iostream>
#include <stdlib.h>
#include <atomic>
#include <mutex>
#include <future>
#include <chrono>

const int iterations = 1'000'000;
/*                  19.1
 * Напишите свой собственный мьютекс на основе спин-блокировки,
 * который называется SpinLock . Выставьте блокировку, try_lock и метод
 * разблокировки. Ваш класс должен удалить конструктор копирования.
 * Попробуйте использовать std::lock_guard<SpinLock> с экземпляром
 * вашего класса.
 */

struct SpinLock{
   bool try_lock();
   void unlock();
   void lock();

   SpinLock(const SpinLock&) = delete;
   SpinLock& operator=(const SpinLock&) = delete;
   SpinLock() : locker{} {}
private:
    std::atomic_flag locker;
};


void SpinLock::lock() {
  while(locker.test_and_set(std::memory_order_acquire)){}
}

bool SpinLock::try_lock() {
    if (locker.test_and_set(std::memory_order_acquire))
        return false;
    return true;
}

void SpinLock::unlock() {
    locker.clear(std::memory_order_release);
}


void lock_once()
{
    int available{};
    SpinLock spinLock;

    auto adder = std::async(std::launch::async, [&]{
        std::lock_guard<SpinLock> guard{spinLock};

        for (int i = 0; i < iterations; i++ )
        {
            available++;
        }
        return available;
    });
    auto subtractor = std::async(std::launch::async, [&] {
        std::lock_guard<SpinLock> guard{spinLock};
        for (int i = 0; i < iterations; i++ )
        {
            available--;
        }
        return available;
    });

    adder.get();
    subtractor.get();

    std::cout << "Available: " << available << std::endl;
}

void lock_on_each()
{
    int available{};
    SpinLock spinLock;

    auto adder = std::async(std::launch::async, [&]{
        for (int i = 0; i < iterations; i++ )
        {
            std::lock_guard<SpinLock> guard{spinLock};
            available++;
        }
        return available;
    });
    auto subtractor = std::async(std::launch::async, [&] {
        for (int i = 0; i < iterations; i++ )
        {
            std::lock_guard<SpinLock> guard{spinLock};
            available--;
        }
        return available;
    });

    adder.get();
    subtractor.get();

    std::cout << "Available: " << available << std::endl;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    lock_once();
    auto stop= std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Lock once time: " << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    lock_on_each();
    stop= std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Lock on each time: " << duration.count() << std::endl;
}
