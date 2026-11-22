#include <iostream>
#include "\Users\lapte\Desktop\Blok1\3825B1FIsp1-2_3\includes\Lab2\utmatrix.h"

int main() {
    TMatrix<int> mat1(3);
    std::cout << "Введите матрицу 3x3 (верхнетреугольную):\n";
    std::cin >> mat1;

    TMatrix<int> mat2(3);
    std::cout << "Введите вторую матрицу 3x3:\n";
    std::cin >> mat2;

    TMatrix<int> sum = mat1 + mat2;
    std::cout << "Сумма матриц:\n" << sum << std::endl;

    if (mat1 == mat2) {
        std::cout << "Матрицы равны.\n";
    }
    else {
        std::cout << "Матрицы не равны.\n";
    }

    return 0;
}