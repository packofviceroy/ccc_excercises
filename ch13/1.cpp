#include <stdlib.h>
#include <iostream>
#include <vector>


int main(int argc, char* argv[]){
    // std::cout<< "test";
    std::vector<unsigned long> vec;

    std::cout << vec.capacity() << std::endl;

    vec.reserve(30);

    std::cout << vec.capacity() << std::endl;

    vec.push_back(0);
    vec.push_back(1);
    int prev_el = 1;
    int pprev_el = 0;
    int cur;
    for (int i = 0; i < 18; i++){
        cur = pprev_el + prev_el;
        vec.push_back(pprev_el + prev_el);
        pprev_el = prev_el;
        prev_el = cur;
    }
    for (int i = 0; i < 20; i++){
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;

    std::cout << vec.capacity() << std::endl;

    return 0;
}