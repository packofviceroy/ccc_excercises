#include <iostream>
#include <vector>

template <typename T>
struct Matrix
{
    Matrix() = delete;
    Matrix(size_t row, size_t col) : rows_len(row), col_len(col)
    {
        for (int i = 0; i < row; i++)
            data.push_back(std::vector<T>(col));
    }

    T &at(size_t row, size_t col)
    {
        if (row >= rows_len || col >= col_len)
            throw std::out_of_range{"Index invalid."};
        return data[row][col];
    }

    void printMatrix(){
        for (auto vec: data){
            for (auto el:vec)
            {
                std::cout << el << ',';
            }
            std::cout << std::endl;
        }
    }

private:
    size_t col_len;
    size_t rows_len;
    std::vector<std::vector<T>> data;
};

int main(int argc, char *argv[])
{
    Matrix<int> *m = new Matrix<int>(3, 3);
    m->printMatrix();
    m->at(0, 0) = 2;
    m->printMatrix();
    return 0;
}