#include <iostream>
#include <set>
#include <cstring>

struct Comparator{
    bool operator()(const char* s1, const char* s2){
    for (int i = 0; i < strlen(s1) && i < strlen(s2) ; i++){
        if (s1[i] == s2[i])
            continue;
        return s1[i] < s2[i];
    }
    return true;
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