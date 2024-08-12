#include <iostream>
#include <set>

bool comp(const char* s1, const char* s2){
    for (int i = 0; i < strlen(s1) && i < strlen(s2) ; i++){
        if (s1[i] == s2[i])
            continue;
        return s1[i] > s2[i];
    }
    return false;
}

int main(int argc, char* argv[]){
    
    auto cmp = [](const char* s1, const char* s2){   
     for (int i = 0; i < strlen(s1) && i < strlen(s2) ; i++){
        if (s1[i] == s2[i])
            continue;
        return s1[i] > s2[i];
    }
    return false;
    };
    std::set<const char*, decltype(cmp)> abc;

    for (int i = 1; i < argc; i++){
        abc.insert(argv[i]);
    }

    return 0;
}