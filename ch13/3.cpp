#include <iostream>
#include <set>
#include <cstring>

struct Comparator{
    bool operator()(const char* s1, const char* s2){
        return std::strcmp(s1, s2) < 0;
    }
};

int main(int argc, char* argv[]){
    
    std::set<const char*, Comparator> abc ;

    for (int i = 1; i < argc; i++){
        abc.insert(argv[i]);
    }

    for (auto el : abc){
        std::cout << el << std::endl;
    }
    return 0;
}