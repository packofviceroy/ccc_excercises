#include <iostream>
#include <vector>

template <typename T> 
struct Matrix{
    Matrix(size_t col, size_t row){
        for( int i = 0; i < col; i++)
            columns.push_back(std::vector<T>(row));
    }
    
private:
    std::vector<std::vector<T>> columns;
    std::vector<T> rows;
};

int main(int argc, char* argv[])
{

    return 0;
}