#include <iostream>
#include <array>

int main() {
    //2.9
    std::array<int,4> arr{{1,2,3,4}};
    printf("The third element is %d.\n", arr[2]); 
    arr[2] = 100;
    printf("The third element is %d.\n", arr[2]);
    
    //2.10
    unsigned long maximum = 0;
    std::array<unsigned long, 5> values = { 10, 50, 20, 40, 0 };
    for(size_t i=0; i < 5; i++) {
         if (values[i] > maximum) 
            maximum = values[i]; 
        }
    printf("The maximum value is %lu\n", maximum);

    //2.11
    maximum = 0;
    for(unsigned long value : values) {
        if (value > maximum) 
        maximum = value;
    }
     printf("The maximum value is %lu.\n", maximum);
}

