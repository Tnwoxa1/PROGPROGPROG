#pragma once
#include <vector>

#define M_PI


std::vector<std::vector<float>> multiplyMatrices(const std::vector<std::vector <float>>& matrix1, const std::vector<std::vector<float>>& matrix2)//перемножение матриц
{
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    std::vector<std::vector<float>> result(rows1, std::vector<float>(cols2, 0));

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}


// Функция для транспонирования матрицы
std::vector<std::vector<float>> transpose(const std::vector<std::vector<float>>& matrix)
{
    size_t n = matrix.size();
    size_t m = matrix[0].size();
    std::vector<std::vector<float>> result(m, std::vector<float>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}


// Функция для нахождения псевдообратной матрицы Sigma с порогом
std::vector<std::vector<float>> pseudoInverseSigma(const std::vector<std::vector<float>>& sigma, float threshold)
{
    size_t n = sigma.size();
    size_t m = sigma[0].size();
    std::vector<std::vector<float>> sigmaInv(n, std::vector<float>(m, 0.0f));
    for (size_t i = 0; i < std::min(n, m); ++i) {
        if (i < threshold && sigma[i][i] != 0) {
            sigmaInv[i][i] = 1.0f / sigma[i][i];
        }
        else {
            sigmaInv[i][i] = 0.0f; // обнуляем значения от порога и далее
        }
    }
    return sigmaInv;
}




// Функция для вычисления обратной матрицы A с использованием SVD
std::vector<std::vector<float>> inverseMatrixUsingSVD(const std::vector<std::vector<float>>& U, const std::vector<std::vector<float>>& sigma, const std::vector<std::vector<float>>& V) {
    // Проверка, что матрица квадратная и все сингулярные значения ненулевые
    size_t n = sigma.size();
    size_t m = sigma[0].size();
    if (n != m) {
        throw std::invalid_argument("Matrix is not square, inverse cannot be computed.");
    }
    for (size_t i = 0; i < n; ++i) {
        if (sigma[i][i] <= std::numeric_limits<float>::epsilon()) {
            throw std::invalid_argument("Matrix is singular, inverse cannot be computed.");
        }
    }

    // 1. Найти обратную матрицу Sigma
    std::vector<std::vector<float>> sigmaInv = pseudoInverseSigma(sigma, n);

    // 2. Транспонировать матрицу U
    std::vector<std::vector<float>> UT = transpose(U);

    // 3. Найти обратную матрицу A: A^-1 = V * Sigma^+ * U^T
    std::vector<std::vector<float>> V_SigmaInv = multiplyMatrices(V, sigmaInv);
    std::vector<std::vector<float>> A_inv = multiplyMatrices(V_SigmaInv, UT);

    return A_inv;
}


std::vector<std::vector<float>> pseudoInverseMatrixUsingSVD(const std::vector<std::vector<float>>& U, const std::vector<std::vector<float>>& sigma, const std::vector<std::vector<float>>& V, int threshold) {
    // 1. Найти псевдообратную матрицу Sigma с порогом
    std::vector<std::vector<float>> sigmaInv = pseudoInverseSigma(sigma, threshold);

    // 2. Транспонировать матрицу U
    std::vector<std::vector<float>> UT = transpose(U);

    // 3. Найти псевдообратную матрицу A: A^+ = V * Sigma^+ * U^T
    std::vector<std::vector<float>> V_SigmaInv = multiplyMatrices(V, sigmaInv);
    std::vector<std::vector<float>> A_pinv = multiplyMatrices(V_SigmaInv, UT);

    return A_pinv;
}


// Функция для перемножения матрицы A и вектора x
std::vector<float> multiplyMatrixVector(const std::vector<std::vector<float>>& A, const std::vector<float>& x) {
    int n = A.size();
    int m = A[0].size();
    std::vector<float> result(n, 0.0f);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result[i] += A[i][j] * x[j];
        }
    }
    return result;
}

// Функция для расчёта разности между двумя векторами
std::vector<float> Diff(const std::vector<float>& x, const std::vector<float>& xpseudo) {
    int n = x.size();
    std::vector<float> difference(n, 0.0f);
    for (int i = 0; i < n; ++i) {
        difference[i] = x[i] - xpseudo[i];
    }
    return difference;
}

// Функция для вычисления среднего значения вектора
float average(const std::vector<float>& difference) {
    float sum = 0.0f;
    for (const auto& value : difference) {
        sum += value;
    }
    return sum / difference.size();
}

///////////////////////////////2 часть////////////////////////////////

std::vector<float> Gen_Sign(int N, double fd, double A1, double A2, double A3, double f1, double f2, double f3, double fi1, double fi2, double fi3)
{
    std::vector<float> Sign;
    Sign.resize(N);
    double* x = new double[N];
    double dt = 0;

    for (int i = 0; i < N; i++)
    {
        dt = double(i) / fd;
        x[i] = A1 * sin(2 * 3.14159265 * f1 * dt + fi1) + A2 * sin(2 * 3.14159265 * f2 * dt + fi2) + A3 * sin(2 * 3.14159265 * f3 * dt + fi3);

        Sign[i] = x[i];



    }
    return Sign;
}


void MatrixAKP(int P,int N, std::vector<float> rxx,std::vector<float> Signal, std::vector<std::vector<float>> Rxx)
        {
             rxx.resize(P);
        	for (int i = 0; i < P; i++)  // поиск отсчетов автокорреляции
        	{
                //rxx[i] = 0;
        		for (int j = 0; j < (N - i); j++)
        		{
        			rxx[i] += Signal[j] * Signal[j + i];
        		}
        		rxx[i] /= (N - i);
        	}

           // Rxx.resize(P);
            for (int i = 0; i < P; i++)
            {
                /*Rxx[i].resize(P);*/
                for (int j = 0; j < P; j++)
                {
                    Rxx[i][j] = rxx[abs(i - j)];
                }

              
            }

            
        }




//std::vector<std::vector<double>> minus(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B)
//{
//    int n = A.size();
//    int m = A[0].size();
//
//    std::vector<std::vector<double>> result(n, std::vector<double>(m, 0.0));
//
//    for (int i = 0; i < n; ++i)
//    {
//        for (int j = 0; j < m; ++j)
//        {
//            result[i][j] = A[i][j] - B[i][j];
//        }
//    }
//
//    return result;
//}


