#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>
#include <map>

struct Stopwatch
{
    Stopwatch(std::chrono::nanoseconds &result)
        : result{result},
          start{std::chrono::system_clock::now()} {}
    ~Stopwatch()
    {
        result = std::chrono::system_clock::now() - start;
    }

private:
    std::chrono::nanoseconds &result;
    const std::chrono::time_point<std::chrono::system_clock> start;
};

int fib_sum(size_t n)
{
    std::vector<unsigned long> vec;
    vec.push_back(0);
    vec.push_back(1);
    int prev_el = 1;
    int pprev_el = 0;
    int cur;
    long int sum = 0;
    for (int i = 0; i < 18; i++){
        cur = pprev_el + prev_el;
        vec.push_back(pprev_el + prev_el);
        pprev_el = prev_el;
        prev_el = cur;
    }
    for (auto el:vec){
        sum+=el;
    }
    return 0;
}

long cached_fib_sum(size_t n) {
    static std::map<long, long> cache;
    if (cache.find(n) != cache.end())
    {
        return cache.at(n);
    }
    long ret = fib_sum(n);
    cache[n] = ret; 
    return ret;
}

long random()
{
    static std::mt19937_64 mt_engine{102787};
    static std::uniform_int_distribution<long> int_d{1000, 2000};
    return int_d(mt_engine);
}

int main(int argc, char *argv[])
{

    size_t samples{1'000'000};
    std::chrono::nanoseconds elapsed;
    {
        Stopwatch stopwatch{elapsed};
        volatile double answer;
        while (samples--)
        {
            // answer = fib_sum(random());
            answer = cached_fib_sum(random());
        }
    }
        printf("Elapsed: %g s.\n", elapsed.count() / 1'000'000'000.);
}