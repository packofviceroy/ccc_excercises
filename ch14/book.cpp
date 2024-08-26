#include <forward_list>
#include <stack>

#include "catch_amalgamated.hpp"
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("std::forward_list’s begin and end provide forward iterators")
{
    const std::forward_list<int> easy_as{1, 2, 3};
    auto itr1 = easy_as.begin();
    auto itr2{itr1};
    int double_sum{};
    while (itr1 != easy_as.end())
        double_sum += *(itr1++);
    while (itr2 != easy_as.end())
        double_sum += *(itr2++);
    REQUIRE(double_sum == 12);
}

TEST_CASE("std::stack begin and end provide forward iterators")
{
    const std::deque<int> a{1, 2, 3, 4};
    auto itr1 = a.begin();
    auto itr2 = itr1;
    auto itr3 = a.begin();
    int sum = 0;
    REQUIRE(*itr1 == 1 );
    REQUIRE(*itr2 == 1 );
    REQUIRE(*itr3 == 1);
    while (itr1 != a.end())
    {
        sum += *itr1;
        itr1++;
    }
    REQUIRE(sum == 10);
    while (itr2 != a.end())
    {
        sum += *itr2;
        itr2++;
    }
    REQUIRE(sum == 20);
    while (itr3 != a.end())
    {
        sum += *itr3;
        itr3++;
    }
    REQUIRE(sum == 30);
}